/*
 * Problem: Maximum Sum of Subarray Less Than or Equal to X
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/maximum-sum-of-subarray-less-than-or-equal-to-x/1
 * 
 * Given an array arr[] of integers and a number x, find the sum of subarray 
 * having maximum sum less than or equal to the given value of x.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 3, 4, 5], x = 11
 * Output: 10
 * Explanation: Subarray [1, 2, 3, 4] has maximum sum = 10 ≤ 11.
 * 
 * Input: arr[] = [2, 4, 6, 8, 10], x = 7
 * Output: 6
 * Explanation: Subarray [2, 4] or [6] both have sum = 6 ≤ 7.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 1 ≤ x ≤ 10^12
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use sliding window (two pointers) technique
 * - Expand window by moving right pointer and adding elements
 * - When sum exceeds x, shrink window from left until sum ≤ x
 * - Track maximum valid sum encountered during the process
 * - This ensures we check all possible subarrays efficiently
 * - Handle edge case where single element > x
 * 
 * Time: O(n) - each element added and removed at most once
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long maxSubarraySum(vector<int>& arr, long long x) {
        
        int n = arr.size();
        long long maxSum = 0;
        long long currentSum = 0;
        int left = 0;
        
        for(int right = 0; right < n; right++) {
            
            // Add current element to window
            currentSum += arr[right];
            
            // Shrink window from left while sum exceeds x
            while(currentSum > x && left <= right) {
                currentSum -= arr[left];
                left++;
            }
            
            // Update maximum sum if current sum is valid
            if(currentSum <= x) {
                maxSum = max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
};