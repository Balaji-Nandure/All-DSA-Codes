/*
 * Problem: Print 1 to N
 *
 * Print numbers from 1 to N in ascending order using recursion.
 *
 * Time: O(n) - we make n recursive calls
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

void f(int n){
    // Base case: when n becomes 0, stop recursion
    if(n == 0) return;
    // First, recursively print 1 to n-1
    // This ensures smaller numbers are printed first
    f(n - 1);
    // Then print n (after recursive call)
    // This gives us ascending order: 1, 2, 3, ..., n
    cout << n << endl;
}

signed main() {
    int n = 5;
    f(n);
    return 0;
}