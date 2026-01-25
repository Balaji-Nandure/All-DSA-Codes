#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Count the number of ways to tile the floor of size n x m using 1 x m size tiles
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/count-the-number-of-ways-to-tile-the-floor-of-size-n-x-m-using-1-x-m-size-tiles0509/1
LeetCode: N/A

Given a floor of size n x m and tiles of size 1 x m, count the number of ways to tile 
the given floor using the 1 x m tiles. A tile can be placed either horizontally or vertically.

Constraints:
- 1 <= n, m <= 1000

Example:
n = 2, m = 3
Output: 1
Explanation: 
- Floor is 2 rows × 3 columns
- Tiles are 1 × 3
- Only way: place 2 tiles horizontally (one per row)

n = 4, m = 4
Output: 2
Explanation:
- Floor is 4 rows × 4 columns  
- Tiles are 1 × 4
- Way 1: All 4 tiles placed horizontally (one per row)
- Way 2: All 4 tiles placed vertically (one per column)

Key Insight:
- For a floor of n rows × m columns with 1 × m tiles:
  - Horizontal placement: covers 1 row completely (m columns) → remaining: (n-1) rows
  - Vertical placement: covers m rows (1 column each) → remaining: (n-m) rows
- We need to consider both orientations

DP State:
- dp[i] = number of ways to tile a floor of i rows × m columns

Recurrence Relation:
- dp[i] = dp[i-1] + dp[i-m]
  - dp[i-1]: place one tile horizontally (covers 1 row)
  - dp[i-m]: place m tiles vertically (covers m rows, 1 column each)

Base Cases:
- dp[0] = 1 (one way to tile empty floor - do nothing)
- dp[i] = 1 for 1 <= i < m (only horizontal placement possible)
- dp[m] = 2 (one horizontal tile OR m vertical tiles)

Time Complexity: O(n)
Space Complexity: O(n) for tabulation, O(m) for space optimized
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int n, int m) {
        // Base cases
        if (n == 0) return 1;  // One way to tile empty floor
        if (n < m) return 1;   // Only horizontal placement possible
        
        // Option 1: Place one tile horizontally (covers 1 row)
        int horizontal = solve(n - 1, m);
        // Option 2: Place m tiles vertically (covers m rows)
        int vertical = solve(n - m, m);
        
        return horizontal + vertical;
    }
    
    int numberOfWays(int n, int m) {
        return solve(n, m);
    }
};

// Approach 1.0: Pure Recursion (for loop method)
class Solution1_Recursion_ForLoop {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int n, int m) {
        if (n == 0) return 1;
        if (n < m) return 1;
        
        return solve(n - 1, m) + solve(n - m, m);
    }
    
    int numberOfWays(int n, int m) {
        return solve(n, m);
    }
};

// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n), SC: O(n) for dp + O(n) recursion stack
    int solve(int n, int m, vector<int>& dp) {
        if (n == 0) return 1;
        if (n < m) return 1;
        
        if (dp[n] != -1) return dp[n];
        
        // Place horizontally or vertically
        return dp[n] = (solve(n - 1, m, dp) + solve(n - m, m, dp)) % MOD;
    }
    
    int numberOfWays(int n, int m) {
        vector<int> dp(n + 1, -1);
        return solve(n, m, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    int numberOfWays(int n, int m) {
        if (n == 0) return 1;
        if (n < m) return 1;
        
        // dp[i] = number of ways to tile i rows × m columns
        vector<int> dp(n + 1, 0);
        
        // Base cases
        dp[0] = 1; // Empty floor
        
        // For rows less than m, only horizontal placement
        for (int i = 1; i < m; i++) {
            dp[i] = 1;
        }
        
        // For row m, both horizontal and vertical possible
        if (m <= n) {
            dp[m] = 2; // One horizontal OR m vertical tiles
        }
        
        // Fill DP table
        for (int i = m + 1; i <= n; i++) {
            // Place one tile horizontally or m tiles vertically
            dp[i] = (dp[i - 1] + dp[i - m]) % MOD;
        }
        
        return dp[n];
    }
};

// Approach 4.1: Cleaner space-optimized solution
class Solution {
public:
    // TC: O(n), SC: O(m) - track last m values
    int numberOfWays(int n, int m) {
        if (n == 0) return 1;
        if (n < m) return 1;
        
        // dp[i] stores ways to tile i rows (using modulo for circular buffer)
        vector<int> dp(m, 0);
        dp[0] = 1; // Base: empty floor
        
        // Fill for rows 1 to n
        for (int i = 1; i <= n; i++) {
            if (i < m) {
                dp[i] = 1; // Only horizontal
            } else {
                // dp[i] = dp[i-1] + dp[i-m]
                // Use modulo indexing for circular buffer
                int idx = i % m;
                int prev1 = (i - 1) % m;
                int prevM = (i - m) % m;
                dp[idx] = (dp[prev1] + dp[prevM]) % MOD;
            }
        }
        
        return dp[n % m];
    }
};
