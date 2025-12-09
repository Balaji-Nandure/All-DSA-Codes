#include <bits/stdc++.h>
using namespace std;

// Recursive function to return the last index of occurrence of x in arr[]
// DIFFERENCE from 'first index of occurrence':
// - 'firstIndex' checks at the current idx first, then recursively goes forward (left-to-right).
// - 'lastIndex' FIRST DOES the recursion to the end and checks results while coming back (right-to-left).
//   Thus, lastIndex explores *deeper* first, preferring the last match on the return/backtracking phase.
int lastIndex(int arr[], int n, int idx, int x) {
    if (idx == n) return -1; // base case: reached end
    
    // Go to end first, looking for the match during the backtrack
    int res = lastIndex(arr, n, idx + 1, x);

    // If found in further recursion, return that index (the last match)
    if (res != -1) return res;

    // Else, check if current element matches
    if (arr[idx] == x) return idx;

    // Not found in rest or current location
    return -1;
}

int main() {
    int arr[] = {15, 11, 40, 4, 4, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    cout << lastIndex(arr, n, 0, x) << endl; // Output should be 4
    return 0;
}
