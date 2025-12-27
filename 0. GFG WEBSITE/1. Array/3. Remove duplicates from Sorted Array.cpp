/*
 * Problem: Remove Duplicates from Sorted Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/remove-duplicates-sorted-array/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/remove-duplicate-elements-from-sorted-array/1
 * LeetCode: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * 
 * Given a sorted array arr[] of size N, the task is to remove the duplicate elements
 * from the array and return the new size of the array.
 * 
 * Note: 
 * - Do not use extra space, modify the array in-place
 * - The array should be modified such that all unique elements appear at the beginning
 * - Return the new size (number of unique elements)
 * 
 * Example 1:
 * Input: N = 5, arr[] = {2, 2, 2, 2, 2}
 * Output: 1
 * Explanation: After removing all duplicates, only one instance of 2 remains.
 * 
 * Example 2:
 * Input: N = 3, arr[] = {1, 2, 2}
 * Output: 2
 * Explanation: After removing duplicates, array becomes {1, 2}
 * 
 * Example 3:
 * Input: N = 5, arr[] = {1, 1, 2, 2, 3}
 * Output: 3
 * Explanation: After removing duplicates, array becomes {1, 2, 3}
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - 0 <= arr[i] <= 10^6
 * 
 * Approach:
 * - Use two pointers: one for current unique position, one for traversing
 * - Since array is sorted, duplicates are adjacent
 * - When we find a new unique element, place it at the next unique position
 * - Return the count of unique elements
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - in-place modification, no extra space
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 2: Alternative Two Pointers (LeetCode style)
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }
    
    int pos = 1;  // Position for next unique element
    
    for (int i = 1; i < nums.size(); i++) {
        // If current element is different from previous, it's unique
        if (nums[i] != nums[i - 1]) {
            nums[pos] = nums[i];
            pos++;
        }
    }
    
    return j;
}
