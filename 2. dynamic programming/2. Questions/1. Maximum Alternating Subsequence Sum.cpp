#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Maximum Alternating Subsequence Sum
LeetCode 1911: https://leetcode.com/problems/maximum-alternating-subsequence-sum/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/maximum-alternating-subsequence-sum/1

The alternating sum of a 0-indexed array is defined as the sum of the elements at 
even indices minus the sum of the elements at odd indices.

For example, the alternating sum of [4,2,5,3] is (4 + 5) - (2 + 3) = 4.

Given an array nums, return the maximum sum of a subsequence with the property that 
no two consecutive elements of the subsequence have the same sign in the alternating sum.

In other words, you can choose any subsequence, and the alternating sum is:
- Sum of elements at even positions (0-indexed) in the subsequence
- Minus sum of elements at odd positions (0-indexed) in the subsequence

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^5

Example:
nums = [4,2,5,3]
Subsequence: [4,2,5] -> alternating sum = 4 - 2 + 5 = 7
Or: [4,5] -> alternating sum = 4 + 5 = 9
Maximum = 9

Key Insight:
- We need to find a subsequence that maximizes alternating sum
- Elements at even positions (0, 2, 4, ...) are added
- Elements at odd positions (1, 3, 5, ...) are subtracted
- We can track two states: even (next should be added) and odd (next should be subtracted)
- For each element, we can either take it (if it matches current state) or skip it

DP State: 
- dp[i][even] = maximum alternating sum ending at index i, where i is at even position
- dp[i][odd] = maximum alternating sum ending at index i, where i is at odd position

Alternative simpler state:
- even = maximum alternating sum if next element should be added (even position)
- odd = maximum alternating sum if next element should be subtracted (odd position)

Recurrence:
- For each element nums[i]:
  - even = max(even, odd + nums[i])  // Add current to even position
  - odd = max(odd, even - nums[i])   // Subtract current from odd position
  - Or we can skip: even = even, odd = odd

Base Cases:
- even = 0, odd = 0 (start with no elements)

Time Complexity: O(n) where n is array length
Space Complexity: O(1) for space optimized approach
*/

// 1. Recursive approach (take/not take method)
class MaxAlternatingSumRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    long long solve(int idx, int isEven, vector<int>& nums) {
        // Base case: reached end of array
        if (idx == nums.size()) return 0;
        
        // Option 1: Skip current element
        long long skip = solve(idx + 1, isEven, nums);
        
        // Option 2: Take current element
        long long take = 0;
        if (isEven) {
            // Add current element (even position)
            take = nums[idx] + solve(idx + 1, 0, nums);
        } else {
            // Subtract current element (odd position)
            take = -nums[idx] + solve(idx + 1, 1, nums);
        }
        
        return max(skip, take);
    }
    
    long long maxAlternatingSum(vector<int>& nums) {
        // Start with even position (add first element)
        return solve(0, 1, nums);
    }
};

// 2. Memoization (Top-down DP)
class MaxAlternatingSumMemoization {
public:
    // TC: O(n), SC: O(n) for dp array + O(n) recursion stack
    long long solve(int idx, int isEven, vector<int>& nums, vector<vector<long long>>& dp) {
        if (idx == nums.size()) return 0;
        if (dp[idx][isEven] != -1) return dp[idx][isEven];
        
        long long skip = solve(idx + 1, isEven, nums, dp);
        
        long long take = 0;
        if (isEven) {
            take = nums[idx] + solve(idx + 1, 0, nums, dp);
        } else {
            take = -nums[idx] + solve(idx + 1, 1, nums, dp);
        }
        
        return dp[idx][isEven] = max(skip, take);
    }
    
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2, -1));
        return solve(0, 1, nums, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class MaxAlternatingSumTabulation {
public:
    // TC: O(n), SC: O(n) for dp array
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        // dp[i][0] = max alternating sum ending at i, where i is at odd position (subtracted)
        // dp[i][1] = max alternating sum ending at i, where i is at even position (added)
        vector<vector<long long>> dp(n, vector<long long>(2, 0));
        
        // Base case: first element at even position
        dp[0][1] = nums[0];
        dp[0][0] = 0;
        
        for (int i = 1; i < n; i++) {
            // If we take nums[i] at even position (add it)
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] + nums[i]);
            // If we take nums[i] at odd position (subtract it)
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] - nums[i]);
        }
        
        return max(dp[n-1][0], dp[n-1][1]);
    }
};

// 4. Space Optimization (O(1) DP)
class Solution {
public:
    // TC: O(n), SC: O(1) - only track two states
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        // even = max alternating sum if next element should be added (even position)
        // odd = max alternating sum if next element should be subtracted (odd position)
        long long even = 0;  // Start with even position
        long long odd = 0;   // Start with odd position
        
        for (int i = 0; i < n; i++) {
            long long prevEven = even;
            long long prevOdd = odd;
            
            // If we take nums[i] at even position (add it)
            even = max(prevEven, prevOdd + nums[i]);
            // If we take nums[i] at odd position (subtract it)
            odd = max(prevOdd, prevEven - nums[i]);
        }
        
        return max(even, odd);
    }
};
