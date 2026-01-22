#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Minimum Cost to Cut the Stick
LeetCode 1547: https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/minimum-cost-to-cut-a-stick/1

Given a wooden stick of length n units. The stick is labelled from 0 to n.

Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.

You should perform the cuts in order, you can change the order of the cuts as you wish.

The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs 
of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum 
of their lengths is the length of the stick before the cut).

Return the minimum total cost of the cuts.

Constraints:
- 2 <= n <= 10^6
- 1 <= cuts.length <= min(n - 1, 100)
- 1 <= cuts[i] <= n - 1
- All the integers in cuts array are distinct

Example:
n = 7, cuts = [1, 3, 4, 5]
Optimal order: Cut at 3, then at 1, then at 4, then at 5
Total cost = 7 + 4 + 3 + 2 = 16

Key Insight:
- This is similar to Matrix Chain Multiplication (range DP problem)
- Push 0 and n into cuts, then sort it to represent the full stick
- dp[i][j] = minimum cost to cut the stick between cuts[i] and cuts[j]
- For each partition point k between i and j, try cutting at cuts[k]
- Cost = cost of left part + cost of right part + cost of current cut

DP State: dp[i][j] = minimum cost to cut the stick between cuts[i] and cuts[j]
where cuts array is sorted and includes 0 and n at the ends

Recurrence:
- dp[i][j] = min(dp[i][k] + dp[k][j] + cuts[j] - cuts[i]) for all k from i+1 to j-1
- For each cut position k, we split into [i..k] and [k..j]
- Cost of cutting at k = cuts[j] - cuts[i] (length of current stick segment)

Base Cases:
- dp[i][i+1] = 0 (no cuts between adjacent positions)
- dp[i][j] = INF for i >= j (invalid range)

Time Complexity: O(m^3) where m is the number of cuts (after adding 0 and n)
Space Complexity: O(m^2) for dp array

Note: We push 0 and n into cuts array, then sort it to handle the full stick properly.
*/

// 1. Recursive approach
class MinimumCostToCutStickRecursive {
public:
    // TC: O(2^m) exponential, SC: O(m) recursion stack
    int solve(int i, int j, vector<int>& cuts) {
        // Base case: no cuts between adjacent positions
        if (i + 1 >= j) return 0;
        
        int minCost = INF;
        
        // Try all possible cut positions between i and j
        for (int k = i + 1; k < j; k++) {
            // Cost = cost of left part + cost of right part + cost of current cut
            int cost = solve(i, k, cuts) + solve(k, j, cuts) + (cuts[j] - cuts[i]);
            minCost = min(minCost, cost);
        }
        
        return minCost;
    }
    
    int minCost(int n, vector<int>& cuts) {
        // Push 0 and n into cuts, then sort
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        
        // Solve for the entire stick (from index 0 to last index)
        return solve(0, cuts.size() - 1, cuts);
    }
};

// 2. Memoization (Top-down DP)
class MinimumCostToCutStickMemoization {
public:
    // TC: O(m^3), SC: O(m^2) for dp array + O(m) recursion stack
    int solve(int i, int j, vector<int>& cuts, vector<vector<int>>& dp) {
        if (i + 1 >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INF;
        
        for (int k = i + 1; k < j; k++) {
            int cost = solve(i, k, cuts, dp) + solve(k, j, cuts, dp) + (cuts[j] - cuts[i]);
            minCost = min(minCost, cost);
        }
        
        return dp[i][j] = minCost;
    }
    
    int minCost(int n, vector<int>& cuts) {
        // Push 0 and n into cuts, then sort
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        
        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        return solve(0, m - 1, cuts, dp);
    }
};
