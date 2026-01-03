/*
Problem:
Longest Subarray With Sum Divisible By K

Given an integer array arr[] and an integer K,
find the length of the longest subarray whose sum is divisible by K.

Examples:
Input  : arr = [2, 7, 6, 1, 4, 5], K = 3
Output : 4
Explanation:
Subarray [7, 6, 1, 4] has sum = 18, which is divisible by 3

Input  : arr = [-2, 2, -5, 12, -11, -1, 7], K = 3
Output : 5

Input  : arr = [1, 2, 3], K = 5
Output : 0


Approach (Expected / Optimal – Prefix Sum + Hashing):
1. Maintain a running prefix sum.
2. At each index i, compute remainder:
      rem = ((prefixSum % K) + K) % K   // handles negative sums
3. Use a hash map to store the first index at which a remainder appears.
4. If the same remainder occurs again at index i:
      - The subarray between the first occurrence + 1 and i
        has sum divisible by K.
      - Update maximum length.
5. Initialize remainder 0 with index -1
   (to handle subarrays starting from index 0).

Why this works:
- If two prefix sums have the same remainder modulo K,
  their difference is divisible by K.
- Storing the earliest index maximizes subarray length.

Time Complexity:
O(n)

Space Complexity:
O(k)   (at most k different remainders)


GeeksforGeeks:
https://www.geeksforgeeks.org/longest-subarray-with-sum-divisible-by-k/

LeetCode:
https://leetcode.com/problems/subarray-sums-divisible-by-k/
*/

int longestSubarrayDivByK(vector<int>& arr, int K) {
    unordered_map<int, int> firstIndex; // remainder -> first occurrence index

    int prefixSum = 0; // running prefix sum
    int maxLen = 0; // maximum length of subarray

    // Remainder 0 seen at index -1
    firstIndex[0] = -1; // remainder 0 seen at index -1

    for (int i = 0; i < arr.size(); i++) { // traverse the array
        prefixSum += arr[i];

        int rem = ((prefixSum % K) + K) % K; // remainder

        // If remainder seen before, update length
        if (firstIndex.count(rem)) {
            maxLen = max(maxLen, i - firstIndex[rem]); // update the maximum length of subarray
        } 
        // Store first occurrence only
        else {
            firstIndex[rem] = i; // store the first occurrence of remainder
        }
    }

    return maxLen; // return the maximum length of subarray
}
