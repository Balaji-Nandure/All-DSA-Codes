#include <bits/stdc++.h>
using namespace std;

// Recursive function to return the first index of occurrence of x in arr[]
int firstIndex(int arr[], int n, int idx, int x) {
    if (idx == n) return -1; // base case: reached end, not found

    // first check at current index
    if (arr[idx] == x) return idx; // found at current index

    // if not found, search in rest of array
    return firstIndex(arr, n, idx + 1, x);
}

int main() {
    int arr[] = {15, 11, 40, 4, 4, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    cout << firstIndex(arr, n, 0, x) << endl;
    return 0;
}
