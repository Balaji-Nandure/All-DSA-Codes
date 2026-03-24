/*
Problem: Smallest Positive Missing Number

GFG: https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/

Description: You are given an integer array arr[]. Your task is to find the smallest positive number missing from the array.

Note: Positive number starts from 1. The array can have negative integers too.

Examples:

Input: arr[] = [2, -3, 4, 1, 1, 7]
Output: 3
Explanation: Smallest positive missing number is 3.
Input: arr[] = [5, 3, 2, 5, 1]
Output: 4
Explanation: Smallest positive missing number is 4.
Input: arr[] = [-8, 0, -1, -4, -3]
Output: 1
Explanation: Smallest positive missing number is 1.

Constraints:
1 ≤ arr.size() ≤ 105
-106 ≤ arr[i] ≤ 106

Approach:
Place each number at its correct index.
Number x should be at index x-1.
After placement, first index where arr[i] != i+1
is the missing number.

Algorithm:
1. Initialize i = 0
2. While i < n:
   - correctIndex = arr[i] - 1
   - If arr[i] > 0 && arr[i] <= n && arr[i] != arr[correctIndex]:
     * swap(arr[i], arr[correctIndex])
   - Else: i++
3. Find first missing positive:
   - For i from 0 to n-1:
     * if arr[i] != i+1: return i+1
4. Return n+1 if all numbers 1..n are present

Why it works:
- Places each positive number at its correct index
- After placement, the first position where arr[i] != i+1 is the missing number
- Handles negative numbers and duplicates correctly

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingNumber(int arr[], int n) {
        int i = 0;

        while (i < n) {
            int correctIndex = arr[i] - 1;

            // Place arr[i] at correct position if possible
            if (arr[i] > 0 && arr[i] <= n && arr[i] != arr[correctIndex]) {
                swap(arr[i], arr[correctIndex]);
            }
            else {
                i++;
            }
        }

        // Find first missing positive
        for (int i = 0; i < n; i++) {
            if (arr[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1; // All numbers 1..n are present
    }
};
