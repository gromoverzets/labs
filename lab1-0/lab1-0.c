#include <stdio.h>
#include <stdlib.h>


#define MAX_BUFF 250
#define MAX_PATTERN 18
#define MAX_SHIFT 250


void make_table_shifts(const unsigned char* pattern, int* shift_table, int ind_pattern) {
    for (size_t i = 0; i < MAX_SHIFT; ++i) {
        shift_table[i] = ind_pattern;
    }

    for (int i = 0; i < ind_pattern - 1; ++i) {
        shift_table[pattern[i]] = ind_pattern - i - 1;
    }
}


void change_buff(unsigned char* buff, int* buff_len, int ind_pattern, int now_str_ind, long long int* ind_shift, FILE* file) {
    for (int i = now_str_ind - ind_pattern + 1; i < *buff_len; ++i) {
        buff[i - now_str_ind + ind_pattern - 1] = buff[i];
    }

    int shift = *buff_len - now_str_ind + ind_pattern - 1;

    *ind_shift += MAX_BUFF - shift;
    *buff_len = fread(buff + shift, sizeof(unsigned char), MAX_BUFF - shift, file);
    *buff_len += shift;
}


void find(FILE* file) {
    if (!file)
        return;

    unsigned char pattern[MAX_PATTERN];

    if (fgets((char*)pattern, MAX_PATTERN, file) == NULL)
        return;
    
    int ind_pattern = 0;
    while (pattern[ind_pattern] != '\n' && pattern[ind_pattern] != '\0' && ind_pattern < MAX_PATTERN) {
        ++ind_pattern;
    }

    if (ind_pattern == 0)
        return;

    unsigned char* buff = malloc(sizeof(unsigned char) * MAX_BUFF);
    if (buff == NULL) {
        free(buff);
        return;
    }

    int buff_len = fread(buff, sizeof(unsigned char), MAX_BUFF, file);
    long long int ind_shift = 1;

    int now_str_ind = ind_pattern - 1;
    int shift_table[MAX_SHIFT];
    make_table_shifts(pattern, shift_table, ind_pattern);

    while (now_str_ind < buff_len) {
        int is_match = 0;
        for (int i = ind_pattern - 1; i >= 0; --i) {
            int ind = now_str_ind - ind_pattern + i + 1;
            printf("%lld ", ind + ind_shift);

            if (buff[ind] != pattern[i]) {
                is_match = 1;
                break;
            }
        }

        if (is_match == 0) {
            now_str_ind += ind_pattern;
        }
        else {
            now_str_ind += shift_table[buff[now_str_ind]];
        }

        if (now_str_ind >= buff_len - ind_pattern && buff_len == MAX_BUFF) {
            change_buff(buff, &buff_len, ind_pattern, now_str_ind, &ind_shift, file);
            now_str_ind = ind_pattern - 1;
        }

        if (now_str_ind > buff_len && buff_len < MAX_BUFF) {
            free(buff);
            return;
        }
    }
    free(buff);
}




int main(void) {
    FILE *file = fopen("in.txt", "r");
    find(file);
    fclose(file);

    return 0;
}
