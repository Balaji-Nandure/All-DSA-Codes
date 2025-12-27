/*
 * Problem: Maximum Sum Circular Subarray
 * 
 * LeetCode: https://leetcode.com/problems/maximum-sum-circular-subarray/
 * GeeksforGeeks: https://www.geeksforgeeks.org/maximum-contiguous-circular-sum/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/max-circular-subarray-sum-1587115620/1
 * 
 * LeetCode 918: Maximum Sum Circular Subarray
 * 
 * Given a circular integer array nums of length n, return the maximum possible 
 * sum of a non-empty subarray of nums.
 * 
 * A circular array means the end of the array connects to the beginning of the array.
 * Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous 
 * element of nums[i] is nums[(i - 1 + n) % n].
 * 
 * A subarray may only include each element of the fixed buffer nums at most once.
 * Formally, for a subarray nums[i], nums[i+1], ..., nums[j], there does not exist 
 * i <= k1, k2 <= j with k1 % n == k2 % n.
 * 
 * Example 1:
 * Input: nums = [1,-2,3,-2]
 * Output: 3
 * Explanation: Subarray [3] has maximum sum 3.
 * 
 * Example 2:
 * Input: nums = [5,-3,5]
 * Output: 10
 * Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
 * 
 * Example 3:
 * Input: nums = [-3,-2,-3]
 * Output: -2
 * Explanation: Subarray [-2] has maximum sum -2.
 * 
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 3 * 10^4
 * - -3 * 10^4 <= nums[i] <= 3 * 10^4
 * 
 * Approach:
 * - Key Insight: In circular array, max sum can be:
 *   1. Maximum subarray sum in normal array (using Kadane's)
 *   2. Total sum - Minimum subarray sum (wrapping around)
 * 
 * - Method: Use Kadane's algorithm twice
 *   - First: Find maximum subarray sum (normal)
 *   - Second: Find minimum subarray sum
 *   - Answer: max(normalMax, totalSum - minSum)
 *   - Edge case: If all elements are negative, return normalMax
 * 
 * Time: O(n) - two passes through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Kadane's Algorithm (Optimal) - O(n) time, O(1) space
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        
        // Case 1: Maximum subarray sum (normal, non-circular)
        int maxSum = nums[0];
        int currentMax = nums[0];
        
        for (int i = 1; i < n; i++) {
            currentMax = max(nums[i], currentMax + nums[i]);
            maxSum = max(maxSum, currentMax);
        }
        
        // Case 2: Minimum subarray sum (for circular case)
        int minSum = nums[0];
        int currentMin = nums[0];
        int totalSum = nums[0];
        
        for (int i = 1; i < n; i++) {
            totalSum += nums[i];
            currentMin = min(nums[i], currentMin + nums[i]);
            minSum = min(minSum, currentMin);
        }
        
        // Edge case: If all elements are negative
        if (totalSum == minSum) {
            return maxSum;  // Return the maximum single element
        }
        
        // Maximum circular sum = max(normalMax, totalSum - minSum)
        return max(maxSum, totalSum - minSum);
    }

};