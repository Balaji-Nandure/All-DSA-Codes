/*
 * Problem: Minimum distance in an Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/minimum-distance-in-an-array/0
 * 
 * You are given an array, arr[]. Find the minimum index based distance 
 * between two distinct elements of the array, x and y. Return -1, if either 
 * x or y does not exist in the array.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 3, 2], x = 1, y = 2
 * Output: 1
 * Explanation: x = 1 and y = 2. There are two distances between x and y, 
 *              which are 1 and 3 out of which least is 1.
 * 
 * Input: arr[] = [86, 39, 90, 67, 84, 66, 62], x = 42, y = 12
 * Output: -1
 * Explanation: x = 42 and y = 12. We return -1 as x and y don't exist in the array.
 * 
 * Input: arr[] = [10, 20, 30, 40, 50], x = 10, y = 50
 * Output: 4
 * Explanation: The distance between x = 10 (index 0) and y = 50 (index 4) is 4, 
 *              which is the only distance between them.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i], x, y ≤ 10^5
 * x != y
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Find indices of x and y in the array
 * - If either doesn't exist, return -1
 * - Calculate absolute difference between their indices
 * - This gives the minimum index-based distance
 * - Single pass through array to find both elements
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDist(vector<int>& arr, int x, int y) {
        
        int n = arr.size();
        
        int lastIndex = -1;
        int minDist = INT_MAX;
        
        for(int i = 0; i < n; i++) {
            
            if(arr[i] == x || arr[i] == y) {
                
                // If previously seen x/y and they are different
                if(lastIndex != -1 && arr[i] != arr[lastIndex]) {
                    minDist = min(minDist, i - lastIndex);
                }
                
                lastIndex = i;
            }
        }
        
        if(minDist == INT_MAX)
            return -1;
            
        return minDist;
    }
};
