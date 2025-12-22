/*
 * Problem: Sum of First N Natural Numbers
 *
 * Calculate the sum of first N natural numbers using recursion.
 * Formula: 1 + 2 + 3 + ... + n = n*(n+1)/2
 *
 * Time: O(n) - we make n recursive calls
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

int f(int n){
    // Base case: sum of 0 numbers is 0
    if(n == 0) return 0;
    // Recursive case: sum(n) = n + sum(n-1)
    // Add current n to the sum of first n-1 numbers
    return n + f(n - 1);
}

signed main() {
    int n = 5;
    int sum = f(n); // Returns the sum of first n numbers
    cout << "Sum of first " << n << " numbers is " << sum << endl;
    return 0;
}