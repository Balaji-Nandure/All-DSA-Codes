/*
 * Problem: Reverse an Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/reverse-an-array/0
 * LeetCode: https://leetcode.com/problems/reverse-string/ (for strings)
 * 
 * Given an array arr[] of size N, reverse the array.
 * 
 * Example 1:
 * Input: N = 5, arr[] = {1, 2, 3, 4, 5}
 * Output: {5, 4, 3, 2, 1}
 * 
 * Example 2:
 * Input: N = 4, arr[] = {10, 20, 30, 40}
 * Output: {40, 30, 20, 10}
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - 0 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Use two pointers: one at start, one at end
 * - Swap elements at these positions
 * - Move pointers towards center until they meet
 * 
 * Time: O(n) - single pass through half the array
 * Space: O(1) - in-place reversal, constant extra space
 */

#include <bits/stdc++.h>
using namespace std;
class Solution {

public:
    void reverseArray(vector<int>& arr) {
        int n = arr.size();
        int left = 0, right = n - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }

};
