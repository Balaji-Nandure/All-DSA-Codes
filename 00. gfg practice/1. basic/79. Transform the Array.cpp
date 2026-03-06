/*
 * Problem: Transform the Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/transform-the-array/1
 * 
 * Given an array arr[] containing integers, zero is considered an invalid number, 
 * and the rest are valid. If two nearest valid numbers are equal, double the first 
 * one and make the second number 0. Finally, move all valid numbers to the left.
 * 
 * Examples:
 * Input: arr[] = [2, 4, 5, 0, 0, 5, 4, 8, 6, 0, 6, 8]
 * Output: [2, 4, 10, 4, 8, 12, 8, 0, 0, 0, 0, 0]
 * Explanation: 
 * Step 1: Remove zeros → [2, 4, 5, 5, 4, 8, 6, 6, 8]
 * Step 2: Merge pairs → 5,5→10 and 6,6→12 → [2, 4, 10, 0, 4, 8, 12, 0, 8]
 * Step 3: Move zeros right → [2, 4, 10, 4, 8, 12, 8, 0, 0, 0, 0, 0]
 * 
 * Input: arr[] = [0, 0]
 * Output: [0, 0]
 * Explanation: All elements are invalid.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Optimized two-step in-place transformation to achieve O(1) space
 * - Step 1: Compact and merge in single pass - process valid elements and merge on-the-fly
 * - Step 2: Fill remaining positions with zeros
 * - This reduces from 3 passes to 2 passes while maintaining O(1) space
 * - Use write pointer to track position for next valid element
 * - Merge logic integrated during compaction for better efficiency
 * 
 * Time: O(n) - two linear passes (optimized from three)
 * Space: O(1) - in-place transformation, no extra arrays
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> transformArray(vector<int>& arr) {
        
        int n = arr.size();
        int writePos = 0;
        
        // Step 1: Compact and merge in single pass
        for(int i = 0; i < n; i++) {
            
            if(arr[i] != 0) {
                
                // Check if we can merge with previous element
                if(writePos > 0 && arr[writePos - 1] == arr[i]) {
                    arr[writePos - 1] *= 2;  // Double the previous element
                    // Don't increment writePos, effectively skipping current element
                }
                else {
                    arr[writePos++] = arr[i];  // Place element at write position
                }
            }
        }
        
        // Step 2: Fill remaining positions with zeros
        while(writePos < n) {
            arr[writePos++] = 0;
        }
        
        return arr;
    }
};