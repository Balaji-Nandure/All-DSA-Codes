/*
 * Problem: Find Second Largest Element in Array/Vector
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-second-largest-element-array/
 * Practice: https://practice.geeksforgeeks.org/problems/second-largest3735/1
 * 
 * Given an array of integers, find the second largest element.
 * 
 * Example 1:
 * Input: arr[] = {12, 35, 1, 10, 34, 1}
 * Output: 34
 * Explanation: Largest is 35, second largest is 34
 * 
 * Example 2:
 * Input: arr[] = {10, 5, 10}
 * Output: 5
 * Explanation: Largest is 10, second largest is 5
 * 
 * Example 3:
 * Input: arr[] = {10, 10, 10}
 * Output: -1
 * Explanation: All elements are same, no second largest
 * 
 * Constraints:
 * - 2 <= n <= 10^5
 * - 1 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Method 1: Two Pass (Iterative) - O(n) time, O(1) space
 *   First pass: find largest
 *   Second pass: find largest element smaller than largest
 * 
 * - Method 2: Single Pass (Iterative) - O(n) time, O(1) space
 *   Track largest and second largest in single iteration
 * 
 * - Method 3: Sorting (Iterative) - O(n log n) time, O(1) space
 *   Sort array, find second largest
 * 
 * Time: O(n) - single pass (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Single Pass Iterative - O(n) Time and O(1) Space
    int getSecondLargest(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) return -1;
        
        int largest = INT_MIN;
        int secondLargest = INT_MIN;
        
        // Iterate through array once
        for (int i = 0; i < n; i++) {
            if (arr[i] > largest) {
                // New largest found, update second largest to previous largest
                secondLargest = largest;
                largest = arr[i];
            } else if (arr[i] > secondLargest && arr[i] != largest) {
                // Update second largest if current element is greater than second largest
                // but not equal to largest
                secondLargest = arr[i];
            }
        }
        
        return secondLargest;
    }
    
};