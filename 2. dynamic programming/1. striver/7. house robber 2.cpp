/*
PROBLEM: House Robber II
STATEMENT SUMMARY:
You are given an array nums where nums[i] represents the amount of money in the ith house.
All houses are arranged in a circle, meaning the first and last houses are adjacent.
You cannot rob two adjacent houses. Return the maximum money you can rob.

KEY OBSERVATION:
Because houses are circular, you cannot rob both first and last houses.
So break into TWO LINEAR subproblems:
1) Rob houses from index 0 to n-2
2) Rob houses from index 1 to n-1
Answer = max(result of both)

DP STATE (for linear robber):
dp[i] = maximum money robbed from houses [start...i]

RECURRENCE:
dp[i] = max(
    dp[i-1],                // do not rob ith house
    nums[i] + dp[i-2]       // rob ith house
)

BASE CASES:
If n == 1 → answer = nums[0]

PLATFORM LINKS:
GFG: https://practice.geeksforgeeks.org/problems/house-robber-ii/1
LeetCode: https://leetcode.com/problems/house-robber-ii/
*/


/*===============================================================
  APPROACH 1: PURE RECURSION (PICK / NOT PICK)
  TC: O(2^N)
  SC: O(N) recursion stack
================================================================*/
class Solution1_Recursion_PickNotPick {
public:
    int solve(int idx, int start, vector<int>& nums) {
        if (idx < start) return 0;          // crossed allowed range
        if (idx == start) return nums[start];

        int notPick = solve(idx - 1, start, nums);
        int pick = nums[idx] + solve(idx - 2, start, nums);

        return max(pick, notPick);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int case1 = solve(n - 2, 0, nums);  // exclude last
        int case2 = solve(n - 1, 1, nums);  // exclude first

        return max(case1, case2);
    }
};

/*===============================================================
  APPROACH 2: MEMOIZATION (TOP-DOWN)
  TC: O(N)
  SC: O(N) + recursion stack
================================================================*/
class Solution2_Memoization {
public:
    int solve(int idx, int start, vector<int>& nums, vector<int>& dp) {
        if (idx < start) return 0;
        if (idx == start) return nums[start];

        if (dp[idx] != -1) return dp[idx];     // reuse

        int notPick = solve(idx - 1, start, nums, dp);
        int pick = nums[idx] + solve(idx - 2, start, nums, dp);

        return dp[idx] = max(pick, notPick);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        vector<int> dp1(n, -1), dp2(n, -1);

        int case1 = solve(n - 2, 0, nums, dp1);
        int case2 = solve(n - 1, 1, nums, dp2);

        return max(case1, case2);
    }
};


/*===============================================================
  APPROACH 3: TABULATION (BOTTOM-UP)
  TC: O(N)
  SC: O(N)
================================================================*/
class Solution3_Tabulation {
public:
    int helper(int start, int end, vector<int>& nums) {
        vector<int> dp(nums.size(), 0);

        dp[start] = nums[start];                          // base
        dp[start + 1] = max(nums[start], nums[start + 1]);

        for (int i = start + 2; i <= end; i++) {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }

        return dp[end];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int case1 = helper(0, n - 2, nums);
        int case2 = helper(1, n - 1, nums);

        return max(case1, case2);
    }
};


/*===============================================================
  APPROACH 4: SPACE OPTIMIZATION
  TC: O(N)
  SC: O(1)
================================================================*/
class Solution4_SpaceOptimized {
public:
    int helper(int start, int end, vector<int>& nums) {
        int prev2 = nums[start];                      // dp[i-2]
        int prev1 = max(nums[start], nums[start + 1]); // dp[i-1]

        for (int i = start + 2; i <= end; i++) {
            int curr = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int case1 = helper(0, n - 2, nums);
        int case2 = helper(1, n - 1, nums);

        return max(case1, case2);
    }
};
