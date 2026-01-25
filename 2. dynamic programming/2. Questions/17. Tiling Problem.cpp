#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Tiling Problem
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/ways-to-tile-a-floor5836/1
LeetCode: N/A (Similar to Fibonacci)

Given a floor of size n x 2 and tiles of size 2 x 1, count the number of ways to tile 
the given floor using the 2 x 1 tiles. A tile can either be placed horizontally or vertically.

Constraints:
- 1 <= n <= 70

Example:
n = 3
Output: 3
Explanation:
Way 1: All 3 tiles placed vertically
Way 2: First tile horizontal (covers 2x1), then 1 vertical tile
Way 3: Last tile horizontal (covers 2x1), then 1 vertical tile

Key Insight:
- For a 2 x n floor, we have two choices for the first column:
  1. Place one tile vertically: covers 2x1, remaining floor is 2x(n-1)
  2. Place two tiles horizontally: covers 2x2, remaining floor is 2x(n-2)
- This is exactly the Fibonacci sequence!

DP State:
- dp[i] = number of ways to tile a 2 x i floor

Recurrence Relation:
- dp[i] = dp[i-1] + dp[i-2]
  - dp[i-1]: place one vertical tile (covers 1 column)
  - dp[i-2]: place two horizontal tiles (covers 2 columns)

Base Cases:
- dp[0] = 1 (one way to tile empty floor - do nothing)
- dp[1] = 1 (one way - place one vertical tile)
- dp[2] = 2 (two ways - both vertical or both horizontal)

Time Complexity: O(n)
Space Complexity: O(n) for tabulation, O(1) for space optimized
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int n) {
        // Base cases
        if (n == 0) return 1;  // One way to tile empty floor
        if (n == 1) return 1; // One vertical tile
        if (n == 2) return 2; // Two vertical or two horizontal
        
        // Option 1: Place one vertical tile (covers 1 column)
        int vertical = solve(n - 1);
        // Option 2: Place two horizontal tiles (covers 2 columns)
        int horizontal = solve(n - 2);
        
        return vertical + horizontal;
    }
    
    int numberOfWays(int n) {
        return solve(n);
    }
};

// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n), SC: O(n) for dp + O(n) recursion stack
    int solve(int n, vector<int>& dp) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        if (dp[n] != -1) return dp[n];
        
        // Place vertical tile or horizontal tiles
        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }
    
    int numberOfWays(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    int numberOfWays(int n) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        // dp[i] = number of ways to tile 2 x i floor
        vector<int> dp(n + 1, 0);
        
        // Base cases
        dp[0] = 1; // Empty floor
        dp[1] = 1; // One vertical tile
        dp[2] = 2; // Two vertical or two horizontal
        
        // Fill DP table
        for (int i = 3; i <= n; i++) {
            // Place one vertical tile or two horizontal tiles
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        
        return dp[n];
    }
};

// Approach 4: Space Optimization (O(1) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(n), SC: O(1) - only track previous two values
    int numberOfWays(int n) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        // Track previous two values (Fibonacci-like)
        int prev2 = 1; // dp[1]
        int prev1 = 2; // dp[2]
        
        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};
