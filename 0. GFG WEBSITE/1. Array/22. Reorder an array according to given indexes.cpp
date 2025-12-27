/*
 * Problem: Reorder an array according to given indexes
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/reorder-a-array-according-to-given-indexes/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/reorder-an-array-according-to-given-indexes/1
 * 
 * Given two integer arrays of same size, "arr[]" and "index[]", reorder elements 
 * in "arr[]" according to the given index array. It is not allowed to use any 
 * extra array space.
 * 
 * Example 1:
 * Input: arr[] = {10, 11, 12}, index[] = {1, 0, 2}
 * Output: arr[] = {11, 10, 12}
 * Explanation: 
 *   index[0] = 1 means arr[0] should be at position 1
 *   index[1] = 0 means arr[1] should be at position 0
 *   index[2] = 2 means arr[2] should be at position 2
 *   So result: arr[0] = 11, arr[1] = 10, arr[2] = 12
 * 
 * Example 2:
 * Input: arr[] = {50, 40, 70, 60, 90}, index[] = {3, 0, 4, 1, 2}
 * Output: arr[] = {40, 60, 90, 50, 70}
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 0 <= index[i] < n
 * - All elements in index[] are distinct
 * 
 * Approach:
 * - Method 1: Using Extra Array - O(n) time, O(n) space
 *   Create temp array, place elements according to index array
 * 
 * - Method 2: In-place with Cycle Detection - O(n) time, O(1) space
 *   For each position, follow the cycle to place elements correctly
 *   Use visited array or modify index array to track cycles
 * 
 * - Method 3: Sorting with Pairs - O(n log n) time, O(n) space
 *   Sort pairs of (index, value) according to index array
 * 
 * Time: O(n) - single pass
 * Space: O(1) - constant extra space (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Using Extra Array - O(n) time, O(n) space
    void reorder(vector<int>& arr, vector<int>& index, int n) {
        vector<int> temp(n);
        
        // Place elements according to index array
        for (int i = 0; i < n; i++) {
            temp[index[i]] = arr[i];
        }
        
        // Copy back to original array
        for (int i = 0; i < n; i++) {
            arr[i] = temp[i];
        }
    }
    
    // APPROACH 2: In-place with Cycle Detection (Optimal) - O(n) time, O(1) space
    void reorderInPlace(vector<int>& arr, vector<int>& index, int n) {
        for (int i = 0; i < n; i++) {
            // While current element is not at correct position
            while (index[i] != i) {
                // Swap both arr and index to maintain consistency
                swap(arr[i], arr[index[i]]);
                swap(index[i], index[index[i]]);
            }
        }
    }
 
    // Function same as above
    void reorderArray(vector<int>& arr, vector<int>& index) {
        int i = 0;
        int n = arr.size();

        // Perform cyclic swaps until all elements are placed at their correct index
        while (i < n) {
            // If current index is already correct, move on
            if (index[i] == i) {
                i++;
            } else {
                // Otherwise, swap arr[i] with arr[index[i]]
                // and update index[i] accordingly
                swap(arr[i], arr[index[i]]);
                swap(index[i], index[index[i]]);
            }
        }
    }
    
};
