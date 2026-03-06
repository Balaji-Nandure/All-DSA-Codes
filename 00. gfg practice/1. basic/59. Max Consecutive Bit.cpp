/*
 * Problem: Max Consecutive Bit
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/max-consecutive-bit/1
 * 
 * Given an array arr[] consisting of only 0's and 1's, return count of the 
 * maximum number of consecutive 1's or 0's present in the array.
 * 
 * Examples:
 * Input: arr[] = [0, 1, 0, 1, 1, 1, 1]
 * Output: 4
 * Explanation: The maximum number of consecutive 1's in the array is 4 from index 3-6.
 * 
 * Input: arr[] = [0, 0, 1, 0, 1, 0]
 * Output: 2
 * Explanation: The maximum number of consecutive 0's in the array is 2 from index 0-1.
 * 
 * Input: arr[] = [0, 0, 0, 0]
 * Output: 4
 * Explanation: The maximum number of consecutive 0's in the array is 4.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 1
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use single traversal to track consecutive identical bits
 * - Maintain currentCount for current streak and maxCount for maximum seen
 * - If current element equals previous element, increment currentCount
 * - Otherwise reset currentCount to 1 (start new streak)
 * - Update maxCount with maximum of current and previous maximum
 * - This works for both consecutive 0s and 1s simultaneously
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxConsecutiveBits(vector<int> &arr) {
        
        int n = arr.size();
        
        int currentCount = 1;
        int maxCount = 1;
        
        for(int i = 1; i < n; i++) {
            
            if(arr[i] == arr[i-1]) {
                currentCount++;
            }
            else {
                currentCount = 1;
            }
            
            maxCount = max(maxCount, currentCount);
        }
        
        return maxCount;
    }
};