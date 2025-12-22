/*
 * Problem: First Index of Occurrence
 *
 * Find the first index where element x occurs in array using recursion.
 * Return -1 if element is not found.
 *
 * Time: O(n) - worst case visit all elements
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Find first index of x in array
int firstIndex(int arr[], int n, int idx, int x) {
    // Base case: reached end of array, element not found
    if (idx == n) return -1;

    // Check current index first (to find first occurrence)
    if (arr[idx] == x) return idx; // Found at current index

    // Search in remaining array
    return firstIndex(arr, n, idx + 1, x);
}

int main() {
    int arr[] = {15, 11, 40, 4, 4, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    cout << firstIndex(arr, n, 0, x) << endl;
    return 0;
}
