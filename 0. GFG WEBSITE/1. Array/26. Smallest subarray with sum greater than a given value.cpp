/*
 * Problem: Minimum Size Subarray Sum
 * 
 * LeetCode: https://leetcode.com/problems/minimum-size-subarray-sum/
 * GeeksforGeeks: https://www.geeksforgeeks.org/minimum-length-subarray-sum-greater-given-value/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1
 * 
 * LeetCode 209: Minimum Size Subarray Sum
 * 
 * Given an array of positive integers nums and a positive integer target, 
 * return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr] 
 * of which the sum is greater than or equal to target. If there is no such subarray, return 0.
 * 
 * Example 1:
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem constraint.
 * 
 * Example 2:
 * Input: target = 4, nums = [1,4,4]
 * Output: 1
 * 
 * Example 3:
 * Input: target = 11, nums = [1,1,1,1,1,1,1,1]
 * Output: 0
 * 
 * Constraints:
 * - 1 <= target <= 10^9
 * - 1 <= nums.length <= 10^5
 * - 1 <= nums[i] <= 10^4
 * 
 * Approaches:
 * [Naive Approach] Using Two Nested Loops - O(n^2) Time and O(1) Space
 *   For each starting index, find minimum length subarray with sum >= target
 * 
 * [Better Approach] Prefix Sum and Binary Search - O(n Log n) Time and O(n) Space
 *   Build prefix sum array, for each starting index, binary search for ending index
 * 
 * [Expected Approach] Using Two Pointers - O(n) Time and O(1) Space
 *   Use sliding window technique with two pointers
 *   Expand window by moving right pointer, shrink by moving left pointer
 * 
 * Time: O(n) - single pass (optimal approach)
 * Space: O(1) - constant extra space (optimal approach)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Naive Approach] Using Two Nested Loops - O(n^2) Time and O(1) Space
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        
        // For each starting index
        for (int i = 0; i < n; i++) {
            int sum = 0;
            
            // Find minimum length subarray starting at i with sum >= target
            for (int j = i; j < n; j++) {
                sum += nums[j];
                
                // If sum >= target, update minimum length
                if (sum >= target) {
                    minLen = min(minLen, j - i + 1);
                    break;  // Found minimum for this starting index
                }
            }
        }
        
        return (minLen == INT_MAX) ? 0 : minLen;
    }
    
    // [Expected Approach] Using Two Pointers - O(n) Time and O(1) Space
    // The idea is to use two pointer approach to maintain a sliding window, 
    // where we keep expanding the window by adding elements until the sum 
    // becomes greater than x, 
    // then we try to minimize this window by shrinking it from the start 
    // while maintaining the sum > x condition. This way, we explore all 
    // possible subarrays and keep track of the smallest valid length.
    int minSubArrayLenTwoPointers(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        int left = 0;
        int sum = 0;
        
        // Use sliding window with two pointers
        for (int right = 0; right < n; right++) {
            // Expand window by adding current element
            sum += nums[right];
            
            // Shrink window from left while sum >= target
            while (sum >= target) {
                // Update minimum length
                minLen = min(minLen, right - left + 1);
                
                // Remove leftmost element and move left pointer
                sum -= nums[left];
                left++;
            }
        }
        
        return (minLen == INT_MAX) ? 0 : minLen;
    }
    
    // Alternative: Two Pointers (More explicit)
    int minSubArrayLenSlidingWindow(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        int left = 0, right = 0;
        int sum = 0;
        
        while (right < n) {
            // Expand window
            sum += nums[right];
            
            // Shrink window while condition is satisfied
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                left++;
            }
            
            right++;
        }
        
        return (minLen == INT_MAX) ? 0 : minLen;
    }
    
};
