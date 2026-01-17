#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Target Sum
LeetCode 494: https://leetcode.com/problems/target-sum/

You are given an integer array nums and an integer target. You want to build an expression 
out of nums by adding one of the symbols '+' and '-' before each integer in nums and then 
concatenate all the integers. Return the number of different expressions that you can build, 
which evaluates to target.



So, reduce this to: Count number of subsets with sum == S1, where S1 = (totalSum + target)/2
This is the same as "Count Partitions With Given Difference" problem.

Constraints:
- Each number can be assigned + or - sign
- Count number of ways to get target sum
- If (totalSum + target) is odd or totalSum < |target|, return 0

Example:
nums = [1, 1, 1, 1, 1], target = 3
S1 = (5 + 3)/2 = 4
Count subsets with sum 4: [1,1,1,1] -> 1 way
Answer = 1

DP State: dp[i][sum] = number of ways to achieve sum using first i elements
Recurrence:
dp[i][sum] = dp[i-1][sum] + dp[i-1][sum - nums[i-1]]
- dp[i-1][sum]: not pick nums[i-1] (assign - sign)
- dp[i-1][sum - nums[i-1]]: pick nums[i-1] (assign + sign, if sum >= nums[i-1])

Base Cases:
- dp[0][0] = 1 (one way: empty subset)
- dp[i][0] = 1 for all i (empty subset always sums to 0)

Time Complexity: O(n * target)
Space Complexity: O(n * target) for memoization/tabulation, O(target) for space optimization
*/


// Key Insight:
// Let S1 = sum of numbers with '+' sign
// Let S2 = sum of numbers with '-' sign
// We need: S1 - S2 = target
// But also: S1 + S2 = totalSum
// => 2*S1 = totalSum + target  => S1 = (totalSum + target)/2
// 1. Recursive approach (take/not take method)
class TargetSumRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int indx, vector<int>& nums, int sum) {
        // Base case: processed all elements
        if (indx == nums.size()) return sum == 0;
        
        // Pick (assign + sign) or not pick (assign - sign)
        int pick = solve(indx + 1, nums, sum - nums[indx]);
        int notPick = solve(indx + 1, nums, sum);
        
        return pick + notPick;
    }
    
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0LL);
        // Check if target is achievable
        if (totalSum < abs(target) || (totalSum + target) % 2 != 0) return 0;
        int s1 = (totalSum + target) / 2;
        return solve(0, nums, s1);
    }
};

// Yes, we can directly assign positive or negative to each element,
class TargetSumRecursiveAssignSigns {
public:
    // TC: O(2^n), SC: O(n) recursion stack
    int solve(int indx, int currentSum, const vector<int>& nums, int target) {
        // Base case: finished assigning signs to every element
        if (indx == nums.size()) return currentSum == target ? 1 : 0;

        // Assign + sign
        int plus = solve(indx + 1, currentSum + nums[indx], nums, target);
        // Assign - sign
        int minus = solve(indx + 1, currentSum - nums[indx], nums, target);

        return plus + minus;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        return solve(0, 0, nums, target);
    }
};

// 2. Memoization (Top-down DP)
class TargetSumMemoization {
public:
    // TC: O(n * target), SC: O(n * target) for dp array + O(n) recursion stack
    int solve(int indx, int sum, vector<int>& nums, vector<vector<int>>& dp) {
        // Base case: processed all elements
        if (indx == nums.size()) return sum == 0;
        
        // Return cached result
        if (dp[indx][sum] != -1) return dp[indx][sum];
        
        // Pick (assign + sign) or not pick (assign - sign)
        int pick = 0;
        if (sum >= nums[indx])
            pick = solve(indx + 1, sum - nums[indx], nums, dp);
        int notPick = solve(indx + 1, sum, nums, dp);
        
        return dp[indx][sum] = (pick + notPick) % MOD;
    }
    
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0LL);
        if (totalSum < abs(target) || (totalSum + target) % 2 != 0) return 0;
        int s1 = (totalSum + target) / 2;
        vector<vector<int>> dp(nums.size() + 1, vector<int>(s1 + 1, -1));
        return solve(0, s1, nums, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class TargetSumTabulation {
public:
    // TC: O(n * target), SC: O(n * target) for dp array
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0LL);
        if (totalSum < abs(target) || (totalSum + target) % 2 != 0) return 0;
        int s1 = (totalSum + target) / 2;
        
        // dp[i][sum]: number of ways to achieve sum using first i elements
        vector<vector<int>> dp(nums.size() + 1, vector<int>(s1 + 1, 0));
        dp[0][0] = 1;
        
        for (int i = 1; i <= nums.size(); ++i) {
            for (int t = 0; t <= s1; ++t) {
                // Not pick nums[i-1] (assign - sign)
                dp[i][t] = dp[i - 1][t];
                // Pick nums[i-1] (assign + sign) if possible
                if (t >= nums[i - 1])
                    dp[i][t] += dp[i - 1][t - nums[i - 1]];
            }
        }
        
        return dp[nums.size()][s1];
    }
};

// 4. Space Optimized (O(target) DP)
class Solution {
public:
    // TC: O(n * target), SC: O(target) - only store previous row
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0LL);
        if (totalSum < abs(target) || (totalSum + target) % 2 != 0) return 0;
        int s1 = (totalSum + target) / 2;
        
        vector<int> prev(s1 + 1, 0);
        prev[0] = 1;
        
        for (int i = 0; i < nums.size(); ++i) {
            vector<int> curr(s1 + 1, 0);
            for (int t = 0; t <= s1; ++t) {
                // Not pick nums[i] (assign - sign)
                curr[t] = prev[t];
                // Pick nums[i] (assign + sign) if it fits
                if (t >= nums[i])
                    curr[t] += prev[t - nums[i]];
            }
            prev = curr;
        }
        
        return prev[s1];
    }
};
