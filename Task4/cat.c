#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int i = 1;
    int sym;
    int line_num = 0;
	int strf = 0;
    FILE *file = NULL;
    
    if (argc < 1) {
        fprintf(stderr, "Incorrect input\n");
        exit(1);
    }

    if (strcmp(argv[i], "-n") == 0) {
        if (argc >= 3) {
			line_num = 1;
			i++;
		} else {
			fprintf(stderr, "Incorrect input\n");
			exit(1);
		}
    }

    while (i < argc) {
        if (!file_exists(argv[i])) {
            fprintf(stderr, "Файл '%s' не существует.\n", argv[i]);
            i++;
            continue;
        }

        file = fopen(argv[i], "r");
        if (!file) {
            fprintf(stderr, "Не удалось открыть файл '%s'.\n", argv[i]);
            i++;
			exit(1);
			continue;
        }
        
        while ((sym = fgetc(file)) != EOF) {
            if ((line_num != 0) && (strf == 0)) {
                printf("%-2d ", line_num);
                line_num++;
				strf++;
            }
            putchar(sym);
            
            if (sym == '\n') {
                strf = 0;
            }
        }
        
        fclose(file);
        file = NULL;
        

        i++;
    }
    
    return 0;
}
