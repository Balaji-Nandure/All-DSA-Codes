#include <bits/stdc++.h>
using namespace std;

/**
 * PROBLEM: LeetCode 256 - Paint House
 * SUMMARY: There are n houses in a row, each can be painted with one of 3 colors (Red, Blue, Green).
 *          Costs[i][c] is the cost to paint house i with color c. No two adjacent houses can have the same color.
 *          Find the minimum cost to paint all houses.
 * 
 * DP STATE: dp[i][c] = Minimum cost to paint houses from 0 to i, where house i is painted with color c.
 * 
 * RECURRENCE: dp[i][c] = costs[i][c] + min(dp[i-1][c_other1], dp[i-1][c_other2])
 * 
 * BASE CASE: dp[0][c] = costs[0][c]
 * 
 * PLATFORM: https://leetcode.com/problems/paint-house/
 */

// Approach 1: Pure Recursion (Take/Not Take style logic)
// TC: O(3 * 2^(n-1)) -> O(2^n)
// SC: O(n) (Recursion Stack)
class Solution1 {
public:
    int solve(int i, int lastCol, vector<vector<int>>& costs) {
        if (i < 0) return 0; // Base case: no more houses
        
        int minCost = INT_MAX;
        for (int c = 0; c < 3; c++) {
            if (c != lastCol) { // Cannot pick same color as adjacent house
                minCost = min(minCost, costs[i][c] + solve(i - 1, c, costs));
            }
        }
        return minCost;
    }
    int minCost(vector<vector<int>>& costs) {
        return solve(costs.size() - 1, -1, costs);
    }
};

// Approach 2: Memoization
// TC: O(n * 3) -> O(n)
// SC: O(n * 3) + O(n) -> O(n)
class Solution2 {
public:
    int solve(int i, int lastCol, vector<vector<int>>& costs, vector<vector<int>>& dp) {
        if (i < 0) return 0;
        if (lastCol != -1 && dp[i][lastCol] != -1) return dp[i][lastCol];
        
        int minCost = INT_MAX;
        for (int c = 0; c < 3; c++) {
            if (c != lastCol) {
                minCost = min(minCost, costs[i][c] + solve(i - 1, c, costs, dp));
            }
        }
        if (lastCol != -1) dp[i][lastCol] = minCost;
        return minCost;
    }
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(3, -1));
        return solve(n - 1, -1, costs, dp);
    }
};

// Approach 3: Tabulation
// TC: O(n * 3) -> O(n)
// SC: O(n * 3) -> O(n)
class Solution3 {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        vector<vector<int>> dp(n, vector<int>(3));
        
        // Base case: first house
        dp[0] = costs[0];
        
        for (int i = 1; i < n; i++) {
            dp[i][0] = costs[i][0] + min(dp[i - 1][1], dp[i - 1][2]); // Min if house i is Red
            dp[i][1] = costs[i][1] + min(dp[i - 1][0], dp[i - 1][2]); // Min if house i is Green
            dp[i][2] = costs[i][2] + min(dp[i - 1][0], dp[i - 1][1]); // Min if house i is Blue
        }
        return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
    }
};

// Approach 4: Space Optimization
// TC: O(n)
// SC: O(1)
class Solution4 {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if (n == 0) return 0;
        
        // Only need costs of the previous house
        int r = costs[0][0], g = costs[0][1], b = costs[0][2];
        
        for (int i = 1; i < n; i++) {
            int nr = costs[i][0] + min(g, b); // New Red cost
            int ng = costs[i][1] + min(r, b); // New Green cost
            int nb = costs[i][2] + min(r, g); // New Blue cost
            r = nr; g = ng; b = nb; // Update for next house
        }
        return min({r, g, b});
    }
};
