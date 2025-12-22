/*
 * Problem: Factorial of a Number
 *
 * Calculate factorial of N using recursion.
 * Factorial(n) = n * (n-1) * (n-2) * ... * 1
 * Factorial(0) = 1 (by definition)
 *
 * Time: O(n) - we make n recursive calls
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

int factorial(int n) {
    // Base case: factorial of 0 is 1 (mathematical definition)
    if (n == 0) return 1;
    // Recursive case: factorial(n) = n * factorial(n-1)
    // Multiply current n with factorial of n-1
    return n * factorial(n - 1);
}

int main() {
    int n = 5;
    int ans = factorial(n);
    cout << "Factorial of " << n << " is " << ans << endl;
    return 0;
}