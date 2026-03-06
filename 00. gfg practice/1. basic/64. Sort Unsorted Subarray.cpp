/*
 * Problem: Sort Unsorted Subarray
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/sort-unsorted-subarray/1
 * 
 * Given an unsorted array arr[]. Find the subarray arr[s...e] such that sorting 
 * this subarray makes the whole array sorted. If the given array is already 
 * sorted then return [0, 0].
 * 
 * Examples:
 * Input: arr[] = [10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60]
 * Output: [3, 8]
 * Explanation: Sorting subarray from index 3 to 8 results in sorted array.
 * Initial: [10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60]
 * Final: [10, 12, 20, 25, 30, 31, 32, 35, 40, 50, 60]
 * 
 * Input: arr[] = [0, 1, 15, 25, 6, 7, 30, 40, 50]
 * Output: [2, 5]
 * Explanation: Sorting subarray from index 2 to 5 results in sorted array.
 * Initial: [0, 1, 15, 25, 6, 7, 30, 40, 50]
 * Final: [0, 1, 6, 7, 15, 25, 30, 40, 50]
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 2*10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Find the leftmost element that is out of order (greater than next element)
 * - Find the rightmost element that is out of order (smaller than previous element)
 * - Find min and max elements in the unsorted subarray
 * - Expand the boundaries to include elements that should be part of sorted subarray
 * - Left boundary: extend left while elements > min of unsorted part
 * - Right boundary: extend right while elements < max of unsorted part
 * - Handle edge case: if array is already sorted, return [0, 0]
 * 
 * Time: O(n) - multiple single passes
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> findUnsorted(vector<int> &arr) {
        
        int n = arr.size();
        
        // Step 1: Find the first element from left that is out of order
        int left = -1;
        for(int i = 0; i < n-1; i++) {
            if(arr[i] > arr[i+1]) {
                left = i;
                break;
            }
        }
        
        // If no such element found, array is already sorted
        if(left == -1) {
            return {0, 0};
        }
        
        // Step 2: Find the first element from right that is out of order
        int right = -1;
        for(int i = n-1; i > 0; i--) {
            if(arr[i] < arr[i-1]) {
                right = i;
                break;
            }
        }
        
        // Step 3: Find min and max in the unsorted subarray
        int minVal = arr[left];
        int maxVal = arr[left];
        
        for(int i = left; i <= right; i++) {
            minVal = min(minVal, arr[i]);
            maxVal = max(maxVal, arr[i]);
        }
        
        // Step 4: Expand left boundary
        while(left > 0 && arr[left-1] > minVal) {
            left--;
        }
        
        // Step 5: Expand right boundary  
        while(right < n-1 && arr[right+1] < maxVal) {
            right++;
        }
        
        return {left, right};
    }
};