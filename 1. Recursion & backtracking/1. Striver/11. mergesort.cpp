/*
 * Problem: Merge Sort
 *
 * Divide and conquer sorting algorithm.
 * Divide array into halves, sort each half, then merge them.
 *
 * Time: O(n log n) - always, stable performance
 * Space: O(n) - for temporary arrays during merge
 */

#include <bits/stdc++.h>
using namespace std;

// Merge two sorted subarrays arr[l..m] and arr[m+1..r] into one sorted array
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; // Size of left subarray
    int n2 = r - m;     // Size of right subarray

    vector<int> left(n1), right(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i)
        left[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        right[j] = arr[m + 1 + j];

    // Merge the two sorted arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        // Compare and place smaller element first (ascending order)
        // For descending: use left[i] >= right[j]
        if (left[i] <= right[j]) 
            arr[k++] = left[i++];
        else 
            arr[k++] = right[j++];
    }
    // Copy remaining elements from left subarray
    while (i < n1) arr[k++] = left[i++];
    // Copy remaining elements from right subarray
    while (j < n2) arr[k++] = right[j++];
}

// Merge Sort: Divide and conquer
void mergeSort(vector<int>& arr, int l, int r) {
    // Base case: single element or empty array is already sorted
    if (l >= r) return;

    // Find middle point to divide array
    int m = l + (r - l) / 2;
    // Recursively sort left half
    mergeSort(arr, l, m);
    // Recursively sort right half
    mergeSort(arr, m + 1, r);

    // Merge the two sorted halves
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
