/*
 * Problem: Two Smallests in Every Subarray
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/two-smallests-in-every-subarray/1
 * 
 * Given an array of integers arr, the task is to find and return the maximum 
 * sum of the smallest and second smallest element among all possible subarrays 
 * of size greater than one. If it is not possible, then return -1.
 * 
 * Examples:
 * Input: arr = [4, 3, 1, 5, 6]
 * Output: 11
 * Explanation: Subarrays with smallest and second smallest are:
 * [4, 3] → smallest = 3, second smallest = 4, sum = 7
 * [3, 1] → smallest = 1, second smallest = 3, sum = 4
 * [1, 5] → smallest = 1, second smallest = 5, sum = 6
 * [5, 6] → smallest = 5, second smallest = 6, sum = 11
 * Maximum sum among all choices is 5 + 6 = 11.
 * 
 * Input: arr = [1]
 * Output: -1
 * Explanation: Array size is 1, but we need minimum 2 elements.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Key insight: The optimal sum of smallest + second smallest will always
 *   come from two adjacent elements in the array
 * - For any subarray of size ≥ 2, if we have a gap between elements,
 *   there might be smaller elements in between that reduce the sum
 * - Therefore, we only need to check adjacent pairs: arr[i] + arr[i+1]
 * - Find the maximum sum among all adjacent pairs
 * - Handle edge case: if array size < 2, return -1
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int pairWithMaxSum(vector<int> &arr) {
        
        int n = arr.size();
        
        if(n < 2) {
            return -1;
        }
        
        int ans = 0;
        
        for(int i = 0; i < n-1; i++) {
            ans = max(ans, arr[i] + arr[i+1]);
        }
        
        return ans;
    }
};