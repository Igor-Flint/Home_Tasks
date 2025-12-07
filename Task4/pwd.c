#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char * argv[]) {
	size_t buf = 4096;
	int flag_corr = 0;
	if ((argc == 1) && (argv[1] != NULL)) {
		char *pwd = malloc(buf);
		while (flag_corr != 1) {
			if (getcwd(pwd, buf) != NULL) {
				printf("%s\n", pwd);
				free(pwd);
				flag_corr = 1;
			} else {
				buf = buf * 2;
				pwd = realloc(pwd, buf);
			}
		}
	} else fprintf(stderr, "Incorrect input\n");
	return 0;
}
