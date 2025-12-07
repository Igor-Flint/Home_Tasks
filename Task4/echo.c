#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hexadecimal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

void print_with_escapes(const char *str) {
    while (*str) {
        if (*str == '\\') {
            str++;
            if (*str == '\0') {
                putchar('\\');
                break;
            }
            
            switch (*str) {
                case '\\': putchar('\\'); break;
                case 'a': putchar('\a'); break;
                case 'b': putchar('\b'); break;
                case 'e': putchar('\x1B'); break;
                case 'f': putchar('\f'); break;
                case 'n': putchar('\n'); break;
                case 'r': putchar('\r'); break;
                case 't': putchar('\t'); break;
                case 'v': putchar('\v'); break;
                case '0': {
                    int oct_val = 0;
                    int digits = 0;
                    str++;
                    while (digits < 3 && *str && *str >= '0' && *str <= '7') {
                        oct_val = oct_val * 8 + (*str - '0');
                        str++;
                        digits++;
                    }
                    putchar(oct_val);
                    if (*str != '\0') {
                        str--;
                    }
                    break;
                }
                case 'x': {
                    int hex_val = 0;
                    int digits = 0;
                    str++;
                    if (*str == '\0') {
                        putchar('\\');
                        putchar('x');
                        break;
                    }
                    while (digits < 2 && *str) {
                        int digit = hexadecimal(*str);
                        if (digit == -1) break;
                        hex_val = hex_val * 16 + digit;
                        str++;
                        digits++;
                    }
                    putchar(hex_val);
                    if (*str != '\0') {
                        str--;
                    }
                    break;
                }
                default:
                    putchar('\\');
                    putchar(*str);
                    break;
            }
        } else {
            putchar(*str);
        }
        str++;
    }
}

int main(int argc, char *argv[]) {
    int i = 1;
    int newline = 1;
    int sequence_escapes = 0;
    
    if (argc < 2) {
        putchar('\n');
        return 0;
    }
    
    while (i < argc) {
        if (argv[i][0] == '-') {
            int j = 1;
            while (argv[i][j] != '\0') {
                switch (argv[i][j]) {
                    case 'n':
                        newline = 0;
                        break;
                    case 'e':
                        sequence_escapes = 1;
                        break;
                    case 'E':
                        sequence_escapes = 0;
                        break;
                    default:
                        fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
                        exit(1);
                }
                j++;
            }
            i++;
        } else {
            break;
        }
    }
    
    for (; i < argc; i++) {
        if (sequence_escapes) {
            print_with_escapes(argv[i]);
        } else {
            fputs(argv[i], stdout);
        }
        if (i + 1 < argc) {
            putchar(' ');
        }
    }
    
    if (newline) {
        putchar('\n');
    }
    
    return 0;
}
