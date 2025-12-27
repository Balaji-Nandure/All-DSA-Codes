/*
 * Problem: Find Pivot Index / Equilibrium Index
 * 
 * LeetCode: https://leetcode.com/problems/find-pivot-index/
 * GeeksforGeeks: https://www.geeksforgeeks.org/equilibrium-index-of-an-array/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/equilibrium-point-1587115620/1
 * 
 * LeetCode 724: Find Pivot Index
 * 
 * Given an array of integers nums, calculate the pivot index of this array.
 * 
 * The pivot index is the index where the sum of all the numbers strictly to the 
 * left of the index is equal to the sum of all the numbers strictly to the right.
 * 
 * If the index is on the left edge of the array, then the left sum is 0 because 
 * there are no elements to the left. This also applies to the right edge of the array.
 * 
 * Return the leftmost pivot index. If no such index exists, return -1.
 * 
 * Example 1:
 * Input: nums = [1,7,3,6,5,6]
 * Output: 3
 * Explanation: The pivot index is 3.
 *              Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
 *              Right sum = nums[4] + nums[5] = 5 + 6 = 11
 * 
 * Example 2:
 * Input: nums = [1,2,3]
 * Output: -1
 * Explanation: There is no index that satisfies the conditions.
 * 
 * Example 3:
 * Input: nums = [2,1,-1]
 * Output: 0
 * Explanation: The pivot index is 0.
 *              Left sum = 0 (no elements to the left of index 0)
 *              Right sum = nums[1] + nums[2] = 1 + -1 = 0
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -1000 <= nums[i] <= 1000
 * 
 * Approach:
 * - Method 1: Prefix Sum (Optimal) - O(n) time, O(1) space
 *   Calculate total sum, then for each index check if left sum = right sum
 *   leftSum = sum of elements before index
 *   rightSum = totalSum - leftSum - nums[index]
 * 
 * - Method 2: Two Pass with Prefix Array - O(n) time, O(n) space
 * - Method 3: Brute Force - O(n^2) time
 * 
 * Time: O(n) - single pass
 * Space: O(1) - constant extra space (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Prefix Sum (Optimal) - O(n) time, O(1) space
    int pivotIndex(vector<int>& nums) {
        int totalSum = 0;
        
        // Calculate total sum
        for (int num : nums) {
            totalSum += num;
        }
        
        int leftSum = 0;
        
        // For each index, check if it's a pivot
        for (int i = 0; i < nums.size(); i++) {
            // Right sum = total sum - left sum - current element
            int rightSum = totalSum - leftSum - nums[i];
            
            // Check if left sum equals right sum
            if (leftSum == rightSum) {
                return i;
            }
            
            // Update left sum for next iteration
            leftSum += nums[i];
        }
        
        return -1;  // No pivot index found
    }
    
    // APPROACH 3: Brute Force - O(n^2) time, O(1) space
    int pivotIndexBrute(vector<int>& nums) {
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            int leftSum = 0, rightSum = 0;
            
            // Calculate left sum
            for (int j = 0; j < i; j++) {
                leftSum += nums[j];
            }
            
            // Calculate right sum
            for (int j = i + 1; j < n; j++) {
                rightSum += nums[j];
            }
            
            if (leftSum == rightSum) {
                return i;
            }
        }
        
        return -1;
    }
    
};