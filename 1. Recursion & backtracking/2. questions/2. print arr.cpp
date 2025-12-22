/*
 * Problem: Print Array using Recursion
 *
 * Print array elements in forward and reverse order using recursion.
 *
 * Time: O(n) - visit each element once
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Print array in forward order (left to right)
void printArr(int arr[], int n, int idx) {
    // Base case: reached end of array
    if (idx == n) return;
    // Print current element first
    cout << arr[idx] << endl;
    // Then print remaining elements
    printArr(arr, n, idx + 1);
}

// Print array in reverse order (right to left)
void printArrReverse(int arr[], int n, int idx) {
    // Base case: reached end of array
    if (idx == n) return;
    // First print remaining elements (recursive call)
    printArrReverse(arr, n, idx + 1);
    // Then print current element (after recursion returns)
    cout << arr[idx] << endl;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, n, 0);
    return 0;
}
