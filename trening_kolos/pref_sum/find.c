#include <stdio.h>
#include <stdlib.h>

int find(int arr[], int size) {
    int l = 0; 
    int r = size - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (arr[m-1] > arr[m] && arr[m] < arr[m+1]) { // low point
            return m;
        } else if (m + 1 < size && arr[m-1] < arr[m] && arr[m] > arr[m+1]) { // high point
            return m+1;
        } else if (arr[m] < arr[m+1]) // goes up
            l = m + 1;
        else r = m;
    }
    return l;
}

int main () {
    int n = 8;
    //           0  1  2  3  4  5  6  7
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    printf("%d\n", find(arr, n));

    return 0;
}