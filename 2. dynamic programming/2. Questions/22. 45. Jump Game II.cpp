#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Jump Game II
LeetCode 45: https://leetcode.com/problems/jump-game-ii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1

You are given a 0-indexed array of integers nums of length n. You are initially positioned 
at nums[0]. Each element nums[i] represents the maximum jump length from position i.

Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated 
such that you can always reach nums[n - 1].

Constraints:
- 1 <= nums.length <= 10^4
- 0 <= nums[i] <= 1000

Example:
nums = [2,3,1,1,4]
Output: 2
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Key Insight:
- From index i, we can jump to any index from i+1 to i+nums[i]
- We want to minimize the number of jumps to reach the last index
- For each position, try all possible jumps and take the minimum

DP State:
- dp[i] = minimum number of jumps to reach index i from index 0

Recurrence Relation:
- For each index i, update all reachable positions j:
  dp[j] = min(dp[j], dp[i] + 1) for all j in [i+1, i+nums[i]]
- We iterate from left to right and update future positions

Base Cases:
- dp[0] = 0 (starting position, no jumps needed)
- dp[i] = INF initially for i > 0 (not reached yet)

Time Complexity: O(n^2) for DP approach
Space Complexity: O(n) for dp array
Note: Greedy approach can solve in O(n) time
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int idx, vector<int>& nums) {
        // Base case: reached last index
        if (idx >= nums.size() - 1) return 0;
        
        int minJumps = INF;
        // Try all possible jumps from current position
        for (int jump = 1; jump <= nums[idx]; jump++) {
            int nextIdx = idx + jump;
            if (nextIdx < nums.size()) {
                int jumps = 1 + solve(nextIdx, nums);
                minJumps = min(minJumps, jumps);
            }
        }
        
        return minJumps;
    }
    
    int jump(vector<int>& nums) {
        return solve(0, nums);
    }
};

// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n^2), SC: O(n) for dp + O(n) recursion stack
    int solve(int idx, vector<int>& nums, vector<int>& dp) {
        // Base case: reached last index
        if (idx >= nums.size() - 1) return 0;
        
        if (dp[idx] != -1) return dp[idx];
        
        int minJumps = INF;
        // Try all possible jumps from current position
        for (int jump = 1; jump <= nums[idx] && idx + jump < nums.size(); jump++) {
            int nextIdx = idx + jump;
            int jumps = 1 + solve(nextIdx, nums, dp);
            minJumps = min(minJumps, jumps);
        }
        
        return dp[idx] = minJumps;
    }
    
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        return solve(0, nums, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n^2), SC: O(n) for dp array
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        // dp[i] = minimum jumps to reach index i
        vector<int> dp(n, INF);
        dp[0] = 0; // Starting position
        
        // For each position, update all reachable positions
        for (int i = 0; i < n; i++) {
            // Update all positions reachable from i
            for (int jump = 1; jump <= nums[i] && i + jump < n; jump++) {
                int nextIdx = i + jump;
                dp[nextIdx] = min(dp[nextIdx], dp[i] + 1);
            }
        }
        
        return dp[n - 1];
    }
};

// Approach 4: Space Optimization (O(1) space with greedy)
// Note: This is actually a greedy approach, not space-optimized DP
class Solution4_SpaceOptimized {
public:
    // TC: O(n), SC: O(1) - greedy approach
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        int jumps = 0;
        int currentEnd = 0; // Current farthest position we can reach
        int farthest = 0;    // Farthest position we can reach
        
        for (int i = 0; i < n - 1; i++) {
            // Update farthest reachable position
            farthest = max(farthest, i + nums[i]);
            
            // If we've reached the end of current jump range
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                
                // Early exit if we can reach the end
                if (currentEnd >= n - 1) break;
            }
        }
        
        return jumps;
    }
};

// Approach 4.1: Alternative DP with early termination
class Solution {
public:
    // TC: O(n^2), SC: O(n) - optimized DP with early exit
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        vector<int> dp(n, INF);
        dp[0] = 0;
        
        for (int i = 0; i < n; i++) {
            // Early exit if we've already reached last index
            if (dp[n - 1] != INF) break;
            
            // Update all reachable positions
            for (int jump = 1; jump <= nums[i] && i + jump < n; jump++) {
                int nextIdx = i + jump;
                if (dp[i] != INF) {
                    dp[nextIdx] = min(dp[nextIdx], dp[i] + 1);
                }
            }
        }
        
        return dp[n - 1];
    }
};
