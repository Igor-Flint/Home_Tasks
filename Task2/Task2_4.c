#include <stdio.h>

double str2double(char str[]) {
    double result = 0.0;
    double fraction = 0.1;
    int exponent = 0;
    int sign = 1;
    int exp_sign = 1;
    int i = 0, j;
    int has_fraction = 0;
    int has_exponent = 0;
    
    while (str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while ((str[i] >= '0') && (str[i] <= '9')) {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    
    if (str[i] == '.') {
        has_fraction = 1;
        i++;
        while ((str[i] >= '0') && (str[i] <= '9')) {
            result += (str[i] - '0') * fraction;
            fraction *= 0.1;
            i++;
        }
    }
    
    if ((str[i] == 'e') || (str[i] == 'E')) {
        has_exponent = 1;
        i++;
        
        if (str[i] == '-') {
            exp_sign = -1;
            i++;
        } else if (str[i] == '+') {
            i++;
        }

        while ((str[i] >= '0') && (str[i] <= '9')) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }
    }

    if (has_exponent) {
        if (exp_sign > 0) {
            for (j = 0; j < exponent; j++) {
                result *= 10.0;
            }
        } else {
            for (j = 0; j < exponent; j++) {
                result /= 10.0;
            }
        }
    }   
    return sign * result;
}

int main() {
    char str[100];
    
    while (scanf("%99s", str) != EOF) {
        double number = str2double(str);
        printf("%.10g\n", number);
    }
    
    return 0;
}
