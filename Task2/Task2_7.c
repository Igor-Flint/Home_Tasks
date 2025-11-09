#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf begin;
char curlex;

void getlex(void);
int expr(void);
int prop(void);
int factor(void);
int power(void);
void error(void);

int main() {
    int result;
    setjmp(begin);
    printf("> ");
    
    getlex();
    if (curlex == '\n') {
        return 0;
    }
    
    result = expr();
    if (curlex != '\n') error();
    printf("%d\n", result);
    return 0;
}

void getlex() {
    while ((curlex = getchar()) == ' ');
}

void error(void) {
    printf("\nERROR\n");
    while (getchar() != '\n');
    longjmp(begin, 1);
}

int expr() {
    int e = prop();
    while (curlex == '+' || curlex == '-') {
        char op = curlex;
        getlex();
        int t = prop();
        if (op == '+') e += t;
        else e -= t;
    }
    return e;
}

int prop() {
    int t = factor();
    while (curlex == '*' || curlex == '/') {
        char op = curlex;
        getlex();
        int f = factor();
        if (op == '*') t *= f;
        else {
            if (f == 0) error();
            t /= f;
        }
    }
    return t;
}

int factor() {
    int f = power();
    if (curlex == '^') {
        getlex();
        int p = factor();
        if (p < 0) error();
        
        int result = 1;
        for (int i = 0; i < p; i++) {
            result *= f;
        }
        f = result;
    }
    return f;
}

int power() {
    int p;
    switch (curlex) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            p = curlex - '0';
            break;
        case '(':
            getlex();
            p = expr();
            if (curlex != ')') error();
            break;
        default:
            error();
    }
    getlex();
    return p;
}





