/*
Problem: Partition Point in the Array

GFG: https://www.geeksforgeeks.org/problems/partition-point-in-the-array/1

Description: Given an array arr[] of integers. Find an element such that all the elements to its left are smaller and to its right are greater. Print -1 if no such element exists.

Note: There can be more than one such element. In that case, print the first such number occurring in the array.

Examples:

Input: arr[] = [4, 3, 2, 5, 8, 6, 7]
Output: 5
Explanation: To the left of element 5 every element is smaller to it and to its right every element is greater to it.
Input: arr[] = [5, 6, 2, 8, 10, 9, 8]
Output: -1
Explanation: No such desired element is present in the array.

Constraints:
1 ≤ arr.size() ≤ 106
1 ≤ arr[i] ≤ 106

Approach:
This is a classic prefix max + suffix min problem.

We need an element arr[i] such that:
- all elements on left < arr[i]
- all elements on right > arr[i]

This can be rewritten as:
- arr[i] > max(left side)
- arr[i] < min(right side)

So we precompute suffixMin[i] = min from i → n-1
and track leftMax on the fly.

Optimized: Use only suffixMin array + leftMax variable

Why it works:
- suffixMin ensures all right elements are greater
- leftMax tracked during traversal ensures all left elements are smaller
- First such element is found by left-to-right traversal

Time Complexity: O(n)
Space Complexity: O(n) - optimized to single auxiliary array
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findElement(vector<int>& arr) {
        int n = arr.size();
        if (n < 3) return -1;

        // Only store suffix min (right side minimums)
        vector<int> suffixMin(n);
        suffixMin[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffixMin[i] = min(suffixMin[i + 1], arr[i]);
        }

        int leftMax = arr[0];

        // Find partition point - check indices 1 to n-2
        for (int i = 1; i < n - 1; i++) {
            if (arr[i] > leftMax && arr[i] < suffixMin[i + 1]) {
                return arr[i];
            }
            leftMax = max(leftMax, arr[i]);
        }

        return -1;
    }
};
