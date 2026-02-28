/*
 * Problem: Modify the Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/modify-the-array/1
 * 
 * Given an array arr. Return the modified array in such a way that if the current 
 * and next numbers are valid numbers and are equal then double the current number 
 * value and replace the next number with 0. After the modification, rearrange the 
 * array such that all 0's are shifted to the end.
 * 
 * Note:
 * Assume '0' as the invalid number and all others as a valid number.
 * The sequence of the valid numbers is present in the same order.
 * 
 * Examples:
 * Input: arr[] = [2, 2, 0, 4, 0, 8]
 * Output: [4, 4, 8, 0, 0, 0]
 * Explanation: At index 0 and 1 both the elements are the same. So, we will change 
 *              the element at index 0 to 4 and the element at index 1 is 0 then we 
 *              will shift all the zeros to the end of the array. So, the array will 
 *              become [4, 4, 8, 0, 0, 0].
 * 
 * Input: arr[] = [0, 2, 2, 2, 0, 6, 6, 0, 0, 8]
 * Output: [4, 2, 12, 8, 0, 0, 0, 0, 0, 0]
 * Explanation: At index 5 and 6 both the elements are the same. So, we will change 
 *              the element at index 5 to 12 and the element at index 6 is 0. We will 
 *              change the element at index 1 to 4 and the element at index 2 is 0. 
 *              Then we shift all the zeros to the end of the array. So, array will 
 *              become [4, 2, 12, 8, 0, 0, 0, 0, 0, 0].
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - First pass: iterate through array and double adjacent equal non-zero elements
 * - When arr[i] == arr[i+1] != 0, set arr[i] *= 2, arr[i+1] = 0, skip next
 * - Second pass: collect all non-zero elements in order, then append zeros
 * - Use index pointer to place non-zero elements at front
 * - Fill remaining positions with zeros
 * - Maintains relative order of non-zero elements
 * 
 * Time: O(n) - two passes through array
 * Space: O(n) - in-place modification
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> modifyArray(vector<int>& arr) {
        
        int n = arr.size();
        
        // Step 1: Double equal adjacent non-zero elements
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] != 0 && arr[i] == arr[i + 1]) {
                arr[i] *= 2;
                arr[i + 1] = 0;
                i++; // skip next
            }
        }
        
        // Step 2: Move all non-zero elements to front
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] != 0) {
                arr[index++] = arr[i];
            }
        }
        
        // Fill remaining with zeros
        while (index < n) {
            arr[index++] = 0;
        }
        
        return arr;
    }
};
