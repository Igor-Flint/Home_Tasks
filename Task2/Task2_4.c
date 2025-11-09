#include <stdio.h>

double str2double(char str[]) {
    double res = 0.0;
    double fraction = 0.1;
    int exponent = 0;
	double c = 0;
    int sign = 1;
    int expSign = 1;
	int cSign = 1;
    int i = 0, j;
    int hasFraction = 0;
    int hasExponent = 0;
	int hasC = 0;
    
    while (str[i] == ' ') {
        i++;
    }
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') i++;
    
    while ((str[i] >= '0') && (str[i] <= '9')) {
        res = res * 10.0 + (str[i] - '0');
        i++;
    }
    
    if (str[i] == '.') {
        hasFraction = 1;
        i++;
        while ((str[i] >= '0') && (str[i] <= '9')) {
            res += (str[i] - '0') * fraction;
            fraction *= 0.1;
            i++;
        }
    }
    
    if ((str[i] == 'e') || (str[i] == 'E')) {
        hasExponent = 1;
        i++;
        
        if (str[i] == '-') {
            expSign = -1;
            i++;
        } else if (str[i] == '+') {
            i++;
        }

        while ((str[i] >= '0') && (str[i] <= '9')) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }
    }
	else if ((str[i] == 'c') || (str[i] == 'C')) {
		hasC = 1;
		++i;
		if (str[i] == '-') {
			cSign = -1;
			i++;
		}	else if (str[i] == '+') i++;
		while ((str[i] >= '0') && (str[i] <= '9')){
			c = c * 10 + (str[i] - '0');
			++i;
		}
	}

    if (hasExponent) {
        if (expSign > 0) {
            for (j = 0; j < exponent; j++) {
                res *= 10.0;
            }
        } else {
            for (j = 0; j < exponent; j++) {
                res /= 10.0;
            }
        }
    }
	if (hasC) {
		double copyRes = res;
		if (cSign > 0) {
			for (j = 0; j < copyRes; j++) {
				c *= 10.0;
			}
		} else {
			for (j = 0; j < copyRes; j++) {
				c /= 10.0;
			}
		}
		res = c;
	}
    return sign * res;
}

int main() {
    char str[100];
    
    while (scanf("%99s", str) != EOF) {
        double number = str2double(str);
        printf("%.10g\n", number);
    }
    
    return 0;
}	
