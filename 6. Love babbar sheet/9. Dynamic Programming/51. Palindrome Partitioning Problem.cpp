#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Palindrome Partitioning Problem (Minimum Cuts)
 * 
 * Given a string str, find the MINIMUM number of cuts needed such that every 
 * resulting partitioned substring is a palindrome.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Category 8, problem 7, we PRINTED all palindromic partitions using Backtracking.
 * - Here, we want to MINIMIZE the integer count of cuts.
 * - While naive interval MCM-style DP takes O(N^3), 1D DP with precomputed palindrome 
 *   table achieves strictly O(N^2) time!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Dynamic Programming with Precomputed Palindrome Table:
 *   Step 1: 2D Palindrome Table in O(N^2):
 *     isPalin[i][j] = true if str[i ... j] is a palindrome.
 *     isPalin[i][j] = (str[i] == str[j]) && (j - i <= 2 || isPalin[i + 1][j - 1]).
 *   
 *   Step 2: 1D Minimum Cuts Recurrence:
 *     Let cuts[i] be the minimum cuts needed to partition prefix str[0 ... i].
 *     
 *     If isPalin[0][i] is true:
 *       The entire prefix str[0 ... i] is already a palindrome!
 *       cuts[i] = 0 (zero cuts required).
 *     
 *     Else:
 *       We must make a cut before some index j (1 <= j <= i).
 *       If the suffix str[j ... i] is a palindrome (isPalin[j][i] is true):
 *         cuts[i] = min(cuts[i], 1 + cuts[j - 1])
 *   
 *   Result:
 *     cuts[N - 1] gives the minimum cuts for the entire string.
 */

class Solution {
public:
    int palindromicPartition(string str) {
        int n = str.length();
        if (n <= 1) return 0;

        // Step 1: Precompute isPalin table in O(N^2)
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) isPalin[i][i] = true;

        for (int L = 2; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;
                if (str[i] == str[j]) {
                    isPalin[i][j] = (L == 2) ? true : isPalin[i + 1][j - 1];
                }
            }
        }

        // Step 2: 1D DP for minimum cuts in O(N^2)
        vector<int> cuts(n, 0);

        for (int i = 0; i < n; i++) {
            // If prefix str[0 ... i] is already a palindrome, no cut needed
            if (isPalin[0][i]) {
                cuts[i] = 0;
            } else {
                cuts[i] = INT_MAX;
                // Test all possible last palindromic chunks str[j ... i]
                for (int j = 1; j <= i; j++) {
                    if (isPalin[j][i]) {
                        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                        // 1 cut between (j-1) and j, plus optimal cuts for prefix str[0...j-1]
                        cuts[i] = min(cuts[i], 1 + cuts[j - 1]);
                    }
                }
            }
        }

        return cuts[n - 1];
    }
};

int main() {
    Solution sol;
    string s1 = "ababbbabbababa";
    cout << "Min cuts 1: " << sol.palindromicPartition(s1) << "\n"; // Expected: 3

    string s2 = "aaabba";
    cout << "Min cuts 2: " << sol.palindromicPartition(s2) << "\n"; // "aa" | "abba" -> 1 cut. Expected: 1.

    string s3 = "abcde";
    cout << "Min cuts 3: " << sol.palindromicPartition(s3) << "\n"; // 'a'|'b'|'c'|'d'|'e' -> 4 cuts. Expected: 4.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2). Precomputing palindrome table takes O(N^2), and 1D DP loop takes O(N^2).
 * - Space Complexity: O(N^2) for the 2D boolean palindrome matrix.
 */
