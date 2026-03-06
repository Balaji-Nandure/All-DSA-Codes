/*
 * Problem: Number of occurrence
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/number-of-occurrence/0
 * 
 * Given a sorted array, arr[] and a number target, you need to find the 
 * number of occurrences of target in arr[].
 * 
 * Examples:
 * Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 2
 * Output: 4
 * Explanation: target = 2 occurs 4 times in the given array so the output is 4.
 * 
 * Input: arr[] = [1, 1, 2, 2, 2, 2, 3], target = 4
 * Output: 0
 * Explanation: target = 4 is not present in the given array so the output is 0.
 * 
 * Input: arr[] = [8, 9, 10, 12, 12, 12], target = 12
 * Output: 3
 * Explanation: target = 12 occurs 3 times in the given array so the output is 3.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 1 ≤ target ≤ 10^6
 * 
 * Expected Time Complexity: O(log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Since the array is sorted, we can use binary search to find the target
 * - Find the first occurrence of target using binary search
 * - Find the last occurrence of target using binary search
 * - The count is (last occurrence index - first occurrence index + 1)
 * - If target is not found, return 0
 * 
 * Time: O(log n) - two binary searches
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countOccurrences(vector<int>& arr, int target) {
        int n = arr.size();
        int first = -1, last = -1;
        
        // Binary search for first occurrence
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                first = mid;
                right = mid - 1; // Look for earlier occurrence
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // If target not found, return 0
        if (first == -1) return 0;
        
        // Binary search for last occurrence
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                last = mid;
                left = mid + 1; // Look for later occurrence
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return last - first + 1;
    }
};
