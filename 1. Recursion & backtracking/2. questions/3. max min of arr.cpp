/*
 * Problem: Find Maximum and Minimum in Array using Recursion
 *
 * Find maximum and minimum elements in an array using recursion.
 *
 * Time: O(n) - visit each element once
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Find maximum element recursively
int maxOfArray(int arr[], int n, int idx) {
    // Base case: last element is the max of single element
    if (idx == n - 1) return arr[idx];

    // Find maximum in remaining array
    int maxInRest = maxOfArray(arr, n, idx + 1);
    // Return maximum of current element and max of rest
    return max(arr[idx], maxInRest);
}

// Find minimum element recursively
int minOfArray(int arr[], int n, int idx) {
    // Base case: last element is the min of single element
    if (idx == n - 1) return arr[idx];

    // Find minimum in remaining array
    int minInRest = minOfArray(arr, n, idx + 1);
    // Return minimum of current element and min of rest
    return min(arr[idx], minInRest);
}

int main() {
    int arr[] = {2, 8, 1, 6, 0, 11, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxOfArray(arr, n, 0) << endl;
    return 0;
}
