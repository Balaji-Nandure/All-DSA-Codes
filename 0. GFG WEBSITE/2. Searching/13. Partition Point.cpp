/*
 * Problem: Partition Point
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-the-element-before-which-all-the-elements-are-smaller-than-it-and-after-which-all-are-greater-than-it/
 * Practice: https://practice.geeksforgeeks.org/problems/partition-point-in-array/1
 * 
 * Find the element before which all the elements are smaller than it, 
 * and after which all are greater.
 * 
 * Example 1:
 * Input: arr[] = {5, 1, 4, 3, 6, 8, 10, 7, 9}
 * Output: 6
 * Explanation: At index 4, element 6 has all elements smaller than it on left
 *              and all elements greater than it on right
 * 
 * Example 2:
 * Input: arr[] = {5, 1, 4, 4}
 * Output: -1
 * Explanation: No such element exists
 * 
 * Example 3:
 * Input: arr[] = {4, 2, 5, 7}
 * Output: 5
 * Explanation: At index 2, element 5 has all elements smaller on left and greater on right
 * 
 * Constraints:
 * - 1 <= n <= 10^6
 * - 1 <= arr[i] <= 10^9
 * 
 * Approach:
 * - Method 1: Nested Loops (Naive) - O(n^2) time, O(1) space
 *   For each element, check if all left are smaller and all right are greater
 * 
 * - Method 2: Prefix and Suffix Arrays - O(n) time, O(n) space
 *   Precompute max from left and min from right for each position
 *   Check if arr[i] > maxLeft[i-1] and arr[i] < minRight[i+1]
 * 
 * - Method 3: Prefix Array - O(n) time, O(n) space
 *   Use prefix max array, check in single pass with suffix min
 * 
 * Time: O(n) - prefix and suffix arrays (optimal method)
 * Space: O(n) - prefix and suffix arrays
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Naive Approach] Using Nested Loops - O(n^2) Time and O(1) Space
    int findPartitionPointNaive(vector<int>& arr) {
        int n = arr.size();
        
        // Check each element as potential partition point
        for (int i = 0; i < n; i++) {
            bool valid = true;
            
            // Check all elements to the left are smaller
            for (int j = 0; j < i; j++) {
                if (arr[j] >= arr[i]) {
                    valid = false;
                    break;
                }
            }
            
            if (!valid) continue;
            
            // Check all elements to the right are greater
            for (int j = i + 1; j < n; j++) {
                if (arr[j] <= arr[i]) {
                    valid = false;
                    break;
                }
            }
            
            if (valid) {
                return arr[i];
            }
        }
        
        return -1;
    }
    
    // [Expected Approach 2] Using Prefix Array - O(n) Time and O(n) Space
    int findPartitionPointPrefix(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return -1;
        if (n == 1) return arr[0];
        
        // Prefix array: max element from left up to index i (excluding i)
        vector<int> prefixMax(n);
        prefixMax[0] = INT_MIN;  // No elements before index 0
        
        for (int i = 1; i < n; i++) {
            prefixMax[i] = max(prefixMax[i - 1], arr[i - 1]);
        }
        
        // Traverse from right to left, track minimum from right
        int suffixMin = INT_MAX;
        
        for (int i = n - 1; i >= 0; i--) {
            // Check if current element is partition point
            bool leftValid = (prefixMax[i] < arr[i]);
            bool rightValid = (i == n - 1 || suffixMin > arr[i]);
            
            if (leftValid && rightValid) {
                return arr[i];
            }
            
            // Update suffix minimum
            suffixMin = min(suffixMin, arr[i]);
        }
        
        return -1;
    }
};