/*
 * Problem: Kth Missing Positive Number
 * 
 * LeetCode: https://leetcode.com/problems/kth-missing-positive-number/
 * GeeksforGeeks: https://www.geeksforgeeks.org/k-th-missing-element-in-sorted-array/
 * Practice: https://practice.geeksforgeeks.org/problems/k-th-missing-element3635/1
 * 
 * Given an array arr of positive integers sorted in a strictly increasing order, 
 * and an integer k, return the k-th positive integer that is missing from this array.
 * 
 * Example 1:
 * Input: arr = [2,3,4,7,11], k = 5
 * Output: 9
 * Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. 
 * The 5th missing positive integer is 9.
 * 
 * Example 2:
 * Input: arr = [1,2,3,4], k = 2
 * Output: 6
 * Explanation: The missing positive integers are [5,6,7,...]. 
 * The 2nd missing positive integer is 6.
 * 
 * Example 3:
 * Input: arr = [1,2,3,4], k = 1
 * Output: 5
 * Explanation: The missing positive integers are [5,6,7,...]. 
 * The 1st missing positive integer is 5.
 * 
 * Constraints:
 * - 1 <= arr.length <= 1000
 * - 1 <= arr[i] <= 1000
 * - 1 <= k <= 1000
 * - arr[i] < arr[j] for 1 <= i < j <= arr.length
 * 
 * Approach:
 * - Method 1: Binary Search (Optimal) - O(log n) time, O(1) space
 *   For each index i, count missing numbers before arr[i] = arr[i] - i - 1
 *   Use binary search to find the smallest index where missing count >= k
 * 
 * - Method 2: Linear Search - O(n) time, O(1) space
 *   Traverse array and count missing numbers until we reach k-th missing
 * 
 * - Method 3: Set-based - O(n) time, O(n) space
 *   Store all numbers in set, check from 1 onwards
 * 
 * Time: O(log n) - binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Binary Search - O(log n) Time and O(1) Space
    int findKthPositive(vector<int>& arr, int k) {
        int n = arr.size();
        int left = 0, right = n - 1;
        
        // Binary search to find the smallest index where
        // number of missing elements before arr[i] >= k
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Number of missing elements before arr[mid]
            // = arr[mid] - mid - 1
            // (arr[mid] is the (mid+1)-th element, so missing = arr[mid] - (mid+1))
            int missing = arr[mid] - mid - 1;
            
            if (missing < k) {
                // Not enough missing numbers before arr[mid]
                // k-th missing is to the right
                left = mid + 1;
            } else {
                // Too many or exactly k missing numbers before arr[mid]
                // k-th missing is to the left or at arr[mid]
                right = mid - 1;
            }
        }
        
        // After binary search, left points to the position where
        // we need to insert the k-th missing number
        // k-th missing = left + k
        // (left is the index, and we need k more numbers)
        return left + k;
    }
};