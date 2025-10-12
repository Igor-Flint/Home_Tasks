#include <stdio.h>

extern const int external_const;
static const int static_const = 20;
const int int_const = 30;
const float float_const = 3.14f;
const double double_const = 2.71828;
const char* string_const = "Hello, World!";

int main() {
    printf("Проверка реакции компилятора на попытку изменения констант:\n");
    printf("===========================================================\n");
    const int auto_const = 10;
    printf("Автоматическая константа: %d\n", auto_const);
    printf("Статическая константа: %d\n", static_const);
    printf("Целочисленная константа: %d\n", int_const);
    printf("Вещественная константа (float): %.2f\n", float_const);
    printf("Вещественная константа (double): %.5f\n", double_const);
    printf("Строковая константа: %s\n", string_const);
    
    printf("\nПопытка изменить константы:\n");
    printf("==================================================================\n");
    auto_const = 100;
    
    static_const = 200;
    
    int_const = 300;
    float_const = 4.15f;
    double_const = 3.14159;
    
    string_const[0] = 'h';
    *string_const = 'h';
    external_const = 400;
    
    printf("\nКомпилятор успешно предотвращает все попытки изменения констант!\n");
    
    return 0;
}
