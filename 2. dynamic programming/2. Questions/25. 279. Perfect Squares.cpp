#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Perfect Squares
LeetCode 279: https://leetcode.com/problems/perfect-squares/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/get-minimum-squares0538/1

Given an integer n, return the least number of perfect square numbers that sum to n.
A perfect square is an integer that is the square of an integer.

Constraints:
- 1 <= n <= 10^4

Example:
n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4 (three perfect squares)

Key Insight:
- For any number n, we can express it as n = (n - j*j) + j*j
- We need to find minimum perfect squares for (n - j*j) and add 1
- Try all possible perfect squares j*j <= n and take minimum

DP State:
- dp[i] = minimum number of perfect squares that sum to i

Recurrence Relation:
- dp[i] = min(dp[i - j*j] + 1) for all j such that j*j <= i
- For each i, try subtracting all perfect squares and take minimum

Base Cases:
- dp[0] = 0 (0 perfect squares needed for 0)
- dp[1] = 1 (1 = 1^2)

Time Complexity: O(n * sqrt(n))
Space Complexity: O(n) for DP array
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(n^n) exponential, SC: O(n) recursion stack
    int solve(int n) {
        // Base case: n is 0
        if (n == 0) return 0;
        
        int minSquares = INF;
        
        // Try all perfect squares <= n
        for (int j = 1; j * j <= n; j++) {
            int squares = 1 + solve(n - j * j);
            minSquares = min(minSquares, squares);
        }
        
        return minSquares;
    }
    
    int numSquares(int n) {
        return solve(n);
    }
};

// Approach 2: Memoization
class Solution2_Memoization {
public:
    // TC: O(n * sqrt(n)), SC: O(n) for DP array + O(n) recursion stack
    int solve(int n, vector<int>& dp) {
        // Base case
        if (n == 0) return 0;
        
        // Check memo
        if (dp[n] != -1) return dp[n];
        
        int minSquares = INF;
        
        // Try all perfect squares <= n
        for (int j = 1; j * j <= n; j++) {
            minSquares = min(minSquares, 1 + solve(n - j * j, dp));
        }
        
        return dp[n] = minSquares;
    }
    
    int numSquares(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};

// Approach 3: Tabulation
class Solution3_Tabulation {
public:
    // TC: O(n * sqrt(n)), SC: O(n) for DP array
    int numSquares(int n) {
        vector<int> dp(n + 1, INF);
        dp[0] = 0; // Base case: 0 perfect squares for 0
        
        // Fill DP array from 1 to n
        for (int i = 1; i <= n; i++) {
            // Try all perfect squares <= i
            // Try every perfect square less than or equal to i
            for (int j = 1; j * j <= i; j++) {
                // Update dp[i] with the minimum number of squares
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        
        return dp[n];
    }
};
