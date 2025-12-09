#include <bits/stdc++.h>
using namespace std;

void printArr(int arr[], int n, int idx) {
    if (idx == n) return;
    cout << arr[idx] << endl;
    printArr(arr, n, idx + 1);
}

void printArrReverse(int arr[], int n, int idx) {
    if (idx == n) return;
    printArrReverse(arr, n, idx + 1);
    cout << arr[idx] << endl;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    printArr(arr, n, 0);
    return 0;
}
