/*
 * Problem: Rearrange Array such that arr[i] = i
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/rearrange-array-arri/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/rearrange-an-array-with-o1-extra-space3142/1
 * 
 * Given an array of size N that has elements in the range [0, N-1], 
 * rearrange the array such that arr[i] = i. If i is not present, 
 * replace it with -1.
 * 
 * Example 1:
 * Input: arr[] = {-1, -1, 6, 1, 9, 3, 2, -1, 4, -1}
 * Output: {-1, 1, 2, 3, 4, -1, 6, -1, -1, 9}
 * Explanation: Elements are placed at their correct positions
 * 
 * Example 2:
 * Input: arr[] = {19, 7, 0, 3, 18, 15, 12, 6, 1, 8, 11, 10, 9, 5, 13, 16, 2, 14, 17, 4}
 * Output: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}
 * 
 * Example 3:
 * Input: arr[] = {2, 0, 1}
 * Output: {0, 1, 2}
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - -1 <= arr[i] <= N-1
 * 
 * Approach:
 * - Method 1: Using Hash Set - O(n) time, O(n) space
 *   Store all elements in a set, then place each i at arr[i] if it exists
 * 
 * - Method 2: In-place Swapping - O(n) time, O(1) space
 *   For each index, if arr[i] != i and arr[i] != -1, swap arr[i] with arr[arr[i]]
 *   Continue until arr[i] == i or arr[i] == -1
 * 
 * - Method 3: Two Pass - O(n) time, O(1) space
 *   First pass: Set all invalid positions to -1
 *   Second pass: Place elements at correct positions
 * 
 * Time: O(n) - single or double pass
 * Space: O(1) - constant extra space (optimal method)
 */

#include <iostream>
#include <algorithm> 
#include <vector>
using namespace std;

void modifyArray(vector<int>& arr) {
    int i = 0;
    while (i < arr.size()) {
    
        // Swap if the element arr[i] is not at arr[arr[i]]
        if (arr[i] != -1 && arr[i] != arr[arr[i]]) {
            swap(arr[i], arr[arr[i]]);
        
        } else {
        
            // Increment i if element is at its correct position
            i++;
        }
    }
}