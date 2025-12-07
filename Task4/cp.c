#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>


#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Error: Source and destination are the same file\n");
        return 1;
    }

    int src_fd, dst_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    struct stat src_stat;

    if (stat(argv[1], &src_stat) == -1) {
        fprintf(stderr, "Error: Cannot stat source file '%s': %s\n",
                argv[1], strerror(errno));
        return 1;
    }

    if (!S_ISREG(src_stat.st_mode)) {
        fprintf(stderr, "Error: '%s' is not a regular file\n", argv[1]);
        return 1;
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        fprintf(stderr, "Error: Cannot open source file '%s': %s\n",
                argv[1], strerror(errno));
        return 1;
    }

    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, src_stat.st_mode);

    if (dst_fd == -1) {
        fprintf(stderr, "Error: Cannot open destination file '%s': %s\n",
                argv[2], strerror(errno));
        close(src_fd);
        return 1;
    }

	fchmod(dst_fd, src_stat.st_mode);
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error: Write failed: %s\n", strerror(errno));
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Error: Read failed: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    if (close(src_fd) == -1) {
        fprintf(stderr, "Warning: Error closing source file: %s\n",
                strerror(errno));
    }

    if (close(dst_fd) == -1) {
        fprintf(stderr, "Warning: Error closing destination file: %s\n",
                strerror(errno));
    }
	

    return 0;
}
