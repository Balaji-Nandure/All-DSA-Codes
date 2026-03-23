/*
Problem: Maximum prefix sum for a given range

GFG: https://www.geeksforgeeks.org/problems/maximum-prefix-sum-for-a-given-range/1

Description: Given an array arr[] and a list of queries. Each query consists of two indices, leftIndex and rightIndex, defining a range in the array. For each query, calculate the maximum prefix sum within the given range.

A prefix sum is the sum of all elements from the start of the range up to a certain point within the range.

Examples:

Input: arr = [-1, 2, 3, -5], leftIndex = [0, 1], rightIndex = [3, 3]
Output:[4, 5]
Explanation:For the range [0, 3], the prefix sums are [-1, 1, 4, -1]. The maximum is 4. For the range [1, 3], the prefix sums are [2, 5, 0]. The maximum is 5.
Input: arr = [1, -2, 3, 4, -5], leftIndex = [0, 2, 1], rightIndex = [4, 3, 3]
Output: [6, 7, 5]
Explanation: For the range [0, 4], the prefix sums are [1, -1, 2, 6, 1]. The maximum is 6. For the range [2, 3], the prefix sums are [3, 7]. The maximum is 7. For the range [1, 3], the prefix sums are [-2, 1, 5]. The maximum is 5.

Constraints:
1 ≤ arr.size() ≤ 10^6
-10^4 ≤ arr[i] ≤ 10^4
1 ≤ queries ≤ 10^4
0 ≤ leftIndex[i] ≤ rightIndex[i] < arr.size()

Approach:
For each query:
1. Start from L
2. Keep adding elements till R
3. Track maximum sum during traversal

Why it works:
- We directly simulate prefix sum inside the range

Time Complexity: O(arr.size() * queries)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxPrefixSum(vector<int>& arr, vector<int>& L, vector<int>& R) {
        
        int q = L.size();
        vector<int> result;

        for (int i = 0; i < q; i++) {
            
            int left = L[i];
            int right = R[i];

            int sum = 0;
            int maxi = INT_MIN;

            // Traverse from L to R
            for (int j = left; j <= right; j++) {
                sum += arr[j];           // build prefix
                maxi = max(maxi, sum);   // track max
            }

            result.push_back(maxi);
        }

        return result;
    }
};
