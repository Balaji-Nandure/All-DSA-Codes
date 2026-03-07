/*
 * Problem: Max Value
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/max-value/1
 * 
 * In a given array arr[], find the maximum value of (arr[i] – i) - (arr[j] – j) 
 * where i is not equal to j and n is the size of the array. i and j vary from 0 to n-1.
 * 
 * Examples:
 * Input: arr[] = [9, 15, 4, 12, 13]
 * Output: 12
 * Explanation: (arr[1]-1) - (arr[2]-2) = (15-1) - (4-2) = 14 - 2 = 12
 * 
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 3
 * Explanation: (arr[0]-0) - (arr[1]-1) = (3-0) - (1-1) = 3 - 0 = 3
 * 
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Key insight: We want to maximize (arr[i] - i) - (arr[j] - j)
 * - This equals max(arr[i] - i) - min(arr[j] - j) where i ≠ j
 * - Simple solution: Find overall max and min of (arr[k] - k)
 * - Since array has at least 2 elements, max and min will naturally be different
 * - Even if they occur at same index, there are other elements to choose from
 * - The maximum difference will always be achieved by global max - global min
 * - No need to track indices or second values!
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxValue(vector<int>& arr) {
        
        int maxVal = INT_MIN;
        int minVal = INT_MAX;
        
        // Find max and min of (arr[i] - i)
        for(int i = 0; i < arr.size(); i++) {
            
            int val = arr[i] - i;
            maxVal = max(maxVal, val);
            minVal = min(minVal, val);
        }
        
        return maxVal - minVal;
    }
};