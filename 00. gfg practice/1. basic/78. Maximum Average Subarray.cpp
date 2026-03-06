/*
 * Problem: Maximum Average Subarray
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/maximum-average-subarray/1
 * 
 * Given an array arr[] of size n and a positive integer k, find the subarray of 
 * length k with the maximum average. Return the starting index of the subarray. 
 * If multiple subarrays have the same maximum average, return the smallest starting index.
 * 
 * Examples:
 * Input: k = 4, n = 6, arr[] = {1, 12, -5, -6, 50, 3}
 * Output: 1
 * Explanation: Maximum average is (12 - 5 - 6 + 50)/4 = 51/4.
 * Subarray [12, -5, -6, 50] starts at index 1.
 * 
 * Input: k = 3, n = 7, arr[] = {3, -435, 335, 10, -50, 100, 20}
 * Output: 2
 * Explanation: Maximum average is (335 + 10 - 50)/3 = 295/3.
 * Subarray [335, 10, -50] starts at index 2.
 * 
 * Constraints:
 * 1 ≤ k ≤ n ≤ 10^5
 * 0 ≤ |arr[i]| ≤ 10^3
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use sliding window technique to find maximum sum subarray of length k
 * - Since all subarrays have same length k, maximizing sum = maximizing average
 * - Calculate sum of first k elements as initial window
 * - Slide window: remove leftmost element, add new rightmost element
 * - Track maximum sum and its starting index
 * - If equal sums found, keep the smaller index (automatic due to left-to-right scan)
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findMaxAverage(vector<int>& arr, int n, int k) {
        
        // Calculate sum of first window
        int currentSum = 0;
        for(int i = 0; i < k; i++) {
            currentSum += arr[i];
        }
        
        int maxSum = currentSum;
        int maxIndex = 0;
        
        // Slide the window from index k to n-1
        for(int i = k; i < n; i++) {
            
            // Slide window: remove left, add right
            currentSum += arr[i] - arr[i - k];
            
            // Update maximum if current sum is greater
            if(currentSum > maxSum) {
                maxSum = currentSum;
                maxIndex = i - k + 1;  // Starting index of current window
            }
        }
        
        return maxIndex;
    }
};