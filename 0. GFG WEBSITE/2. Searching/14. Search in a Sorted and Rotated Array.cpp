/*
 * Problem: Search in Rotated Sorted Array
 * 
 * LeetCode: https://leetcode.com/problems/search-in-rotated-sorted-array/
 * GeeksforGeeks: https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
 * Practice: https://practice.geeksforgeeks.org/problems/search-in-a-rotated-array4618/1
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown 
 * pivot index k (1 <= k < nums.length) such that the resulting array is 
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * 
 * Given the array nums after the rotation and an integer target, return the index 
 * of target if it is in nums, or -1 if it is not in nums.
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * Explanation: 0 is at index 4 in the rotated array
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * Explanation: 3 is not in the array
 * 
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 * 
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique
 * - nums is an ascending array that is possibly rotated
 * - -10^4 <= target <= 10^4
 * 
 * Approach:
 * - Method 1: Binary Search (Optimal) - O(log n) time, O(1) space
 *   At least one half is always sorted
 *   Check which half is sorted, then check if target is in that sorted half
 *   If yes, search in sorted half; else search in other half
 * 
 * - Method 2: Find Pivot then Binary Search - O(log n) time, O(1) space
 *   First find the pivot point, then binary search in appropriate half
 * 
 * - Method 3: Linear Search - O(n) time, O(1) space
 *   Traverse array and find target
 * 
 * Time: O(log n) - binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

// [Expected Approach] Binary Search - O(log n) Time and O(1) Space
class Solution1 {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Found target
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check which half is sorted
            if (nums[left] <= nums[mid]) {
                // Left half is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    // Target is in sorted left half
                    right = mid - 1;
                } else {
                    // Target is in right half
                    left = mid + 1;
                }
            } else {
                // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    // Target is in sorted right half
                    left = mid + 1;
                } else {
                    // Target is in left half
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

// APPROACH 3: Linear Search - O(n) Time and O(1) Space
class Solution3 {
public:
    int search(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                return i;
            }
        }
        return -1;
    }
};