/*
 * Problem: Left Smaller Right Greater
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/left-smaller-right-greater/0
 * 
 * Given an unsorted array arr[], find the first element such that every element 
 * to its left is less than or equal to it, and every element to its right is 
 * greater than or equal to it.
 * 
 * Note: If no such element exists, return -1.
 * 
 * Examples:
 * Input: arr = [4, 2, 5, 7]
 * Output: 5
 * Explanation: All elements to the left of 5 are less than or equal to 5, 
 *              and all elements to the right are greater than or equal to 5.
 * 
 * Input: arr = [11, 9, 12]
 * Output: -1
 * Explanation: No element in the array satisfies the required condition.
 * 
 * Constraints:
 * 3 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Precompute suffix minimum array from right to left
 * - suffixMin[i] stores minimum value from arr[i] to end
 * - Track left maximum while iterating from left to right
 * - For each element, check if leftMax <= arr[i] <= suffixMin[i+1]
 * - Return first element that satisfies both conditions
 * - If no element found, return -1
 * 
 * Time: O(n) - two passes through array
 * Space: O(n) - suffix minimum array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findElement(vector<int>& arr) {
        int n = arr.size();
        
        vector<int> suffixMin(n);
        suffixMin[n - 1] = arr[n - 1];
        
        // Build suffix min from right to left
        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(arr[i], suffixMin[i + 1]);
        }
        
        int leftMax = arr[0];
        
        // Check each element from 1 to n-2
        for (int i = 1; i < n - 1; i++) {
            
            if (leftMax <= arr[i] && arr[i] <= suffixMin[i + 1]) {
                return arr[i];
            }
            
            leftMax = max(leftMax, arr[i]);
        }
        
        return -1;
    }
};
