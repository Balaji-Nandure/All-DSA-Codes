/*
 * Problem: Product of Array Except Self
 * 
 * LeetCode: https://leetcode.com/problems/product-of-array-except-self/
 * GeeksforGeeks: https://www.geeksforgeeks.org/product-array-puzzle/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/product-array-puzzle4525/1
 * 
 * LeetCode 238: Product of Array Except Self
 * 
 * Given an integer array nums, return an array answer such that answer[i] is 
 * equal to the product of all the elements of nums except nums[i].
 * 
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * 
 * You must write an algorithm that runs in O(n) time and without using the division operator.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 * Explanation: 
 *   answer[0] = 2*3*4 = 24
 *   answer[1] = 1*3*4 = 12
 *   answer[2] = 1*2*4 = 8
 *   answer[3] = 1*2*3 = 6
 * 
 * Example 2:
 * Input: nums = [-1,1,0,-3,3]
 * Output: [0,0,9,0,0]
 * 
 * Constraints:
 * - 2 <= nums.length <= 10^5
 * - -30 <= nums[i] <= 30
 * - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * 
 * Approach:
 * - Method 1: Prefix and Suffix Products (Optimal) - O(n) time, O(1) space
 *   For each index i, answer[i] = product of all elements before i * product of all elements after i
 *   Use two passes: left to right for prefix, right to left for suffix
 * 
 * - Method 2: Using Division (Not allowed but for reference) - O(n) time, O(1) space
 *   Calculate total product, then divide by each element
 * 
 * - Method 3: Brute Force - O(n^2) time, O(1) space
 * 
 * Time: O(n) - two passes through the array
 * Space: O(1) - constant extra space (excluding output array)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Prefix and Suffix Products (Optimal) - O(n) time, O(1) space
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // First pass: Calculate prefix products (left to right)
        // result[i] = product of all elements to the left of i
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }
        
        // Second pass: Multiply with suffix products (right to left)
        // result[i] = prefix * suffix
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }
        
        return result;
    }
    
    // APPROACH 2: Using Prefix and Suffix Arrays - O(n) time, O(n) space
    vector<int> productExceptSelfArrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n, 1);
        vector<int> suffix(n, 1);
        vector<int> result(n);
        
        // Calculate prefix products
        prefix[0] = 1;
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }
        
        // Calculate suffix products
        suffix[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }
        
        // Multiply prefix and suffix
        for (int i = 0; i < n; i++) {
            result[i] = prefix[i] * suffix[i];
        }
        
        return result;
    }
    
    // APPROACH 4: Brute Force - O(n^2) time, O(1) space
    vector<int> productExceptSelfBrute(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    result[i] *= nums[j];
                }
            }
        }
        
        return result;
    }
    
};
