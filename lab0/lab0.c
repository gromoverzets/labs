#include <math.h>
#include <stdio.h>
#include <string.h>


// Функция для перевода числа из десятичной системы счисления в другую
void decimalToAnother(double decimal, int base, char *result) {
    long long wholePart = (long long)decimal;
    double fractionalPart = decimal - wholePart;

    // Перевод целой части
    int i = 0;
    while (wholePart > 0) {
        int digit = wholePart % base;
        if (digit < 10) {
            result[i++] = '0' + digit;
        } else {
            result[i++] = 'a' + (digit - 10);
        }
        wholePart /= base;
    }

    // Перевод целой части в обратном порядке
    int j = 0;
    int k = i - 1;
    while (j < k) {
        char temp = result[j];
        result[j] = result[k];
        result[k] = temp;
        j++;
        k--;
    }

    // Перевод дробной части
    if (fractionalPart > 0) {
        result[i++] = '.';
        for (int j = 0; j < 14; j++) { // Ограничение на 12 знаков после запятой
            fractionalPart *= base;
            int digit = (int)fractionalPart;
            if (digit < 10) {
                result[i++] = '0' + digit;
            } else {
                result[i++] = 'a' + (digit - 10);
            }
            fractionalPart -= digit;
        }
    }

    // Удаление лишних нулей
	int iDot = -1;
	for (int i = 0; result[i] != '\0'; ++i){
		if (result[i] == '.'){
			iDot = i;
			break;
		}
	}
	if (iDot != -1){
		result[iDot + 14] = '\0';
		for (int i = iDot + 12;; --i){
			if (result[i] == '0')
				result[i] = '\0';
			else
				break;
		}
		// если после точки ничего
		if (result[iDot + 1] == '\0')
			result [iDot] = '\0';
	}
	//сдвиг вправо на 1 знак
    if (iDot == 0) {
		for (int i = 13; i > 0; --i){
			result[i] = result[i - 1];
		}
		result[0] = '0';
    }
	if (result[1] == '\0'){
		result[1] = '.';
		result[2] = '0';
	}
}

// Функция для перевода числа из одной системы счисления в другую
void convertNumber(double a, int b, char *s, char *outputNumber) {
    // 1. Перевод числа из исходной системы счисления в десятичную
    double decimalNumber = 0;
    int iDot = -1;
    int len = strlen(s);

    for (int i = 0; i < len; ++i) {
        if (s[i] == '.') {
            iDot = i;
            break;
        }
    }

    // Перевод целой части
	long long digit;
    if (iDot != -1) {
        for (int i = 0; i < iDot; ++i) {
			digit = (('0' <= s[iDot - 1 - i]) && (s[iDot - 1 - i] <= '9'))? s[iDot - 1 - i] - '0' : s[iDot - 1 - i] + 10 - 'a';
            decimalNumber += digit * pow(a, i);
        }
    } else {
        for (int i = 0; i < len; ++i) {
			digit = (('0' <= s[len - 1 - i]) && (s[len - 1 - i] <= '9'))? s[len - 1 - i] - '0' : s[len - 1 - i] + 10 - 'a';
            decimalNumber += digit * pow(a, i);
        }
    }

    // Перевод дробной части
    if (iDot != -1) {
		s[iDot] = '.';
        double fractionalPart = 0;
        double multiplier = 1 / a;
        for (int i = iDot + 1; i < len; ++i) {
			digit = (('0' <= s[i]) && (s[i] <= '9'))? s[i] - '0' : s[i] + 10 - 'a';
            fractionalPart += digit * multiplier;
            multiplier /= a;
        }
        decimalNumber += fractionalPart;
    }

    // 2. Перевод числа из десятичной системы счисления в целевую
    decimalToAnother(decimalNumber, b, outputNumber);
}

int main() {
    int a, b;
    char s[14];
    char outputNumber[65];

    // Ввод данных
    if (scanf("%d %d", &a, &b) == 0)
		return 0;
    if (scanf("%13s\n", s) == 0)
		return 0;
	int lenStr = strlen(s);


    // проверка основания
    if (a < 2 || a > 16 || b < 2 || b > 16) {
		printf("bad input");
		return 0;
    }
	if (lenStr == 1 && s[0] == '0'){
		printf("0");
		return 0;
	}
    // проверка числа
    int digitNow, iDot = -1;
    for (int i = 0; i < lenStr; ++i) {
		if ('A' <= s[i] && s[i] <= 'F')
			s[i] = s[i] - 'A' + 'a';
		if (('0' <= s[i] && s[i] <= '9') || ('a' <= s[i] && s[i] <= 'f') || (s[i] == '.')){
			if (s[i] == '.')
				digitNow = -1;
			else if (s[i] <= '9')
				digitNow = s[i] - '0'; 
			else
				digitNow = s[i] - 'a' + 10;
			
			if (digitNow >= a){
				printf("bad input");
				return 0;
			}
		} else{
			printf("bad input");
			return 0;
		}
		
        if (s[i] == '.' && (i == 0 || iDot != -1)) {
            printf("bad input");
            return 0;
        } else if (i == lenStr - 1 && s[i] == '.'){
			printf("bad input");
        	return 0;
		} else if (s[i] == '.')
				iDot = i;
    }
	
	
    convertNumber(a, b, s, outputNumber);

    printf("%s", outputNumber);

    return 0;
}
