/*
 * Problem: Subarray with Given Sum
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-subarray-with-given-sum/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1
 * 
 * Given an unsorted array of non-negative integers, find a continuous subarray which adds to a given number.
 * 
 * Note: Since all elements are positive, we can use sliding window technique efficiently.
 * 
 * Example 1:
 * Input: arr[] = {1, 4, 20, 3, 10, 5}, sum = 33
 * Output: Sum found between indexes 2 and 4
 * Explanation: Sum of elements between indices 2 and 4 is 20 + 3 + 10 = 33
 * 
 * Example 2:
 * Input: arr[] = {1, 4, 0, 0, 3, 10, 5}, sum = 7
 * Output: Sum found between indexes 1 and 4
 * Explanation: Sum of elements between indices 1 and 4 is 4 + 0 + 0 + 3 = 7
 * 
 * Example 3:
 * Input: arr[] = {1, 4}, sum = 0
 * Output: No subarray found
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 0 <= arr[i] <= 10^9
 * - 0 <= sum <= 10^9
 * 
 * Approach:
 * The idea is simple, as we know that all the elements in subarray are positive so,
 * If a subarray has sum greater than the given sum then there is no possibility that 
 * adding elements to the current subarray will be equal to the given sum. 
 * So the Idea is to use a similar approach to a sliding window.
 * 
 * Start with an empty window
 * Add elements to the window while the current sum is less than sum
 * If the sum is greater than sum, remove elements from the start of the current window.
 * If current sum becomes same as sum, return the result
 * 
 * Approaches:
 * [Expected Approach] Sliding Window (Two Pointers) - O(n) Time and O(1) Space
 * [Better Approach] Hash Map (Prefix Sum) - O(n) Time and O(n) Space (works for negative numbers too)
 * [Naive Approach] Two Nested Loops - O(n^2) Time and O(1) Space
 * 
 * Time: O(n) - single pass (optimal approach)
 * Space: O(1) - constant extra space (optimal approach)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Sliding Window (Two Pointers) - O(n) Time and O(1) Space
    // Works efficiently when all elements are non-negative
    vector<int> subarraySum(vector<int>& arr, int n, long long s) {
        int left = 0;
        long long currentSum = 0;
        
        // Start with empty window, add elements while sum < target
        for (int right = 0; right < n; right++) {
            // Add current element to window
            currentSum += arr[right];
            
            // If sum exceeds target, remove elements from start
            while (currentSum > s && left < right) {
                currentSum -= arr[left];
                left++;
            }
            
            // If current sum equals target, return indices (1-indexed for GFG)
            if (currentSum == s) {
                return {left + 1, right + 1};  // GFG uses 1-indexed
            }
        }
        
        // No subarray found
        return {-1};
    }
    
};
