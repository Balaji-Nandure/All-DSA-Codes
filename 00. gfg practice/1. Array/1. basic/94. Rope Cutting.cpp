/*
Problem: Rope Cutting

Approach:
1. Sort the array
2. Traverse and find points where value changes
3. At each change, remaining ropes = n - index

Why it works:
- Each distinct value represents a new cut operation
- All smaller ropes are already removed

Time Complexity: O(n log n)
Space Complexity: O(1) (excluding output)

GFG: https://www.geeksforgeeks.org/problems/rope-cutting/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> ropeCutting(vector<int>& arr) {
        
        int n = arr.size();

        // Step 1: Sort
        sort(arr.begin(), arr.end());

        vector<int> result;

        // Step 2: Traverse
        for (int i = 1; i < n; i++) {
            if (arr[i] != arr[i - 1]) {
                result.push_back(n - i);
            }
        }

        return result;
    }
};
