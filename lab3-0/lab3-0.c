#include <stdio.h>
#include <stdlib.h>


void heapify(int *arr, const int n, const int i)
{
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && largest < n && arr[l] > arr[largest])
      largest = l;

  if (r < n && largest < n && arr[r] > arr[largest])
      largest = r;

  if (largest != i) {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;

      heapify(arr, n, largest);
  }
}


void heapSort(int *arr, const int n)
{
  for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);

  for (int i = n - 1; i > 0; i--) {
      int temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;

      heapify(arr, i, 0);
  }
}


int is_sorted(const int *arr, const int N)
{
  for (int i = 0; i < N - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        return 0;
      }
  }
  return 1;
}


int main(void)
{
    int N;
    if (scanf("%i", &N) == 0)
        return 0;

    int *arr = malloc(N * sizeof(int));
    if (arr == NULL){
        free(arr);
        return 0;
    }

    for(int i = 0; i < N; ++i) {
        if (scanf("%i", &arr[i]) == 0)
            return 0;
    }

    if (!is_sorted(arr, N)){
        heapSort(arr, N);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    
    return 0;
}
