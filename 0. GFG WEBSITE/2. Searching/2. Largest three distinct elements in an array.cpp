/*
 * Problem: Largest three distinct elements in an array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-the-largest-three-elements-in-an-array/
 * Practice: https://practice.geeksforgeeks.org/problems/three-largest-elements4206/1
 * 
 * Given an array of integers, find the largest three distinct elements.
 * 
 * Example 1:
 * Input: arr[] = {10, 4, 3, 50, 23, 90}
 * Output: 90, 50, 23
 * Explanation: Largest three distinct elements are 90, 50, and 23
 * 
 * Example 2:
 * Input: arr[] = {12, 13, 1, 10, 34, 1}
 * Output: 34, 13, 12
 * Explanation: Largest three distinct elements are 34, 13, and 12
 * 
 * Example 3:
 * Input: arr[] = {10, 10, 10}
 * Output: 10
 * Explanation: Only one distinct element exists
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 1 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Single Pass Iterative (Optimal) - O(n) time, O(1) space
 *   Track first, second, and third largest in single iteration
 *   Handle duplicates by checking if element is different from tracked values
 * 
 * Time: O(n) - single pass (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Single Pass Iterative - O(n) Time and O(1) Space
    vector<int> find3Largest(vector<int>& arr) {
        int n = arr.size();
        vector<int> result;
        
        if (n == 0) return result;
        
        int first = INT_MIN;
        int second = INT_MIN;
        int third = INT_MIN;
        
        // Iterate through array once
        for (int i = 0; i < n; i++) {
            // If current element is greater than first
            if (arr[i] > first) {
                third = second;
                second = first;
                first = arr[i];
            }
            // If current element is between first and second (and distinct)
            else if (arr[i] > second && arr[i] != first) {
                third = second;
                second = arr[i];
            }
            // If current element is between second and third (and distinct)
            else if (arr[i] > third && arr[i] != first && arr[i] != second) {
                third = arr[i];
            }
        }
        
        // Add distinct largest elements to result
        if (first != INT_MIN) {
            result.push_back(first);
        }
        if (second != INT_MIN) {
            result.push_back(second);
        }
        if (third != INT_MIN) {
            result.push_back(third);
        }
        
        return result;
    }
};