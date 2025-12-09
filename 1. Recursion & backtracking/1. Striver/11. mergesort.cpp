#include <bits/stdc++.h>
using namespace std;


// Merge function to merge two sorted halves of arr[l..m] and arr[m+1..r]
// this will merge in ascending order.
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; // size of left
    int n2 = r - m;     // size of right

    vector<int> left(n1), right(n2);

    // Copy data because we are not allowed to change the original array.
    for (int i = 0; i < n1; ++i)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    // Merge the temp arrays back into arr[l..r]
    while (i < n1 && j < n2) {
        // if (left[i] >= right[j])   // descending order
        // if (left[i] <= right[j])   // ascending order
        if (left[i] <= right[j]) 
            arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    // Copy the remaining elements
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

// Merge Sort function
void mergeSort(vector<int>& arr, int l, int r) {
    // base vase
    if (l >= r) return;

    int m = l + (r - l) / 2;
    // Sort left half first
    mergeSort(arr, l, m);
    // then sort right half
    mergeSort(arr, m + 1, r);

    // Now merge both the halves
    merge(arr, l, m, r);
}

int main() {
    vector<int> arr = {5, 4, 1, 3, 2};
    int n = arr.size();

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
