/*
 * Problem: Max Consecutive Ones III
 * 
 * LeetCode: https://leetcode.com/problems/max-consecutive-ones-iii/
 * GeeksforGeeks: https://www.geeksforgeeks.org/longest-sequence-consecutive-ones-flipping-k-zeroes/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/maximize-number-of-1s0905/1
 * 
 * LeetCode 1004: Max Consecutive Ones III
 * 
 * Given a binary array nums and an integer k, return the maximum number of 
 * consecutive 1's in the array if you can flip at most k 0's.
 * 
 * Example 1:
 * Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Output: 6
 * Explanation: [1,1,1,0,0,1,1,1,1,1,1]
 *              Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
 * 
 * Example 2:
 * Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
 * Output: 10
 * Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 *              Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - nums[i] is either 0 or 1
 * - 0 <= k <= nums.length
 * 
 * Approach:
 * - Sliding Window Technique (Optimal)
 *   Maintain a window with at most k zeros
 *   Expand window by moving right pointer
 *   If zeros exceed k, shrink window from left
 *   Track maximum window size
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    // APPROACH 2: Sliding Window (Alternative) - More intuitive
    int longestOnesAlternative(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = 0;
        int maxLen = 0;
        int zeros = 0;
        
        while (right < n) {
            // Expand window
            if (nums[right] == 0) {
                zeros++;
            }
            
            // Shrink window if needed
            while (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            
            // Update answer
            maxLen = max(maxLen, right - left + 1);
            right++;
        }
        
        return maxLen;
    }
    
};
 