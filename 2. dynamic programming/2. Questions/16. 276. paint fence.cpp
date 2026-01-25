#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Paint Fence
LeetCode 276: https://leetcode.com/problems/paint-fence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/paint-fence/1

You are painting a fence of n posts with k colors. You must paint the posts such that 
no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Constraints:
- 1 <= n <= 50
- 1 <= k <= 10^5

Example:
n = 3, k = 2
Output: 6
Explanation: 
Post 1: k choices (2)
Post 2: k choices (2) - total 4 ways
Post 3: 
  - If post 2 != post 1: k-1 choices (1) - 2 ways
  - If post 2 == post 1: k-1 choices (1) - 2 ways
Total: 2 + 2 + 2 = 6 ways

Key Insight:
- At most 2 consecutive posts can have the same color
- For each post, we track two states:
  * same: last two posts have same color
  * diff: last two posts have different colors

DP State:
- same[i] = number of ways to paint first i posts where post i and i-1 have same color
- diff[i] = number of ways to paint first i posts where post i and i-1 have different color

Recurrence Relation:
- same[i] = diff[i-1] 
  (can only have same color if previous was different, then choose same color)
- diff[i] = (same[i-1] + diff[i-1]) * (k-1)
  (can choose any color except the one used in previous post)

Base Cases:
- For n=1: same[1] = 0, diff[1] = k (first post can be any color)
- For n=2: same[2] = k, diff[2] = k*(k-1)

Time Complexity: O(n)
Space Complexity: O(n) for tabulation, O(1) for space optimized
*/


// Approach 1.0: Pure Recursion (for loop method)
class Solution1_Recursion_ForLoop {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int posts, int k, int prevColor, int consecutive) {
        if (posts == 0) return 1;
        
        int ways = 0;
        for (int color = 0; color < k; color++) {
            if (color == prevColor && consecutive < 2) {
                ways += solve(posts - 1, k, color, consecutive + 1);
            } else if (color != prevColor) {
                ways += solve(posts - 1, k, color, 1);
            }
        }
        return ways;
    }
    
    int numWays(int n, int k) {
        if (n == 0) return 0;
        return solve(n, k, -1, 0);
    }
};

// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n * k), SC: O(n * k) for dp + O(n) recursion stack
    int solve(int posts, int k, int prevColor, int consecutive, 
              map<tuple<int, int, int>, int>& dp) {
        if (posts == 0) return 1;
        
        tuple<int, int, int> key = {posts, prevColor, consecutive};
        if (dp.find(key) != dp.end()) return dp[key];
        
        int ways = 0;
        for (int color = 0; color < k; color++) {
            if (color == prevColor && consecutive < 2) {
                ways += solve(posts - 1, k, color, consecutive + 1, dp);
            } else if (color != prevColor) {
                ways += solve(posts - 1, k, color, 1, dp);
            }
        }
        
        return dp[key] = ways;
    }
    
    int numWays(int n, int k) {
        if (n == 0) return 0;
        map<tuple<int, int, int>, int> dp;
        return solve(n, k, -1, 0, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP) - State-based approach
class Solution3_Tabulation {
public:
    // TC: O(n), SC: O(n) for dp arrays
    int numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        
        // same[i] = ways where post i and i-1 have same color
        // diff[i] = ways where post i and i-1 have different color
        vector<int> same(n + 1, 0);
        vector<int> diff(n + 1, 0);
        
        // Base cases
        same[1] = 0;  // First post can't be same as previous (no previous)
        diff[1] = k;   // First post can be any color
        
        same[2] = k;           // Second post same as first: k choices
        diff[2] = k * (k - 1); // Second post different: k * (k-1) choices
        
        // Fill DP table
        for (int i = 3; i <= n; i++) {
            // Can only have same color if previous was different
            same[i] = diff[i - 1];
            // Can have different color from any previous state
            diff[i] = (same[i - 1] + diff[i - 1]) * (k - 1);
        }
        
        return same[n] + diff[n];
    }
};

// Approach 4: Space Optimization (O(1) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(n), SC: O(1) - only track previous two states
    int numWays(int n, int k) {
        if (n == 0) return 0;
        if (n == 1) return k;
        
        // Base cases for first two posts
        int same = k;           // Post 2 same as post 1
        int diff = k * (k - 1); // Post 2 different from post 1
        
        // For each subsequent post
        for (int i = 3; i <= n; i++) {
            int prevSame = same;
            int prevDiff = diff;
            
            // Update states
            same = prevDiff;                    // Same only if previous was different
            diff = (prevSame + prevDiff) * (k - 1); // Different from any previous
        }
        
        return same + diff;
    }
};
