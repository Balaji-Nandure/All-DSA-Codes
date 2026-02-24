/*
 * Problem: Convert array into Zig-Zag fashion
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/convert-array-into-zig-zag-fashion/0
 * 
 * Given an array arr of distinct elements, the task is to rearrange the elements 
 * of the array in a zig-zag fashion so that the converted array should be in the 
 * below form: 
 * 
 * arr[0] < arr[1] > arr[2] < arr[3] > arr[4] < . . . . arr[n-2] < arr[n-1] > arr[n].
 * 
 * Note: Modify the given arr[] only, If your transformation is correct, the output 
 * will be "true" else the output will be "false".
 * 
 * Examples:
 * Input: arr[] = [4, 3, 7, 8, 6, 2, 1]
 * Output: true
 * Explanation: After modification the array will look like 3 < 7 > 4 < 8 > 2 < 6 > 1, 
 *              the checker in the driver code will produce 1.
 * 
 * Input: arr[] = [4, 7, 3, 8, 2]
 * Output: true
 * Explanation: After modification the array will look like 4 < 7 > 3 < 8 > 2 hence 
 *              output will be 1.
 * 
 * Input: arr[] = [2, 8, 1, 7, 5, 9]
 * Output: true
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 0 ≤ arr[i] ≤ 10^8
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Single pass through array to create zig-zag pattern
 * - For even indices: ensure arr[i] < arr[i+1]
 * - For odd indices: ensure arr[i] > arr[i+1]
 * - If condition is not met, swap the elements
 * - This greedy approach ensures local zig-zag property
 * - Local property guarantees global zig-zag pattern
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - in-place modifications only
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void zigZag(vector<int>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            
            // If index is even, next element should be greater
            if (i % 2 == 0) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
            // If index is odd, next element should be smaller
            else {
                if (arr[i] < arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
        }
    }
};
