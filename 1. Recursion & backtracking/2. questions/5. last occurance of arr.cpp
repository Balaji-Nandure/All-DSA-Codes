/*
 * Problem: Last Index of Occurrence
 *
 * Find the last index where element x occurs in array using recursion.
 * Return -1 if element is not found.
 *
 * Key difference from firstIndex:
 * - firstIndex: checks current index first, then recurses (left-to-right)
 * - lastIndex: recurses first, then checks current (right-to-left, finds last match)
 *
 * Time: O(n) - worst case visit all elements
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Find last index of x in array
int lastIndex(int arr[], int n, int idx, int x) {
    // Base case: reached end of array
    if (idx == n) return -1;
    
    // First recurse to end (explore deeper first)
    // This ensures we check from right to left
    int res = lastIndex(arr, n, idx + 1, x);

    // If found in further recursion, return that index (last match)
    if (res != -1) return res;

    // If not found in rest, check current element
    if (arr[idx] == x) return idx;

    // Not found anywhere
    return -1;
}

int main() {
    int arr[] = {15, 11, 40, 4, 4, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    cout << lastIndex(arr, n, 0, x) << endl; // Output should be 4
    return 0;
}
