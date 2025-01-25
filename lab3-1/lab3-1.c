#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b) {
    int t = *b;
    *b = *a;
    *a = t;
}


int separation(int *arr, const int l, const int r) {
    const int m = (l + r) / 2;
    int mid_el;

    if ((arr[l] <= arr[m] && arr[m] <= arr[r]) || (arr[r] <= arr[m] && arr[m] <= arr[l])) {
        mid_el = arr[m];
        swap(&arr[m], &arr[r]);
    } else if ((arr[m] <= arr[l] && arr[l] <= arr[r]) || (arr[r] <= arr[l] && arr[l] <= arr[m])) {
        mid_el = arr[l];
        swap(&arr[l], &arr[r]);
    } else {
        mid_el = arr[r];
    }

    int i = l;
    for (int j = l; j <= r; j++) {
        if (arr[j] < mid_el) {
            swap(&arr[i++], &arr[j]);
        }
    }
    swap(&arr[i], &arr[r]);  
    return i;
}


void quickSort(int *arr, const int l, const  int r) {
    if (l >= r)
        return;

    int m = separation(arr, l, r);
    if (m > 0)
        quickSort(arr, l, m - 1);
    if (m < r)
        quickSort(arr, m + 1, r);
}


int is_sorted(const int *arr, const int N) {
  for (int i = 0; i < N - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return 0;
    }
  }
  return 1;
}


int main() {
    int N;
    if (scanf("%i", &N) == 0)
        return 0;

    int *arr = malloc(N * sizeof(int));
    if (arr == NULL){
        free(arr);
        return 0;
    }

    for(int i = 0; i < N; ++i) {
        if (scanf("%i", &arr[i]) == 0){
            free(arr);
            return 0;
        }
    }

    if (!is_sorted(arr, N)){
        quickSort(arr, 0, N - 1);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    
    return 0;
}

