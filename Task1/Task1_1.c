#include <stdio.h>

int main() {
    printf("Размеры типов данных в байтах:\n");
    printf("===============================\n");
    printf("short: %zu байт\n", sizeof(short));
    printf("int: %zu байт\n", sizeof(int));
    printf("long: %zu байт\n", sizeof(long));
    printf("float: %zu байт\n", sizeof(float));
    printf("double: %zu байт\n", sizeof(double));
    printf("long double: %zu байт\n", sizeof(long double));
}
