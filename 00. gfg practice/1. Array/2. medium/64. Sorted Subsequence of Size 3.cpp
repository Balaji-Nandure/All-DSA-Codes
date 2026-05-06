/*
Problem: Sorted Subsequence of Size 3

GFG: https://www.geeksforgeeks.org/problems/sorted-subsequence-of-size-3/1

Description:
Given an array arr[], find any subsequence of three elements such that:
arr[i] < arr[j] < arr[k] and (i < j < k).

Return the three elements if possible, otherwise return empty array.

Examples:
Input: [12, 11, 10, 5, 6, 2, 30]
Output: 1 (valid subsequence: 5, 6, 30)

Input: [1, 2, 3, 4]
Output: 1 (any increasing triplet exists)

Input: [4, 3, 2, 1]
Output: 0 (no such subsequence)

Constraints:
1 ≤ N ≤ 1e5
1 ≤ arr[i] ≤ 1e6

Approach (Optimal - LeftMin + RightMax):
- Create two arrays:
  1. leftMin[i]  → smallest element from 0 to i-1
  2. rightMax[i] → largest element from i+1 to n-1

- Traverse:
  If leftMin[i] < arr[i] < rightMax[i],
  then we found valid triplet.

Why it works:
We fix middle element (arr[i]) and check:
- Is there a smaller element on left?
- Is there a greater element on right?

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> find3Numbers(vector<int> &arr) {
        
        int n = arr.size();
        
        vector<int> leftMin(n);
        vector<int> rightMax(n);
        
        // Step 1: Fill leftMin
        leftMin[0] = arr[0];
        for (int i = 1; i < n; i++) {
            leftMin[i] = min(leftMin[i - 1], arr[i]);
        }
        
        // Step 2: Fill rightMax
        rightMax[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], arr[i]);
        }
        
        // Step 3: Find valid triplet
        for (int i = 1; i < n - 1; i++) {
            
            if (leftMin[i - 1] < arr[i] && arr[i] < rightMax[i + 1]) {
                return {leftMin[i - 1], arr[i], rightMax[i + 1]};
            }
        }
        
        return {}; // No valid subsequence
    }
};
