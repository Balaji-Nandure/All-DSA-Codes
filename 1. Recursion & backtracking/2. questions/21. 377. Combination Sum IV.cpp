/*
 * Problem: Combination Sum IV (Backtracking & DP Solutions)
 * 
 * LeetCode 377: Combination Sum IV
 * 
 * Given an array of distinct integers nums and a target integer target, 
 * return the number of possible combinations that add up to target.
 * 
 * Note: Different sequences are counted as different combinations.
 * The test cases are generated so that the answer can fit in a 32-bit integer.
 *
 * Example 1:
 * Input: nums = [1,2,3], target = 4
 * Output: 7
 * Explanation:
 * The possible combination ways are:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 * Note that different sequences are counted as different combinations.
 *
 * Example 2:
 * Input: nums = [9], target = 3
 * Output: 0
 *
 * Key Difference from LC 39 (Combination Sum):
 * - LC 39: Order doesn't matter ([1,2] = [2,1])
 * - LC 377: Order matters ([1,2] ≠ [2,1], counted separately)
 *
 * Approaches:
 * 1. Pure Backtracking
 *    - Try every number in nums at every step until we reach target
 *    - For every possible sequence, count if sum reaches target (base case)
 *    - No DP/memoization used; may be slow for big targets, but illustrates backtracking idea
 *
 *    Time: O(n^target) in worst case
 *    Space: O(target), recursion stack
 * 2. Dynamic Programming (Recommended)
 *    - dp[t] = number of ways to sum to t
 *    - dp[0] = 1 (empty sequence sums to 0)
 *    - For t from 1 to target, for each num in nums, if t-num >= 0: dp[t] += dp[t-num]
 *    - Time: O(target * n)
 *    - Space: O(target)
 */

#include <bits/stdc++.h>
using namespace std;


// ---------------- take not take method starts here ----------------
// Solution: Variant using recursion (for loop method)
// This is for the variant where order DOES NOT matter (each combination of elements is counted once, not permutations--like LC 39)
class Solution2 {
    public:
        int solve(int idx, const vector<int>& nums, int target) {
            if (target == 0)
                return 1;
            if (idx >= (int)nums.size() || target < 0)
                return 0;   
    
            // Take idx (can reuse same index) 
            // ⭐⭐⭐ if you take start from 0 again.
            int take_idx = solve(0, nums, target - nums[idx]);
            // Don't take idx (move to next)
            int reject_idx = solve(idx + 1, nums, target);
    
            return take_idx + reject_idx;
        }
    
        int combinationSum4_variant(vector<int>& nums, int target) {
            return solve(0, nums, target);
        }
    };

// ---------------- For loop mehod starts here ----------------
// Solution 1: Pure Backtracking 
class Solution {
private:
    void backtrack(vector<int>& nums, int target, int& count) {
        if (target == 0) {
            count++;
            return;
        }
        if (target < 0) return;
        for (int i = 0; i < nums.size(); ++i) {
            backtrack(nums, target - nums[i], count);
        }
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        int count = 0;
        backtrack(nums, target, count);
        return count;
    }
};

// Solution 3: DP with Memoization
// ⭐🌟⭐ this is the best method uses single 1d dp array using for loop method.
class Solution3 {
public:
    int helper(vector<int>& nums, int target, vector<int>& dp) {
        if (target == 0) return 1;
        if (target < 0) return 0;
        if (dp[target] != -1) return dp[target];
        int ways = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ways += helper(nums, target - nums[i], dp);
        }
        dp[target] = ways;
        return ways;
    }

    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, -1);
        return helper(nums, target, dp);
    }
};
