/*
 * Problem: Move All Zeroes to End
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/move-all-zeroes-to-end/0
 * 
 * You are given an array arr[] of non-negative integers. You have to move all the 
 * zeros in the array to the right end while maintaining the relative order 
 * of non-zero elements. The operation must be performed in place, meaning you 
 * should not use extra space for another array.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 0, 4, 3, 0, 5, 0]
 * Output: [1, 2, 4, 3, 5, 0, 0, 0]
 * Explanation: There are three 0s that are moved to the end.
 * 
 * Input: arr[] = [10, 20, 30]
 * Output: [10, 20, 30]
 * Explanation: No change in array as there are no 0s.
 * 
 * Input: arr[] = [0, 0]
 * Output: [0, 0]
 * Explanation: No change in array as there are all 0s.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use two-pointer technique: one from start, one from end
 * - Move non-zero elements from left to right in order
 * - Move zeros from right to left in reverse order
 * - This maintains relative order of non-zero elements
 * - In-place operation without extra space
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZerosToEnd(vector<int>& arr) {
        int n = arr.size();
        int left = 0;      // Pointer for non-zero elements
        int right = n - 1;   // Pointer for zero elements
        
        // Move non-zero elements to the left
        for (int i = 0; i < n; i++) {
            if (arr[i] != 0) {
                arr[left++] = arr[i];
            }
        }
        
        // Move zeros to the right
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] == 0) {
                arr[right--] = arr[i];
            }
        }
    }
};
