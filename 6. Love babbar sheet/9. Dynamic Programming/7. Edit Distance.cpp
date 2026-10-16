#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Edit Distance (Levenshtein Distance)
 * 
 * Given two strings s and t, find the minimum number of operations required to convert s into t.
 * Allowed operations:
 *   1. Insert a character
 *   2. Remove a character
 *   3. Replace a character
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike LCS (Longest Common Subsequence) where we only delete characters,
 *   here 3 distinct operations are allowed: Insert, Delete, and Replace.
 * - Replace costs 1 operation and aligns both strings diagonally without extending length.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D / 1D Space-Optimized Dynamic Programming:
 *   Let dp[i][j] be the edit distance between s[0 ... i-1] and t[0 ... j-1].
 *   
 *   Base Cases:
 *     dp[i][0] = i (must delete all i characters of s to match empty string t).
 *     dp[0][j] = j (must insert all j characters of t into empty string s).
 *   
 *   Recurrence Relations:
 *     If s[i-1] == t[j-1]:
 *       dp[i][j] = dp[i-1][j-1] (characters match; 0 operation cost).
 *     Else:
 *       dp[i][j] = 1 + min({
 *         dp[i][j-1],    // Insert t[j-1] into s
 *         dp[i-1][j],    // Delete s[i-1] from s
 *         dp[i-1][j-1]   // Replace s[i-1] with t[j-1]
 *       });
 *   
 *   Space Optimization:
 *     Notice that to compute the current row, we only need the previous row `prev`
 *     and the immediate previous diagonal value. Space reduces from O(M * N) to strictly O(N).
 */

class Solution {
public:
    // O(M * N) Time and O(N) Space Optimized
    int editDistance(string s, string t) {
        int m = s.length();
        int n = t.length();

        // dp[j] stores distance between s[0...i-1] and t[0...j-1]
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        // Base case: transforming empty s to t[0...j-1] requires j insertions
        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            curr[0] = i; // Base case: transforming s[0...i-1] to empty string requires i deletions

            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Characters match: cost is 0, carry over diagonal subproblem result
                    curr[j] = prev[j - 1];
                } else {
                    // *** CRUCIAL LINE: 1 + min(Insert, Delete, Replace) ***
                    int insert_op  = curr[j - 1];
                    int delete_op  = prev[j];
                    int replace_op = prev[j - 1];
                    curr[j] = 1 + min({insert_op, delete_op, replace_op});
                }
            }

            prev = curr;
        }

        return prev[n];
    }
};

int main() {
    Solution sol;
    string s1 = "geek", t1 = "gesek";
    cout << "Edit Distance 1: " << sol.editDistance(s1, t1) << "\n"; // Expected: 1 (insert 's')

    string s2 = "gfg", t2 = "gfg";
    cout << "Edit Distance 2: " << sol.editDistance(s2, t2) << "\n"; // Expected: 0

    string s3 = "horse", t3 = "ros";
    cout << "Edit Distance 3: " << sol.editDistance(s3, t3) << "\n"; // Expected: 3 (h->r, remove 'r', remove 'e')

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M * N) where M = length of s and N = length of t.
 * - Space Complexity: O(N) auxiliary space using two 1D rows.
 */
