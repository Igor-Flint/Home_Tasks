#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef MAJOR
#define MINOR_SIZE 8
#define DEVICE_MAJOR(x) ((unsigned) x >> MINOR_SIZE)
#define DEVICE_MINOR(x) (x & ((1U << MINOR_SIZE) - 1))
#endif


int detailed_mode_enabled = 0;
int recursive_mode_enabled = 0;
int hide_owner_info_enabled = 0;


void show_file_category(mode_t file_permissions) {                                   
    switch (file_permissions & S_IFMT) {
        case S_IFDIR:  putchar('d'); return;
        case S_IFCHR:  putchar('c'); return;
        case S_IFBLK:  putchar('b'); return;
        case S_IFREG:  putchar('-'); return;
        case S_IFLNK:  putchar('l'); return;
        case S_IFSOCK: putchar('s'); return;
        case S_IFIFO:  putchar('p'); return;
        default:       putchar('?'); return;
    }
} 


void show_access_rights(mode_t permission_bits) {
    const char permission_template[] = "rwxrwxrwx";
    char formatted_permissions[10];
    int position, mask_bit;


    for (position = 0, mask_bit = (1 << 8); position < 9; position++, mask_bit >>= 1)
        formatted_permissions[position] = (permission_bits & mask_bit) ? 
                                          permission_template[position] : '-';
    

    if (permission_bits & S_ISUID) formatted_permissions[2] = 
        (permission_bits & S_IXUSR) ? 's' : 'S';
    if (permission_bits & S_ISGID) formatted_permissions[5] = 
        (permission_bits & S_IXGRP) ? 's' : 'S';
    if (permission_bits & S_ISVTX) formatted_permissions[8] = 
        (permission_bits & S_IXOTH) ? 't' : 'T';
    
    formatted_permissions[9] = '\0';
    printf("%s ", formatted_permissions);
}


void output_formatted_timestamp(time_t modification_time) {
    char time_string[64];
    struct tm *local_time = localtime(&modification_time);
    

    strftime(time_string, sizeof(time_string), "%b %e %H:%M", local_time);
    printf("%s ", time_string);
}


void display_file_details(const char *directory_path, const char *entry_name) {
    struct stat file_statistics;
    char absolute_path[1024];
    struct passwd *user_info;
    struct group *group_info;
    

    if (strcmp(directory_path, ".") == 0) {
        snprintf(absolute_path, sizeof(absolute_path), "%s", entry_name);
    } else {
        snprintf(absolute_path, sizeof(absolute_path), "%s/%s", 
                directory_path, entry_name);
    }
    

    if (lstat(absolute_path, &file_statistics)) { 
        perror(absolute_path);
        return;
    }
    

    show_file_category(file_statistics.st_mode);
    

    show_access_rights(file_statistics.st_mode);
    

    printf("%3ld ", (long)file_statistics.st_nlink);
    

    if (!hide_owner_info_enabled) {
        user_info = getpwuid(file_statistics.st_uid);
        if (user_info) {
            printf("%-8s ", user_info->pw_name);
        } else {
            printf("%-8d ", file_statistics.st_uid);
        }
    }
    

    group_info = getgrgid(file_statistics.st_gid);
    if (group_info) {
        printf("%-8s ", group_info->gr_name);
    } else {
        printf("%-8d ", file_statistics.st_gid);
    }


    if ((file_statistics.st_mode & S_IFMT) == S_IFCHR || 
        (file_statistics.st_mode & S_IFMT) == S_IFBLK) {
        printf("%4d, %4ld ", 
               DEVICE_MAJOR(file_statistics.st_rdev), 
               DEVICE_MINOR(file_statistics.st_rdev));
    } else {

        printf("%8ld ", (long)file_statistics.st_size);
    }
    

    output_formatted_timestamp(file_statistics.st_mtime);
    

    printf("%s", entry_name);
    

    if ((file_statistics.st_mode & S_IFMT) == S_IFLNK) {
        char link_destination[1024];
        ssize_t path_length = readlink(absolute_path, link_destination, 
                                      sizeof(link_destination) - 1);
        if (path_length != -1) {
            link_destination[path_length] = '\0';
            printf(" -> %s", link_destination);
        }
    }
    
    putchar('\n');
}


void print_basic_info(const char *dir_path, const char *filename) {
    printf("%s\n", filename);
}


void explore_directory_recursively(const char *current_path) {
    DIR *directory_stream;
    struct dirent *directory_entry;
    struct stat entry_statistics;
    char complete_file_path[1024];
    

    directory_stream = opendir(current_path);
    if (!directory_stream) {
        perror(current_path);
        return;
    }
    

    if (strcmp(current_path, ".") != 0) {
        printf("\n%s:\n", current_path);
    }
    

    while ((directory_entry = readdir(directory_stream)) != NULL) {
        if (strcmp(directory_entry->d_name, ".") == 0 || 
            strcmp(directory_entry->d_name, "..") == 0) {
            continue;
        }
        
        if (strcmp(current_path, ".") == 0) {
            snprintf(complete_file_path, sizeof(complete_file_path), 
                    "%s", directory_entry->d_name);
        } else {
            snprintf(complete_file_path, sizeof(complete_file_path), 
                    "%s/%s", current_path, directory_entry->d_name);
        }
        
        if (lstat(complete_file_path, &entry_statistics)) {
            perror(complete_file_path);
            continue;
        }
        
        if (detailed_mode_enabled) {
            display_file_details(current_path, directory_entry->d_name);
        } else {
            print_basic_info(current_path, directory_entry->d_name);
        }
        
        if (recursive_mode_enabled && S_ISDIR(entry_statistics.st_mode)) {
            explore_directory_recursively(complete_file_path);
        }
    }
    
    closedir(directory_stream);
}


void explore_directory_flat(const char *path_to_explore) {
    DIR *dir_handle;
    struct dirent *dir_item;
    

    dir_handle = opendir(path_to_explore);
    if (!dir_handle) {
        perror(path_to_explore);
        return;
    }
    
    while ((dir_item = readdir(dir_handle)) != NULL) {
        if (strcmp(dir_item->d_name, ".") == 0 || 
            strcmp(dir_item->d_name, "..") == 0) {
            continue;
        }
        
        if (detailed_mode_enabled) {
            display_file_details(path_to_explore, dir_item->d_name);
        } else {
            print_basic_info(path_to_explore, dir_item->d_name);
        }
    }
    
    closedir(dir_handle);
}


void handle_filesystem_item(const char *item_path) {
    struct stat item_info;
    
    if (lstat(item_path, &item_info)) {
        perror(item_path);
        return;
    }
    
    if (S_ISDIR(item_info.st_mode)) {
        if (recursive_mode_enabled) {
            explore_directory_recursively(item_path);
        } else {
            explore_directory_flat(item_path);
        }
    } else {
        if (detailed_mode_enabled) {
            char *name_only = strrchr(item_path, '/');
            if (name_only) {
                name_only++;
                char parent_dir[1024];
                strncpy(parent_dir, item_path, name_only - item_path - 1);
                parent_dir[name_only - item_path - 1] = '\0';
                display_file_details(parent_dir, name_only);
            } else {
                display_file_details(".", item_path);
            }
        } else {
            printf("%s\n", item_path);
        }
    }
}


void process_command_line(int argument_count, char *argument_values[]) {
    int option_char;
    
    while ((option_char = getopt(argument_count, argument_values, "lRg")) != -1) {
        switch (option_char) {
            case 'l': 
                detailed_mode_enabled = 1;
                break;
            case 'R':
                recursive_mode_enabled = 1;
                break;
            case 'g':
                hide_owner_info_enabled = 1;
                break;
            default:
                exit(1);
        }
    }
}


int main(int argc, char *argv[]) {
    process_command_line(argc, argv);
    
    int processed_items = 0;
    
    for (int i = optind; i < argc; i++) {
        handle_filesystem_item(argv[i]);
        processed_items++;
    }
    
    if (processed_items == 0) {
        if (recursive_mode_enabled) {
            explore_directory_recursively(".");
        } else {
            explore_directory_flat(".");
        }
    }
    
    return 0;
}

