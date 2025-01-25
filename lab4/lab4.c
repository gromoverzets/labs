#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1100

typedef enum {
    ERR_DIV_ZERO = -1,
    ERR_SYNTAX = -2
} ErrorCode;


int processTerm(char*, size_t*);


int processNumber(const char *expr, size_t *index) {
    int num = 0;
    size_t len = strlen(expr);

    if (*index >= len || !isdigit(expr[*index]))
        return ERR_SYNTAX;

    while (*index < len && isdigit(expr[*index])) {
        num = num * 10 + (expr[*index] - '0');
        (*index)++;
    }
    return num;
}


int isValidInput(const char *input) {
    size_t len = strlen(input);
    int isNum = 0;
    int isSpace = 1;

    for (size_t i = 0; i < len; ++i) {
        if (input[i] == ' ') {
            isSpace = 1;
            continue;
        }
        if (isNum && isSpace && isdigit(input[i]))
            return 0;
        isSpace = 0;
        isNum = isdigit(input[i]);
    }
    return 1;
}


int processFactor(char *expr, size_t *index) {
    int left = processTerm(expr, index);
    if (left == ERR_SYNTAX || left == ERR_DIV_ZERO)
        return left;
    size_t exprLen = strlen(expr);
    while (*index < exprLen && (expr[*index] == '*' || expr[*index] == '/')) {
        char op = expr[(*index)++];

        int right = processTerm(expr, index);

        if (right == ERR_SYNTAX || right == ERR_DIV_ZERO)
            return right;

        if (op == '*') left *= right; else if (right == 0)
            return ERR_DIV_ZERO;

        else left /= right;
    }
    return left;
}


int processExpression(char *expr, size_t *index, size_t exprLen) {
    int left = processFactor(expr, index);
    if (left == ERR_SYNTAX || left == ERR_DIV_ZERO)
        return left;

    while (*index < exprLen && (expr[*index] == '+' || expr[*index] == '-')) {
        char op = expr[*index];
        (*index)++;
        int right = processFactor(expr, index);
        if (right == ERR_SYNTAX || right == ERR_DIV_ZERO)
            return right;
        if (op == '+') left += right; else left -= right;
    }
    return left;
}


ErrorCode processTerm(char *expr, size_t *index) {
    int result;
    size_t exprLen = strlen(expr);
    if (*index >= exprLen)
        return ERR_SYNTAX;

    if (expr[*index] == '(') {
        (*index)++;
        result = processExpression(expr, index, exprLen);
        if (result == ERR_SYNTAX || result == ERR_DIV_ZERO)
            return result;
        if (*index >= exprLen || expr[*index] != ')')
            return ERR_SYNTAX;
        (*index)++;
    } else {
        result = processNumber(expr, index);
        if (result == ERR_SYNTAX)
            return ERR_SYNTAX;
    }
    return result;
}


int main() {
    char input[MAX_LEN], cleanInput[MAX_LEN];
    size_t pos = 0;

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 0;

    input[strcspn(input, "\n")] = 0;
    size_t j = 0, len = strlen(input);

    if (!isValidInput(input)) {
        printf("syntax error");
        return 0;
    }

    for (size_t i = 0; i < len; ++i){
        if (input[i] != ' ')
            cleanInput[j++] = input[i];
    }
    cleanInput[j] = '\0';

    int result = processExpression(cleanInput, &pos, strlen(cleanInput));

    if (result == ERR_SYNTAX)
        printf("syntax error");
    else if (result == ERR_DIV_ZERO)
        printf("division by zero");
    else if (pos != strlen(cleanInput))
        printf("syntax error");
    else
        printf("%d", result);

    return 0;
}
