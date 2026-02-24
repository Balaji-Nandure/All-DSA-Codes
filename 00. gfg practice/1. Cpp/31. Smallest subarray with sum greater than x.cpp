/*
 * Problem: Smallest subarray with sum greater than x
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/smallest-subarray-with-sum-greater-than-x/0
 * 
 * Given a number x and an array of integers arr, find the smallest subarray 
 * with sum greater than the given value. If such a subarray does not exist, 
 * return 0 in that case.
 * 
 * Examples:
 * Input: x = 51, arr[] = [1, 4, 45, 6, 0, 19]
 * Output: 3
 * Explanation: Minimum length subarray is [4, 45, 6]
 * 
 * Input: x = 100, arr[] = [1, 10, 5, 2, 7]
 * Output: 0
 * Explanation: No subarray exist
 * 
 * Constraints:
 * 1 ≤ arr.size(), x ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^4
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use sliding window technique to find minimum length subarray with sum > x
 * - Expand window by adding elements from the right
 * - When sum > x, try to shrink window from left
 * - Track minimum length found so far
 * - If no valid subarray found, return 0
 * 
 * Time: O(n) - each element processed at most twice
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int smallestSubWithSum(int x, vector<int>& arr) {
        int n = arr.size();
        
        int minLen = INT_MAX;
        int sum = 0;
        int left = 0;
        
        for (int right = 0; right < n; right++) {
            sum += arr[right];
            
            // Shrink window while sum > x
            while (sum > x) {
                minLen = min(minLen, right - left + 1);
                sum -= arr[left];
                left++;
            }
        }
        
        return (minLen == INT_MAX) ? 0 : minLen;
    }
};