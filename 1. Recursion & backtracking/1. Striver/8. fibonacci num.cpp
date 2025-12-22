/*
 * Problem: Fibonacci Number
 *
 * Calculate nth Fibonacci number using recursion.
 * Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, ...
 * F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
 *
 * Note: This is inefficient (exponential time) due to repeated calculations.
 * Better approach: Use memoization or dynamic programming.
 *
 * Time: O(2^n) - exponential due to overlapping subproblems
 * Space: O(n) - recursion stack depth is n
 */

// Multiple recursive calls example
#include <bits/stdc++.h>
using namespace std;

int fib_counter = 0;

int fibonacci(int n) {
    fib_counter++; // Track number of function calls
    // Base cases: F(0) = 0, F(1) = 1
    if (n <= 1) return n;
    // Recursive case: F(n) = F(n-1) + F(n-2)
    // Two recursive calls - this causes exponential time complexity
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n = 1000;
    cout << fibonacci(n) << endl;
    cout << "count: " << fib_counter << endl;
    return 0;
}