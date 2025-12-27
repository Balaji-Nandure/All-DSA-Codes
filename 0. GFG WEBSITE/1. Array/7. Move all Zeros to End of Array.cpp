/*
 * Problem: Move all Zeros to End of Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/move-zeroes-end-array/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/move-all-zeroes-to-end-of-array0751/1
 * LeetCode: https://leetcode.com/problems/move-zeroes/
 * 
 * Given an array arr[] of size N, move all zeros to the end of the array
 * while maintaining the relative order of non-zero elements.
 * 
 * Note: 
 * - Do it in-place without making a copy of the array
 * - Minimize the total number of operations
 * 
 * Example 1:
 * Input: N = 5, arr[] = {0, 1, 0, 3, 12}
 * Output: {1, 3, 12, 0, 0}
 * Explanation: All zeros are moved to the end, non-zero elements maintain their order.
 * 
 * Example 2:
 * Input: N = 4, arr[] = {0, 0, 0, 4}
 * Output: {4, 0, 0, 0}
 * 
 * Example 3:
 * Input: N = 5, arr[] = {1, 2, 0, 0, 2}
 * Output: {1, 2, 2, 0, 0}
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - 0 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Use two pointers: one for current position, one for next non-zero position
 * - Traverse the array, when we find a non-zero, swap it with the position
 *   where next non-zero should be placed
 * - This maintains relative order and moves zeros to end
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - in-place modification, constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 3: Using vector (LeetCode style)
void moveZeroes(vector<int>& nums) {
    int nonZeroIndex = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            swap(nums[i], nums[nonZeroIndex]);
            nonZeroIndex++;
        }
    }
}
