/*
 * Problem: Print N to 1
 *
 * Print numbers from N to 1 in descending order using recursion.
 *
 * Time: O(n) - we make n recursive calls
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

void f(int n){
    // Base case: when n becomes 0, stop recursion
    if(n == 0) return;
    // First print n (before recursive call)
    // This ensures larger numbers are printed first
    cout << n << endl;
    // Then recursively print n-1 to 1
    // This gives us descending order: n, n-1, n-2, ..., 1
    f(n - 1);
}

signed main() {
    int n = 5;
    f(n);
    return 0;
}
