/*
 * Problem: Three way partitioning
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/three-way-partitioning/0
 * 
 * Given an array and a range a, b. The task is to partition the array around the range 
 * such that the array is divided into three parts.
 * 1) All elements smaller than a come first.
 * 2) All elements in range a to b come next.
 * 3) All elements greater than b appear in the end.
 * The individual elements of three sets can appear in any order. You are required 
 * to return the modified array.
 * 
 * Note: The generated output is true if you modify the given array successfully. Otherwise false.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 3, 3, 4], a = 1, b = 2
 * Output: true
 * Explanation: One possible arrangement is: {1, 2, 3, 3, 4}. If you return a valid arrangement, 
 *              output will be true.
 * 
 * Input: arr[] = [1, 4, 3, 6, 2, 1], a = 1, b = 3
 * Output: true
 * Explanation: One possible arrangement is: {1, 3, 2, 1, 4, 6}. If you return a valid arrangement, 
 *              output will be true.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ array[i], a, b ≤ 10^9
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use Dutch National Flag algorithm with three pointers
 * - left pointer: boundary for elements < a
 * - mid pointer: current element being processed
 * - right pointer: boundary for elements > b
 * - Process elements until mid crosses right
 * - Swap elements to move them to correct partition
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void threeWayPartition(vector<int>& arr, int lowVal, int highVal) {
        int n = arr.size();
        int left = 0, mid = 0, right = n - 1;
        
        while (mid <= right) {
            if (arr[mid] < lowVal) {
                swap(arr[mid], arr[left]);
                left++;
                mid++;
            } else if (arr[mid] > highVal) {
                swap(arr[mid], arr[right]);
                right--;
            } else {
                mid++;
            }
        }
    }
};
