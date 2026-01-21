#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Longest Bitonic Subsequence
LeetCode: Similar to 673. Number of Longest Increasing Subsequence
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1

Given an array of positive integers, find the length of the longest bitonic subsequence.
A bitonic subsequence is a subsequence that first increases and then decreases.

A subsequence is called bitonic if it is first increasing and then decreasing.
A strictly increasing or strictly decreasing subsequence is also considered bitonic.

Constraints:
- 1 <= n <= 10^3
- 1 <= arr[i] <= 10^6

Example:
arr = [1, 11, 2, 10, 4, 5, 2, 1]
Longest Bitonic Subsequence: [1, 2, 10, 5, 2, 1] or [1, 2, 4, 5, 2, 1]
Length = 6

Key Insight:
- A bitonic subsequence has two parts: increasing part (left) and decreasing part (right)
- For each index i, we need:
  - LIS[i] = length of longest increasing subsequence ending at i (from left)
  - LDS[i] = length of longest decreasing subsequence starting at i (from right)
  - Bitonic length at i = LIS[i] + LDS[i] - 1 (subtract 1 because element at i is counted twice)
- Return the maximum bitonic length over all indices

DP State:
- lis[i] = length of longest increasing subsequence ending at index i
- lds[i] = length of longest decreasing subsequence starting at index i

Recurrence for LIS:
- lis[i] = 1 + max(lis[j]) for all j < i where arr[j] < arr[i]
- If no such j exists, lis[i] = 1

Recurrence for LDS:
- lds[i] = 1 + max(lds[j]) for all j > i where arr[j] < arr[i]
- If no such j exists, lds[i] = 1

Base Cases:
- lis[0] = 1
- lds[n-1] = 1

Time Complexity: O(n^2) where n is the array size
Space Complexity: O(n) for lis and lds arrays
*/

// 4. Space Optimization (Same as tabulation, already O(n) space)
// Note: The tabulation approach already uses O(n) space, which is optimal.
class Solution {
public:
    // TC: O(n^2), SC: O(n) for lis and lds arrays
    int longestBitonicSubsequence(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        
        // longest increasing subsequence
        vector<int> lis(n, 1);
        
        // Compute LIS from left to right
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    lis[i] = max(lis[i], 1 + lis[j]);
                }
            }
        }
        
        // longest decreasing subsequence
        vector<int> lds(n, 1);
        
        // Compute LDS from right to left
        for (int i = n - 2; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (arr[j] < arr[i]) {
                    lds[i] = max(lds[i], 1 + lds[j]);
                }
            }
        }
        
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            // lis[i] + lds[i] - 1 this is bitonic formula
            maxLen = max(maxLen, lis[i] + lds[i] - 1);
        }
        
        return maxLen;
    }
};
