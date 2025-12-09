#include <bits/stdc++.h>
using namespace std;

// Recursive function to find the maximum element in an array
int maxOfArray(int arr[], int n, int idx) {
    if (idx == n - 1) return arr[idx]; // base case: last element

    int maxInRest = maxOfArray(arr, n, idx + 1);

    return max(arr[idx], maxInRest);
}

int minOfArray(int arr[], int n, int idx) {
    if (idx == n - 1) return arr[idx]; // base case: last element

    int minInRest = minOfArray(arr, n, idx + 1);
    return min(arr[idx], minInRest);
}

int main() {
    int arr[] = {2, 8, 1, 6, 0, 11, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << maxOfArray(arr, n, 0) << endl;
    return 0;
}
