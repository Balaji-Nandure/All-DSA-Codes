/*
Problem: Kadane's Algorithm (Maximum Subarray Sum)

GFG: https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1

Description: Given an integer array arr[], find maximum sum of a contiguous subarray.

Examples:

Input: [2, 3, -8, 7, -1, 2, 3]
Output: 11
Explanation: The subarray [7, -1, 2, 3] has the largest sum 11.

Input: [-2, -4]
Output: -2
Explanation: The subarray [-2] has the largest sum -2.

Constraints:
1 ≤ arr.size() ≤ 105
-104 ≤ arr[i] ≤ 104

Approach:
We maintain two variables:
1. currentSum → sum of current subarray
2. maxSum → best sum seen so far

Logic:
- Add current element to currentSum
- Update maxSum
- If currentSum becomes negative → reset it to 0
  (Because negative sum will only reduce future sum)

Why it works:
If running sum becomes negative, it is useless to carry it forward,
so we start a new subarray.

Edge Case:
If all elements are negative → return the largest element.

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarraySum(vector<int> &arr) {
        int n = arr.size();

        int currentSum = arr[0];
        int maxSum = arr[0];

        for (int i = 1; i < n; i++) {
            // Either extend previous subarray OR start new subarray
            currentSum = max(arr[i], currentSum + arr[i]);

            // Update maximum sum found so far
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};
