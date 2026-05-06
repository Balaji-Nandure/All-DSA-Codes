/*
Problem: Max Sum Path in Two Sorted Arrays

GFG: https://www.geeksforgeeks.org/problems/max-sum-path-in-two-arrays/1

Description:
Given two sorted arrays of distinct integers arr1 and arr2. Each array may have some elements in common with the other array. Find the maximum sum of a path from the beginning of any array to the end of any array. You can switch from one array to another array only at common elements.

Examples:

Input: arr1 = [2, 3, 7, 10, 12], arr2 = [1, 5, 7, 8]
Output: 35
Explanation: The path will be 1+5+7+10+12 = 35, where 1 and 5 come from arr2 and then 7 is common so we switch to arr1 and add 10 and 12.

Input: arr1 = [1, 2, 3], arr2 = [3, 4, 5]
Output: 15
Explanation: The path will be 1+2+3+4+5 = 15, where 1 and 2 come from arr1, 3 is common so we switch to arr2 and add 4 and 5.

Constraints:
1 ≤ arr1.size(), arr2.size() ≤ 10^4
1 ≤ arr1[i], arr2[i] ≤ 10^5

Approach (Two Pointer + Greedy):
1. i = 0, j = 0
2. sum1 = 0, sum2 = 0, result = 0
3. While both arrays not finished:
   - If arr1[i] < arr2[j]: sum1 += arr1[i++]
   - Else if arr2[j] < arr1[i]: sum2 += arr2[j++]
   - Else (common element): result += max(sum1, sum2) + arr1[i]; sum1 = sum2 = 0; i++, j++

4. Add remaining elements:
   result += max(sum1, sum2)

Why it works:
- At every common point, we have two choices: continue from arr1 or arr2
- Pick the path with maximum sum so far
- Greedy approach ensures optimal path selection

Time Complexity: O(n + m)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxPathSum(vector<int>& arr1, vector<int>& arr2) {
        
        int i = 0, j = 0;
        int n = arr1.size(), m = arr2.size();
        
        long long sum1 = 0, sum2 = 0;
        long long result = 0;
        
        while (i < n && j < m) {
            
            if (arr1[i] < arr2[j]) {
                sum1 += arr1[i++];
            }
            else if (arr2[j] < arr1[i]) {
                sum2 += arr2[j++];
            }
            else {
                // Common element
                result += max(sum1, sum2) + arr1[i];
                sum1 = sum2 = 0;
                i++, j++;
            }
        }
        
        // Add remaining elements
        while (i < n) sum1 += arr1[i++];
        while (j < m) sum2 += arr2[j++];
        
        result += max(sum1, sum2);
        
        return result;
    }
};
