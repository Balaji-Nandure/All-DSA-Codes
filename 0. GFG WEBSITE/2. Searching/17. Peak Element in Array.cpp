/*
 * Problem: Peak Element in Array
 * 
 * LeetCode: https://leetcode.com/problems/find-peak-element/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
 * Practice: https://practice.geeksforgeeks.org/problems/peak-element/1
 * 
 * A peak element is an element that is strictly greater than its neighbors.
 * Given a 0-indexed integer array nums, find a peak element, and return its index.
 * If the array contains multiple peaks, return the index to any of the peaks.
 * 
 * You may imagine that nums[-1] = nums[n] = -∞.
 * In other words, an element is always considered to be strictly greater than a 
 * neighbor that is outside the array.
 * 
 * You must write an algorithm that runs in O(log n) time.
 * 
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index number 2.
 * 
 * Example 2:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 5
 * Explanation: Your function can return either index number 1 where the peak element is 2,
 *               or index number 5 where the peak element is 6.
 * 
 * Example 3:
 * Input: nums = [1]
 * Output: 0
 * Explanation: Single element is always a peak
 * 
 * Constraints:
 * - 1 <= nums.length <= 1000
 * - -2^31 <= nums[i] <= 2^31 - 1
 * - For all valid i, nums[i] != nums[i + 1]
 * 
 * Approach:
 * - Optimal: Binary Search (O(log n) Time, O(1) Space)
 *   Key insight: If arr[mid] < arr[mid+1], peak is in right half
 *                If arr[mid] > arr[mid+1], peak is in left half (including mid)
 *   We can always move towards a peak because:
 *   - If we're on an upward slope (arr[mid] < arr[mid+1]), there must be a peak to the right
 *   - If we're on a downward slope (arr[mid] > arr[mid+1]), there must be a peak to the left
 * 
 * Time: O(log n) - binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Binary Search - O(log n) Time and O(1) Space
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid is on an upward slope, peak is in right half
            if (nums[mid] < nums[mid + 1]) {
                left = mid + 1;
            } 
            // If mid is on a downward slope, peak is in left half (including mid)
            else {
                right = mid;
            }
        }
        
        // left == right pointing to a peak element
        return left;
    }
};

// APPROACH 2: Linear Search - O(n) Time and O(1) Space
int findPeakElement(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        bool leftOk  = (i == 0) || (arr[i] >= arr[i - 1]);
        bool rightOk = (i == n - 1) || (arr[i] >= arr[i + 1]);

        if (leftOk && rightOk) {
            return i; // index of a peak
        }
    }
    return -1;
}