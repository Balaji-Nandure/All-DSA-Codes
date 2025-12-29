/*
 * Problem: Find Minimum in Rotated Sorted Array
 * 
 * LeetCode: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-minimum-element-in-a-sorted-and-rotated-array/
 * Practice: https://practice.geeksforgeeks.org/problems/minimum-element-in-a-sorted-and-rotated-array3611/1
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown 
 * pivot index k (1 <= k < nums.length) such that the resulting array is 
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * 
 * Find the minimum element in the rotated sorted array.
 * 
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: 1
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2]
 * Output: 0
 * 
 * Example 3:
 * Input: nums = [11,13,15,17]
 * Output: 11
 *
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique
 * - nums is an ascending array that is possibly rotated
 * 
 * Approach:
 * - Optimal: Binary Search (O(log n) Time, O(1) Space)
 *   At each step, check if mid element is the minimum (smaller than both neighbors)
 *   or decide the unsorted half (where the min is present) and continue search there.
 *   If array is not rotated: return nums[0]
 */

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // Minimum is in right half
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            }
            // Minimum is in left half (including mid)
            else {
                // 🌟🌟🌟🌟
                right = mid;
            }
        }

        // left == right pointing to minimum
        return nums[left];
    }
};
    

// APPROACH 2: Linear Search - O(n) Time and O(1) Space (for understanding/completeness)
class Solution2 {
public:
    int findMin(vector<int>& nums) {
        int mn = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            mn = min(mn, nums[i]);
        }
        return mn;
    }
};