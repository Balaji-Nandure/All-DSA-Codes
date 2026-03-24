/*
Problem: Indexes of Subarray Sum

GFG: https://www.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1

Description: Given an array arr[] containing only non-negative integers, your task is to find a continuous subarray (a contiguous sequence of elements) whose sum equals a specified value target. You need to return the 1-based indices of the leftmost and rightmost elements of this subarray. You need to find the first subarray whose sum is equal to the target.

Note: If no such array is possible then, return [-1].

Examples:

Input: arr[] = [1, 2, 3, 7, 5], target = 12
Output: [2, 4]
Explanation: The sum of elements from 2nd to 4th position is 12.
Input: arr[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], target = 15
Output: [1, 5]
Explanation: The sum of elements from 1st to 5th position is 15.
Input: arr[] = [5, 3, 4], target = 2
Output: [-1]
Explanation: There is no subarray with sum 2.

Constraints:
1 ≤ arr.size() ≤ 106
0 ≤ arr[i] ≤ 103
0 ≤ target ≤ 109

Approach:
Sliding Window Technique:
- Use two pointers left and right
- Expand right to increase sum by adding arr[right]
- If sum > target, move left to reduce sum by subtracting arr[left]
- If sum == target, return 1-based indices
- Continue until end of array

Why it works:
- Array contains only non-negative numbers, so sum always increases when expanding
- Sliding window maintains current sum efficiently
- When sum exceeds target, we know we must shrink from left
- First found subarray is guaranteed to be leftmost due to sequential search

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> subarraySum(vector<int> &arr, int target) {
        int n = arr.size();

        int left = 0;
        long long sum = 0;

        for (int right = 0; right < n; right++) {
            sum += arr[right];  // expand window

            // shrink window if sum > target
            while (sum > target && left <= right) {
                sum -= arr[left];
                left++;
            }

            // if sum found
            if (sum == target) {
                return {left + 1, right + 1}; // 1-based index
            }
        }

        return {-1};
    }
};
