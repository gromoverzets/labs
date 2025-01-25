#include <string.h>
#include <stdio.h>

#define MAX_LEN 15


void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}


int NextSet(char* text, int n)
{
    int j = n - 2;
    while (j != -1 && text[j] >= text[j + 1])
        j--;
    
    if (j == -1)
        return 0; // no more changes

    int k = n - 1;
    while (text[j] >= text[k])
        k--;

    swap(&text[j], &text[k]);

    int left, right;
    left = j + 1;
    right = n - 1;
    // sorting the rest of the sequence
    while (left < right)
        swap(&text[left++], &text[right--]);

    return 1;
}


int isCorrectInput(char *text, int n)
{
    for (int i = 0; i < n; ++i){
        if (text[i] < '0' || text[i] > '9')
            return 0;

        for (int j = 0; j < i; ++j){
            if (text[i] == text[j])
                return 0;
        }
    }
    return 1;
}


int main(void)
{
    char text[MAX_LEN];
    if (!fgets(text, MAX_LEN, stdin))
        return 0;

    for (int i = 0; i < MAX_LEN; ++i){
        if (text[i] == '\n'){
            text[i] = '\0';
            break;
        }
    }
    const int len = strlen(text);
        
    int n;
    if (scanf("%i", &n) == 0)
        return 0;

    if (!isCorrectInput(text, len)){
        puts("bad input");
        return 0;
    }

    int i = 0;
    while (i < n && NextSet(text, len)){
        ++i;
        puts(text);
    }

    return 0;
}