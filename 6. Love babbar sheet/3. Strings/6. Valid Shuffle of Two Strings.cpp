// Problem: Check Whether a String is a Valid Shuffle of Two Strings
// Link: NA (Classic String Manipulation Interview Problem)
// Article: https://www.geeksforgeeks.org/dsa/check-if-the-given-string-is-shuffled-substring-of-another-string/
// Difficulty: Medium
// Topic: String, Two Pointers, Dynamic Programming, Frequency Matching

/*
Problem Statement:
Given two strings s1 and s2, and a third string `result`. Determine whether `result` 
is a valid shuffle of s1 and s2.

In technical interviews, there are two distinct variants of this question:
  Variant A (Order-Preserving Shuffle / Interleaving String - LeetCode 97):
    - Characters of s1 and s2 must maintain their original relative left-to-right order in `result`.
    - E.g., s1 = "aabcc", s2 = "dbbca", result = "aadbbcbcac" -> true.
  Variant B (Anagrammatic / Permutation Shuffle):
    - Characters of s1 and s2 can be shuffled in ANY order.
    - `result` must contain all characters of s1 and s2 with exact matching frequencies.

Both variants are solved and explained below.

Example 1 (Order-Preserving / Interleaving):
Input: s1 = "AB", s2 = "CD", result = "ACBD"
Output: true ('A' and 'B' preserve order; 'C' and 'D' preserve order)

Example 2:
Input: s1 = "AB", s2 = "CD", result = "CBAD"
Output: false ('B' appears before 'A', which violates s1's relative order)

Constraints:
- 1 <= s1.length(), s2.length() <= 1000
- 1 <= result.length() <= 2000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 5 (Check Rotations):
//   * A single string was shifted cyclically.
// - In Problem 6 (Valid Shuffle):
//   * TWO distinct source strings must be merged into a target string.
//   * When characters in s1 and s2 are identical (e.g., both offer character 'a'), 
//     a greedy choice fails! Choosing 'a' from s1 might trap us later, whereas choosing 
//     it from s2 would succeed.
//   * Therefore, for Variant A (order-preserving), greedy two-pointers fail and Dynamic Programming 
//     (or memoized DFS) is required!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Variant A: Dynamic Programming (Interleaving String)
//   - Condition 1: `result.length() == s1.length() + s2.length()`.
//   - Let `dp[i][j]` be true if `result[0 .. i+j-1]` is a valid shuffle of `s1[0 .. i-1]` and `s2[0 .. j-1]`.
//   - Transitions:
//       * If `s1[i - 1] == result[i + j - 1]`: `dp[i][j] = dp[i][j] || dp[i - 1][j]`
//       * If `s2[j - 1] == result[i + j - 1]`: `dp[i][j] = dp[i][j] || dp[i][j - 1]`
//   - Complexity: O(N * M) time, O(M) space (with row-level space optimization).
//
// Variant B: Frequency Matching
//   - Count frequencies of s1 and s2 in a frequency array `freq[256]`.
//   - Decrement using `result`. All counts must end at 0.
//   - Complexity: O(N + M) time, O(1) space.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Variant A: Order-Preserving Interleaving (DP with 1D space optimization)
    // -------------------------------------------------------------------------
    bool isValidInterleavedShuffle(const string& s1, const string& s2, const string& result) {
        int n = s1.length();
        int m = s2.length();

        // Guard: Total characters must match exactly
        if (n + m != (int)result.length()) {
            return false;
        }

        // dp[j] represents whether s1 prefix of length i and s2 prefix of length j form result prefix of length i+j
        vector<bool> dp(m + 1, false);

        // Base case: empty s1 and empty s2 form empty result
        dp[0] = true;

        // Initialize for i = 0 (using only s2 characters)
        for (int j = 1; j <= m; ++j) {
            dp[j] = dp[j - 1] && (s2[j - 1] == result[j - 1]);
        }

        // Fill DP table row by row for s1
        for (int i = 1; i <= n; ++i) {
            // First column: using only s1 characters
            dp[0] = dp[0] && (s1[i - 1] == result[i - 1]);

            for (int j = 1; j <= m; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // We test BOTH possibilities because both s1 and s2 might offer the matching character!
                // 1. Matched from s1: prior state was dp[j] (from previous row i - 1)
                // 2. Matched from s2: prior state is dp[j - 1] (from current row i, previous col j - 1)
                bool fromS1 = dp[j] && (s1[i - 1] == result[i + j - 1]);
                bool fromS2 = dp[j - 1] && (s2[j - 1] == result[i + j - 1]);

                dp[j] = fromS1 || fromS2;
            }
        }

        return dp[m];
    }

    // -------------------------------------------------------------------------
    // Variant B: Permutation / Frequency Shuffle (Arbitrary order allowed)
    // -------------------------------------------------------------------------
    bool isValidPermutationShuffle(const string& s1, const string& s2, const string& result) {
        if (s1.length() + s2.length() != result.length()) return false;

        int freq[256] = {0};
        for (char c : s1) freq[(unsigned char)c]++;
        for (char c : s2) freq[(unsigned char)c]++;

        for (char c : result) {
            freq[(unsigned char)c]--;
            if (freq[(unsigned char)c] < 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    string s1 = "AB";
    string s2 = "CD";

    string res1 = "ACBD";
    cout << "Is \"" << res1 << "\" a valid order-preserving shuffle? " 
         << (sol.isValidInterleavedShuffle(s1, s2, res1) ? "Yes" : "No") << "\n";

    string res2 = "CBAD";
    cout << "Is \"" << res2 << "\" a valid order-preserving shuffle? " 
         << (sol.isValidInterleavedShuffle(s1, s2, res2) ? "Yes" : "No") << "\n";

    cout << "Is \"" << res2 << "\" a valid permutation shuffle? " 
         << (sol.isValidPermutationShuffle(s1, s2, res2) ? "Yes" : "No") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Variant A (Order-Preserving / Interleaving):
  * Time Complexity: O(N * M), filling the DP table of dimensions (N+1) x (M+1).
  * Space Complexity: O(M) auxiliary space with 1D vector rolling optimization.
- Variant B (Permutation Shuffle):
  * Time Complexity: O(N + M).
  * Space Complexity: O(1) auxiliary space (256 ASCII buckets).

Key Takeaways:
- When both source strings can supply the same character, greedy branches fail; 
  dynamic programming explores both alternatives deterministically.
*/
