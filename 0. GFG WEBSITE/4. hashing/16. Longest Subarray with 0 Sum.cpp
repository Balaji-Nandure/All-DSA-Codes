/*
Problem:
Longest Subarray with 0 Sum

Given an integer array arr[], find the length of the longest subarray
whose sum is equal to 0.

Examples:
Input  : arr = [15, -2, 2, -8, 1, 7, 10, 23]
Output : 5
Explanation:
Subarray [-2, 2, -8, 1, 7] has sum 0 and length 5

Input  : arr = [1, 2, 3]
Output : 0

Input  : arr = [0, 0, 0]
Output : 3


Approach (Expected / Optimal – Prefix Sum + Hashing):
1. Maintain a running prefix sum.
2. Use an unordered_map to store the FIRST index at which
   each prefix sum is seen.
3. If prefixSum becomes 0 at index i:
   - Subarray from index 0 to i has sum 0 → length = i + 1.
4. If the same prefixSum appears again at index i:
   - The subarray between (previousIndex + 1) and i has sum 0.
   - Update maximum length.
5. Store prefixSum in map only if it is not already present
   (we need the earliest index to maximize length).

Why this works:
- If two prefix sums are equal, their difference (subarray sum) is 0.
- Storing the earliest occurrence ensures the longest subarray.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/

LeetCode:
https://leetcode.com/problems/contiguous-array/
(Related problem: longest subarray with equal number of 0s and 1s)
*/

int longestSubarrayZeroSum(vector<int>& arr) {
    unordered_map<int, int> firstIndex;

    int prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        prefixSum += arr[i];

        // Case 1: Subarray from 0 to i has sum 0
        if (prefixSum == 0) {
            maxLen = i + 1;
        }

        // Case 2: Same prefix sum seen before
        if (firstIndex.count(prefixSum)) {
            maxLen = max(maxLen, i - firstIndex[prefixSum]);
        } 
        // Store first occurrence only
        else {
            firstIndex[prefixSum] = i;
        }
    }

    return maxLen;
}
