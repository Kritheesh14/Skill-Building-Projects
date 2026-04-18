/* 
  Algorithm based on merge sort			

1)Split array into two halves, recursively count inversions in each half, then count cross-inversions during merge.
2)Core structure mirrors merge sort; inversion counting is embedded.
3)Decompose: split array into two halves until single elements. 
  Conquer: recursively count inversions in left and right halves. 
  Combine: count cross-inversions while merging sorted halves. 
4)Logical flow:
5)Left inversions: within left subarray 
  Right inversions: within right subarray 
  Cross inversions: between left and right during merge 
  [Total = left + right + cross]
  
*/
  
#include <stdio.h>
#include <stdlib.h>

int mergecount(int A[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int invcount = 0;

    while (i <= mid && j <= right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
            invcount += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = A[i++];
    }

    while (j <= right) {
        temp[k++] = A[j++];
    } q

    for (int x = left; x <= right; x++) {
        A[x] = temp[x];
    }

    return invcount;
}

int invcount(int A[], int temp[], int left, int right) {
    int invcount = 0;

    if (left < right) {
        int mid = (left + right) / 2;

        invcount += invcount(A, temp, left, mid);
        invcount += invcount(A, temp, mid + 1, right);
        invcount += mergecount(A, temp, left, mid, right);
    }

    return invcount;
}

int main() {
    int A[] = {2, 4, 1, 3, 5};
    int n = sizeof(A) / sizeof(A[0]);

    int *temp = (int *)malloc(n * sizeof(int));

    int result = invcount(A, temp, 0, n - 1);

    printf("Number of inversions: %d\n", result);
    for(int i=0;i<5;i++)
    printf(" %d, ",A[i]);
    printf("\n");
    for(int i=0;i<5;i++)
    printf(" %d, ",temp[i]);

    free(temp);
    return 0;
}
