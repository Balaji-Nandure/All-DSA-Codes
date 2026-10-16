#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest subsequence such that difference between adjacent is one
 * 
 * Given an array a of N integers, find the length of the longest subsequence 
 * such that the absolute difference between adjacent elements in the subsequence is strictly 1:
 * |sub[i] - sub[i-1]| == 1 for all i >= 1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "16. Longest Increasing Subsequence (LIS)", any element with smaller value could precede.
 * - Here, the predecessor requirement is STRICTLY targeted: only (val - 1) and (val + 1) can precede val.
 * - Because the valid predecessors are exactly two specific values, an O(N^2) inner scan is wasteful;
 *   a hash map lookup reduces the algorithm to linear O(N) time!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Hash Map Value-Indexed Dynamic Programming in O(N) Time:
 *   Let dp[x] be the length of the longest valid subsequence ending with value x seen so far.
 *   
 *   For each element x in array a:
 *     The only numbers that can legally precede x with absolute difference 1 are:
 *     - (x - 1): sequence was increasing into x
 *     - (x + 1): sequence was decreasing into x
 *     
 *     Recurrence:
 *       dp[x] = 1 + max(dp[x - 1], dp[x + 1])
 *     
 *     Update the global maximum length:
 *       max_len = max(max_len, dp[x])
 *   
 *   This single-pass linear DP eliminates the quadratic scan completely.
 */

class Solution {
public:
    int longestSubsequence(int N, vector<int>& a) {
        unordered_map<int, int> dp;
        int max_len = 0;

        for (int x : a) {
            // Find longest subsequence ending in (x - 1) and (x + 1)
            int len_minus_1 = (dp.find(x - 1) != dp.end()) ? dp[x - 1] : 0;
            int len_plus_1  = (dp.find(x + 1) != dp.end()) ? dp[x + 1] : 0;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Extend the best valid adjacent predecessor (x - 1 or x + 1) in O(1) time
            dp[x] = 1 + max(len_minus_1, len_plus_1);

            max_len = max(max_len, dp[x]);
        }

        return max_len;
    }
};

int main() {
    Solution sol;
    vector<int> a1 = {10, 9, 4, 5, 4, 8, 6};
    int N1 = a1.size();
    cout << "Longest Subsequence Length 1: " << sol.longestSubsequence(N1, a1) << "\n";
    // Subsequence: {10, 9, 8} (diff 1) or {4, 5, 4} (length 3). Expected: 3.

    vector<int> a2 = {1, 2, 3, 2, 3, 7, 2, 1};
    int N2 = a2.size();
    cout << "Longest Subsequence Length 2: " << sol.longestSubsequence(N2, a2) << "\n";
    // Subsequence: {1, 2, 3, 2, 3, 2, 1} (length 7). Expected: 7.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear pass using O(1) hash map operations.
 * - Space Complexity: O(N) to store distinct elements in the hash map.
 */
