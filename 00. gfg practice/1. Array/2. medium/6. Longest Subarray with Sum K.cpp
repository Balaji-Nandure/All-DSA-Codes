/*
Problem: Longest Subarray with Sum K

GFG: https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1

Description: Given an array arr[] containing integers and an integer k, your task is to find the length of the longest subarray where the sum of its elements is equal to the given value k. If there is no subarray with sum equal to k, return 0.

Examples:

Input: arr[] = [10, 5, 2, 7, 1, -10], k = 15
Output: 6
Explanation: Subarrays with sum = 15 are [5, 2, 7, 1], [10, 5] and [10, 5, 2, 7, 1, -10]. The length of the longest subarray with a sum of 15 is 6.
Input: arr[] = [-5, 8, -14, 2, 4, 12], k = -5
Output: 5
Explanation: Subarrays with sum = -5 are [-5] and [-5, 8, -14, 2, 4]. The length of the longest subarray with a sum of -5 is 5.
Input: arr[] = [10, -10, 20, 30], k = 5
Output: 0
Explanation: No subarray with sum = 5 is present in arr[].

Constraints:
1 ≤ arr.size() ≤ 105
-104 ≤ arr[i] ≤ 104
-109 ≤ k ≤ 109

Approach:
Prefix Sum + HashMap (Optimal):
Store first occurrence of prefix sum.

Formula:
prefixSum[j] - prefixSum[i] = k
=> prefixSum[i] = prefixSum[j] - k

Algorithm:
1. Initialize sum = 0, maxLen = 0, hashmap
2. For each index i:
   - sum += arr[i]
   - If sum == k: maxLen = i + 1
   - If (sum - k) exists in map: 
     * len = i - mp[sum - k]
     * maxLen = max(maxLen, len)
   - Store first occurrence of sum only

Why it works:
- Prefix sum gives sum of subarray [0..i]
- If prefixSum[j] - prefixSum[i] = k, then subarray [i+1..j] has sum k
- HashMap provides O(1) lookup for previous prefix sums

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& arr, int k) {
        unordered_map<long long, int> mp;
        
        long long sum = 0;
        int maxLen = 0;

        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];

            if (sum == k)
                maxLen = i + 1;

            if (mp.find(sum - k) != mp.end()) {
                int len = i - mp[sum - k];
                maxLen = max(maxLen, len);
            }

            // store first occurrence only
            if (mp.find(sum) == mp.end())
                mp[sum] = i;
        }

        return maxLen;
    }
};
