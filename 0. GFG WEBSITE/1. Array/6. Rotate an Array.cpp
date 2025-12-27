/*
 * Problem: Rotate an Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/array-rotation/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/rotate-array-by-n-elements/0
 * LeetCode: https://leetcode.com/problems/rotate-array/
 * 
 * Given an array arr[] of size N, rotate the array by k positions.
 * 
 * Note: 
 * - k can be greater than N, so we use k % N to handle it
 * - Rotation can be left or right
 * - Do it in-place with O(1) extra space
 * 
 * Example 1 (Right Rotate by 2):
 * Input: N = 5, arr[] = {1, 2, 3, 4, 5}, k = 2
 * Output: {4, 5, 1, 2, 3}
 * Explanation: Rotate array to right by 2 positions
 * 
 * Example 2 (Left Rotate by 2):
 * Input: N = 5, arr[] = {1, 2, 3, 4, 5}, k = 2
 * Output: {3, 4, 5, 1, 2}
 * Explanation: Rotate array to left by 2 positions
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - 0 <= k <= 10^5
 * - 0 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Method 1: Reversal Algorithm (Optimal - O(n) time, O(1) space)
 *   1. Reverse entire array
 *   2. Reverse first k elements
 *   3. Reverse remaining elements
 * 
 * - Method 2: Using extra array (O(n) time, O(n) space)
 * - Method 3: Juggling Algorithm (O(n) time, O(1) space)
 * 
 * Time: O(n) - single pass or multiple passes
 * Space: O(1) - in-place rotation (optimal method)
 */

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        
        // Right rotate using reversal
        reverse(nums.begin(), nums.begin() + n);
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.begin() + n);
    }
};