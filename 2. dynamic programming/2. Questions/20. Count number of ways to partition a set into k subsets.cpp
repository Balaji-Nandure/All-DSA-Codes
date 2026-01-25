#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Count number of ways to partition a set into k subsets
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/count-number-of-ways-to-partition-a-set-into-k-subsets/1
LeetCode: N/A (Classic DP problem)

Given two numbers n and k where n represents number of elements in a set, find the number 
of ways to partition the set into k non-empty subsets.

Constraints:
- 1 <= n <= 20
- 1 <= k <= n

Example:
n = 3, k = 2
Output: 3
Explanation:
Set = {1, 2, 3}
Partition 1: {1, 2}, {3}
Partition 2: {1, 3}, {2}
Partition 3: {2, 3}, {1}

Key Insight:
- For n elements and k subsets, consider the nth element:
  1. Add to existing subset: can go into any of k existing subsets → k * dp[n-1][k]
  2. Form new subset: creates a new subset → dp[n-1][k-1]
- This is similar to Stirling numbers of the second kind

DP State:
- dp[i][j] = number of ways to partition i elements into j non-empty subsets

Recurrence Relation:
- dp[i][j] = j * dp[i-1][j] + dp[i-1][j-1]
  - j * dp[i-1][j]: ith element goes into any of j existing subsets
  - dp[i-1][j-1]: ith element forms a new subset

Base Cases:
- dp[0][0] = 1 (empty set, 0 subsets - one way: do nothing)
- dp[i][0] = 0 for i > 0 (can't partition into 0 subsets)
- dp[0][j] = 0 for j > 0 (can't partition empty set into j subsets)
- dp[i][1] = 1 (all elements in one subset)
- dp[i][i] = 1 (each element in its own subset)

Time Complexity: O(n * k)
Space Complexity: O(n * k) for tabulation, O(k) for space optimized
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int n, int k) {
        // Base cases
        if (n == 0 && k == 0) return 1; // Empty set, 0 subsets
        if (n == 0 || k == 0) return 0; // Invalid cases
        if (k == 1) return 1; // All elements in one subset
        if (n == k) return 1; // Each element in its own subset
        if (n < k) return 0; // Can't partition into more subsets than elements
        
        // Option 1: nth element goes into any of k existing subsets
        int existing = k * solve(n - 1, k);
        // Option 2: nth element forms a new subset
        int newSubset = solve(n - 1, k - 1);
        
        return existing + newSubset;
    }
    
    int countWays(int n, int k) {
        return solve(n, k);
    }
};


// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n * k), SC: O(n * k) for dp + O(n) recursion stack
    int solve(int n, int k, vector<vector<int>>& dp) {
        if (n == 0 && k == 0) return 1;
        if (n == 0 || k == 0) return 0;
        if (k == 1 || n == k) return 1;
        if (n < k) return 0;
        
        if (dp[n][k] != -1) return dp[n][k];
        
        // Add to existing subset or form new subset
        return dp[n][k] = k * solve(n - 1, k, dp) + solve(n - 1, k - 1, dp);
    }
    
    int countWays(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
        return solve(n, k, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n * k), SC: O(n * k) for dp array
    int countWays(int n, int k) {
        if (n < k) return 0;
        if (k == 0) return (n == 0) ? 1 : 0;
        
        // dp[i][j] = number of ways to partition i elements into j subsets
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        // Base cases
        dp[0][0] = 1; // Empty set, 0 subsets
        
        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                if (j == 1) {
                    dp[i][j] = 1; // All elements in one subset
                } else if (i == j) {
                    dp[i][j] = 1; // Each element in its own subset
                } else {
                    // Add to existing subset or form new subset
                    dp[i][j] = j * dp[i - 1][j] + dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[n][k];
    }
};

// Approach 4: Space Optimization (O(k) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(n * k), SC: O(k) - only track previous row
    int countWays(int n, int k) {
        if (n < k) return 0;
        if (k == 0) return (n == 0) ? 1 : 0;
        
        // prev[j] = ways to partition previous i-1 elements into j subsets
        vector<int> prev(k + 1, 0);
        prev[0] = 1; // Base case: dp[0][0] = 1
        
        for (int i = 1; i <= n; i++) {
            vector<int> curr(k + 1, 0);
            
            for (int j = 1; j <= min(i, k); j++) {
                if (j == 1) {
                    curr[j] = 1; // All elements in one subset
                } else if (i == j) {
                    curr[j] = 1; // Each element in its own subset
                } else {
                    // Add to existing subset or form new subset
                    curr[j] = j * prev[j] + prev[j - 1];
                }
            }
            
            prev = curr; // Update for next iteration
        }
        
        return prev[k];
    }
};
