/*
Problem:
Longest Subarray with Majority over K

Given an integer array arr[] and an integer K,
find the length of the longest subarray in which
the count of elements strictly greater than K
is MORE than the count of elements less than or equal to K.

Formally, for a subarray:
count(arr[i] > K) > count(arr[i] <= K)

Examples:
Input  : arr = [1, 2, 3, 4, 5], K = 3
Output : 3
Explanation:
Subarray [3,4,5] → elements > K = {4,5} (2)
                  elements <= K = {3}   (1)

Input  : arr = [2, 1, 4, 3, 5], K = 3
Output : 5
Explanation:
Entire array satisfies the condition

Input  : arr = [1, 1, 1], K = 2
Output : 0


Approach (Expected / Optimal – Prefix Sum + Hashing):
1. Convert the array into a +1 / -1 form:
   - If arr[i] > K  → +1
   - Else           → -1
2. Problem reduces to finding the longest subarray
   with POSITIVE sum.
3. Maintain a running prefix sum.
4. Use a hash map to store the FIRST index
   at which each prefix sum occurs.
5. For each index i:
   - If prefixSum > 0:
       Entire subarray [0..i] is valid → length = i + 1
   - Else:
       We need the earliest index j such that:
           prefixSum[j] < prefixSum[i]
       That gives a subarray (j+1 .. i) with positive sum.
6. To achieve O(n), while iterating we:
   - Store first occurrence of each prefixSum.
   - Check if (prefixSum - 1) exists in map.

Why this works:
- Majority condition converts cleanly into a prefix-sum positivity problem.
- If prefixSum[i] > prefixSum[j], then sum(j+1..i) > 0.
- Storing first index guarantees maximum length.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/longest-subarray-with-majority-greater-than-k/

LeetCode:
No direct equivalent problem.
(Related to longest positive-sum subarray patterns)
*/

int longestSubarrayMajorityOverK(vector<int>& arr, int K) {
    unordered_map<int, int> firstIndex;

    int prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {

        // Step 1: Convert to +1 / -1
        if (arr[i] > K)
            prefixSum += 1;
        else
            prefixSum -= 1;

        // Step 2: Entire prefix is valid
        if (prefixSum > 0) {
            maxLen = i + 1;
        }

        // Step 3: Check if prefixSum - 1 occurred earlier
        if (firstIndex.count(prefixSum - 1)) {
            maxLen = max(maxLen, i - firstIndex[prefixSum - 1]);
        }

        // Step 4: Store first occurrence only
        if (!firstIndex.count(prefixSum)) {
            firstIndex[prefixSum] = i;
        }
    }

    return maxLen;
}
