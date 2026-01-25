#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Friends Pairing Problem
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/friends-pairing-problem5425/1
LeetCode: N/A (Classic DP problem)

Given n friends, each friend can remain single or can be paired up with some other friend. 
Each friend can be paired only once. Find out the total number of ways in which friends 
can remain single or can be paired up.

Constraints:
- 1 <= n <= 10^4

Example:
n = 3
Output: 4
Explanation:
Way 1: All 3 friends remain single: {1}, {2}, {3}
Way 2: Friend 1 pairs with friend 2, friend 3 single: {1,2}, {3}
Way 3: Friend 1 pairs with friend 3, friend 2 single: {1,3}, {2}
Way 4: Friend 2 pairs with friend 3, friend 1 single: {2,3}, {1}

Key Insight:
- For n friends, consider the nth friend:
  1. Stay single: remaining (n-1) friends can be paired in dp[n-1] ways
  2. Pair up: can pair with any of the (n-1) remaining friends
     - After pairing, (n-2) friends remain → dp[n-2] ways
     - Total: (n-1) * dp[n-2] ways

DP State:
- dp[i] = number of ways to pair i friends

Recurrence Relation:
- dp[i] = dp[i-1] + (i-1) * dp[i-2]
  - dp[i-1]: ith friend stays single
  - (i-1) * dp[i-2]: ith friend pairs with any of (i-1) friends

Base Cases:
- dp[0] = 1 (no friends, one way - do nothing)
- dp[1] = 1 (one friend stays single)
- dp[2] = 2 (both single OR pair up)

Time Complexity: O(n)
Space Complexity: O(n) for tabulation, O(1) for space optimized
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int n) {
        // Base cases
        if (n == 0) return 1;  // No friends, one way
        if (n == 1) return 1; // One friend stays single
        if (n == 2) return 2; // Both single OR pair up
        
        // Option 1: nth friend stays single
        int single = solve(n - 1);
        // Option 2: nth friend pairs with any of (n-1) friends
        int pair = (n - 1) * solve(n - 2);
        
        return single + pair;
    }
    
    int countFriendsPairings(int n) {
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
        
        // Stay single or pair up
        return dp[n] = (solve(n - 1, dp) + (n - 1) * solve(n - 2, dp)) % MOD;
    }
    
    int countFriendsPairings(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    int countFriendsPairings(int n) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        // dp[i] = number of ways to pair i friends
        vector<int> dp(n + 1, 0);
        
        // Base cases
        dp[0] = 1; // No friends
        dp[1] = 1; // One friend stays single
        dp[2] = 2; // Both single OR pair up
        
        // Fill DP table
        for (int i = 3; i <= n; i++) {
            // Stay single or pair with any of (i-1) friends
            dp[i] = (dp[i - 1] + (i - 1) * dp[i - 2]) % MOD;
        }
        
        return dp[n];
    }
};

// Approach 4: Space Optimization (O(1) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(n), SC: O(1) - only track previous two values
    int countFriendsPairings(int n) {
        if (n <= 1) return 1;
        if (n == 2) return 2;
        
        // Track previous two values
        int prev2 = 1; // dp[1]
        int prev1 = 2; // dp[2]
        
        for (int i = 3; i <= n; i++) {
            // dp[i] = dp[i-1] + (i-1) * dp[i-2]
            int curr = (prev1 + (i - 1) * prev2) % MOD;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};
