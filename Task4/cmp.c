#include <stdio.h>
#include <string.h>

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
		}
    return 0;
}


int chek(int c, char * v[]) {
	if (c < 3) {
		fprintf(stderr, "Не правильный ввод команды\n");
		return -1;
	} else if (file_exists(v[1]) == 0) {
        fprintf(stderr, "Файл '%s' не существует.\n", v[1]);
        return -1;
    } else if (file_exists(v[2]) == 0) {
        fprintf(stderr, "Файл '%s' не существует.\n", v[2]);
		return -1;
	}
	return 0;
}


int main(int argc, char *argv[]) {
	if (chek(argc, argv) == 0) {
		FILE *file1 = fopen(argv[1], "r");
		FILE *file2 = fopen(argv[2], "r");
		
		int sym1, sym2;
		int line = 1;
		int byte = 1;

		while (((sym1 = fgetc(file1)) != EOF) && ((sym2 = fgetc(file2)) != EOF)) {
			if (sym1 != sym2) {
				printf("%s differs from %s: line %d char %d\n", argv[1], argv[2], line, byte);
				break;
			} else {
				if (sym1 == '\n') {
					line++;
					byte = 1;
				} else byte++;
			}
		}
		if ((sym1 == EOF) && (sym2 != EOF))
			printf("%s differs from %s: EOF on %s\n", argv[1], argv[2], argv[1]);
		else if ((sym2 == EOF) && (sym1 != EOF))
			printf("%s differs from %s: EOF on %s\n", argv[1], argv[2], argv[2]);
		fclose(file1);
		fclose(file2);
	}
	return 0;
}
