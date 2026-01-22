#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Burst Balloons
LeetCode 312: https://leetcode.com/problems/burst-balloons/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/burst-balloons/1

You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number 
on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. 
If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon 
with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

Constraints:
- n == nums.length
- 1 <= n <= 300
- 0 <= nums[i] <= 100

Example:
nums = [3,1,5,8]
Optimal: Burst in order 1, 5, 3, 8
Coins = 3*1*5 + 3*5*8 + 1*3*8 + 1*8*1 = 15 + 120 + 24 + 8 = 167

Key Insight:
- This is similar to Matrix Chain Multiplication (range DP problem)
- Think backwards: which balloon should be the LAST one to burst in a range?
- Add 1 at the beginning and end to handle boundaries
- dp[i][j] = maximum coins from bursting all balloons from i to j (inclusive)
- For each k in [i, j], assume k is the LAST balloon to burst in this range
- When k is last, coins = nums[i-1] * nums[k] * nums[j+1]
- Then solve left part [i, k-1] and right part [k+1, j]

DP State: dp[i][j] = maximum coins from bursting all balloons from index i to j (inclusive)
where nums array has 1 added at the beginning and end

Recurrence:
- dp[i][j] = max(dp[i][k-1] + dp[k+1][j] + nums[i-1] * nums[k] * nums[j+1]) for all k from i to j
- For each k, assume k is the LAST balloon to burst in range [i, j]
- Coins from bursting k last = nums[i-1] * nums[k] * nums[j+1] (neighbors are i-1 and j+1)
- Then add coins from left part [i, k-1] and right part [k+1, j]

Base Cases:
- dp[i][j] = 0 for i > j (empty range, no balloons)
- dp[i][i] = nums[i-1] * nums[i] * nums[i+1] (single balloon)

Time Complexity: O(n^3) where n is the number of balloons
Space Complexity: O(n^2) for dp array

Note: We add 1 at the beginning and end to handle boundary cases.
*/

// 1. Recursive approach
class BurstBalloonsRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int i, int j, vector<int>& nums) {
        // Base case: empty range
        if (i > j) return 0;
        
        int maxCoins = 0;
        
        // Try each balloon as the LAST one to burst in range [i, j]
        for (int k = i; k <= j; k++) {
            // Coins from bursting k last = nums[i-1] * nums[k] * nums[j+1]
            int coins = nums[i - 1] * nums[k] * nums[j + 1];
            // Add coins from left and right parts
            coins += solve(i, k - 1, nums) + solve(k + 1, j, nums);
            maxCoins = max(maxCoins, coins);
        }
        
        return maxCoins;
    }
    
    int maxCoins(vector<int>& nums) {
        // Add 1 at the beginning and end
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        
        int n = nums.size();
        // Solve for range [1, n-2] (excluding the added 1s at ends)
        return solve(1, n - 2, nums);
    }
};

// 2. Memoization (Top-down DP)
class BurstBalloonsMemoization {
public:
    // TC: O(n^3), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int i, int j, vector<int>& nums, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int maxCoins = 0;
        
        for (int k = i; k <= j; k++) {
            int coins = nums[i - 1] * nums[k] * nums[j + 1];
            coins += solve(i, k - 1, nums, dp) + solve(k + 1, j, nums, dp);
            maxCoins = max(maxCoins, coins);
        }
        
        return dp[i][j] = maxCoins;
    }
    
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(1, n - 2, nums, dp);
    }
};
