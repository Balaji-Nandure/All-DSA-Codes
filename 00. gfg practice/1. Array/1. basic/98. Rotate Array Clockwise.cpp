/*
Problem: Rotate Array Clockwise

Approach:
1. k = k % n
2. Reverse entire array
3. Reverse first k elements
4. Reverse remaining elements

Time Complexity: O(n)
Space Complexity: O(1)

GFG: https://www.geeksforgeeks.org/problems/rotate-array-clockwise/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& arr, int k) {
        
        int n = arr.size();
        k = k % n;

        // Step 1: reverse whole array
        reverse(arr.begin(), arr.end());

        // Step 2: reverse first k elements
        reverse(arr.begin(), arr.begin() + k);

        // Step 3: reverse remaining elements
        reverse(arr.begin() + k, arr.end());
    }
};
