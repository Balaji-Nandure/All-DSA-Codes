/*
 * Problem: Fibonacci Number
 *
 * LeetCode 509: Fibonacci Number
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/nth-fibonacci-number/0
 *
 * Calculate nth Fibonacci number: F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
 *
 * Approaches:
 * 1. Recursive: O(2^n) time, O(n) space
 * 2. Memoization: O(n) time, O(n) space
 * 3. Tabulation: O(n) time, O(n) space
 * 4. Space Optimized: O(n) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

// Approach 1: Recursive (inefficient - exponential time)
int fibonacci(int n){
    // Base cases: F(0)=0, F(1)=1
    if(n <= 1) return n;
    // Recursive relation: F(n) = F(n-1) + F(n-2)
    return fibonacci(n-1) + fibonacci(n-2);
}

// Approach 2: Memoization (Top-down DP)
int fibonacciMemoization(int n, vector<int> &dp){
    // Base cases
    if(n <= 1) return n;
    // If already computed, return stored value
    if(dp[n] != -1) return dp[n];
    // Compute and store result
    return dp[n] = fibonacciMemoization(n-1, dp) + fibonacciMemoization(n-2, dp);
}

// Approach 3: Tabulation (Bottom-up DP)
int fibonacciTabulation(int n){
    vector<int> dp(n+1, -1);
    // Base cases
    dp[0] = 0;
    dp[1] = 1;
    // Fill dp array from bottom to top
    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// Approach 4: Space Optimization (only need last 2 values)
int fibonacciSpaceOptimization(int n){
    // Only track previous two values
    int prev2 = 0; // F(0)
    int prev1 = 1; // F(1)
    int curr = 0;
    for(int i = 2; i <= n; i++){
        curr = prev1 + prev2; // F(i) = F(i-1) + F(i-2)
        prev2 = prev1; // Update for next iteration
        prev1 = curr;
    }
    return prev1; // F(n)
}

signed main() {
    int n = 10;
    int recursive = fibonacci(n);

    vector<int> dp1(n+1, -1);
    int memoization = fibonacciMemoization(n, dp1);

    int tabulation = fibonacciTabulation(n);
    int spaceOptimization = fibonacciSpaceOptimization(n);

    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
}