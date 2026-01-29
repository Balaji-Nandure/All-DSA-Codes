/*
Problem:
446. Arithmetic Slices II - Subsequence

Approach:
DP with map of differences.

dp[i][d]:
number of arithmetic subsequences (len >= 2)
ending at index i with difference d.

For every pair (j < i):
1) d = nums[i] - nums[j]
2) Existing sequences at j with same d can be extended
3) New pair (nums[j], nums[i]) also forms len = 2 subsequence

Only extensions contribute to final answer (len >= 3).

LeetCode:
https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

Time Complexity:
O(n^2)

Space Complexity:
O(n^2)
*/


class Solution {
public:
    int solve(vector<int>& nums, int i, vector<unordered_map<long long, int>>& dp) {
        if (i >= nums.size()) return 0;
        
        int count = 0;
        
        // Process all previous indices j < i
        for (int j = 0; j < i; j++) {
            long long diff = (long long)nums[i] - nums[j];
            
            // Count of subsequences ending at j with difference diff
            int count_at_j = dp[j].count(diff) ? dp[j][diff] : 0;
            
            // All subsequences at j can be extended to i
            // These are sequences of length >= 3
            count += count_at_j;
            
            // Update dp[i][diff]:
            // 1) Add all extended sequences from j (count_at_j)
            // 2) Add new pair (nums[j], nums[i]) as length 2 subsequence (+1)
            dp[i][diff] += count_at_j + 1;
        }
        
        // Recursively solve for next index and add to count
        count += solve(nums, i + 1, dp);
        
        return count;
    }
    
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
        // dp[i] = map of {difference -> count of subsequences ending at i}
        vector<unordered_map<long long, int>> dp(n);
        
        return solve(nums, 0, dp);
    }
};



































































