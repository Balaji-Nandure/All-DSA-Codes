/*
 * Problem: Find the Duplicate Number (Only Repeating From 1 To n-1)
 * 
 * LeetCode: https://leetcode.com/problems/find-the-duplicate-number/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-repetitive-element-1-n-1/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/find-the-repeating-element/1
 * 
 * LeetCode 287: Find the Duplicate Number
 * 
 * Given an array of integers nums containing n + 1 integers where each integer 
 * is in the range [1, n] inclusive. There is only one repeated number in nums, 
 * return this repeated number.
 * 
 * Note: This problem has a variant where array has n elements with values 
 * from 1 to n-1 (exactly one repeating).
 * 
 * Example 1:
 * Input: nums = [1,3,4,2,2]
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [3,1,3,4,2]
 * Output: 3
 * 
 * Example 3:
 * Input: nums = [1,1]
 * Output: 1
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - nums.length == n + 1 (or n for variant)
 * - 1 <= nums[i] <= n
 * - Only one repeated number in nums
 * 
 * Approach:
 * - Method 1: Sum approach (for variant with n elements, 1 to n-1)
 *   Sum of array - Sum of 1 to n-1 = repeating number
 * 
 * - Method 2: XOR approach
 *   XOR all array elements with 1 to n-1, result is repeating number
 * 
 * - Method 3: Floyd's Cycle Detection (Tortoise and Hare)
 *   Treat array as linked list, find cycle start
 * 
 * - Method 4: Hash map / Set
 * - Method 5: Array marking (negate visited)
 * 
 * Time: O(n) - single pass
 * Space: O(1) - constant extra space (optimal methods)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Sum Approach (Optimal for variant: n elements, 1 to n-1)
    // Sum of array - Expected sum (1 to n-1) = Repeating number
    int findDuplicateSum(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        
        // Calculate sum of array
        for (int num : nums) {
            sum += num;
        }
        
        // Expected sum of 1 to n-1 = (n-1) * n / 2
        int expectedSum = (n - 1) * n / 2;
        
        // Repeating number = sum - expectedSum
        return sum - expectedSum;
    }
    
    // APPROACH 2: XOR Approach (Optimal) - O(n) time, O(1) space
    int findDuplicateXOR(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        
        // XOR all array elements
        for (int num : nums) {
            result ^= num;
        }
        
        // XOR with 1 to n-1 (cancels out all except repeating)
        for (int i = 1; i < n; i++) {
            result ^= i;
        }
        
        return result;
    }
};
