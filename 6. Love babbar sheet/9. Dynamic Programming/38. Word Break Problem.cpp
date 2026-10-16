#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/**
 * Problem: Word Break Problem (Decision Version)
 * 
 * Given a string s and a dictionary of words dict, determine if s can be segmented 
 * into a space-separated sequence of one or more dictionary words. Return 1 if true, 0 if false.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Category 8, problem 3 ("Word Break II"), we used Backtracking to RECONSTRUCT 
 *   every possible segmented sentence (exponential combinations).
 * - Here, we only need a BOOLEAN decision: "Is it possible to segment s?".
 * - 1D Dynamic Programming solves this in O(N^2) polynomial time, avoiding exponential blowup.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Prefix Dynamic Programming:
 *   Let dp[i] be a boolean indicating whether the prefix s[0 ... i - 1] of length i 
 *   can be segmented into valid dictionary words.
 *   
 *   Base Case:
 *     dp[0] = true (empty prefix is trivially valid).
 *   
 *   Transitions for i from 1 to N:
 *     For every previous partition split point j from 0 to i - 1:
 *       If dp[j] == true (prefix s[0 ... j-1] is validly segmented):
 *         Check if the remaining substring s[j ... i - 1] is present in the dictionary.
 *         If YES:
 *           dp[i] = true
 *           break (no need to test further split points j for this i).
 *   
 *   Result:
 *     dp[N] indicates whether the entire string of length N is validly segmentable.
 */

class Solution {
public:
    int wordBreak(string A, vector<string>& B) {
        unordered_set<string> dict(B.begin(), B.end());
        int n = A.length();

        // dp[i] is true if prefix A[0...i-1] can be segmented
        vector<bool> dp(n + 1, false);

        // Base case: empty prefix
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If prefix A[0...j-1] is valid AND substring A[j...i-1] exists in dictionary
                if (dp[j]) {
                    string word = A.substr(j, i - j);
                    if (dict.find(word) != dict.end()) {
                        dp[i] = true;
                        break; // Found valid segmentation for prefix of length i; advance
                    }
                }
            }
        }

        return dp[n] ? 1 : 0;
    }
};

int main() {
    Solution sol;
    vector<string> dict1 = {"i", "like", "sam", "sung", "samsung", "mobile", "ice", "cream", "icecream", "man", "go", "mango"};
    string s1 = "ilike";
    cout << "Can break \"" << s1 << "\": " << sol.wordBreak(s1, dict1) << "\n"; // Expected: 1

    string s2 = "idontlike";
    cout << "Can break \"" << s2 << "\": " << sol.wordBreak(s2, dict1) << "\n"; // Expected: 0

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2 * L) where N is length of string and L is the average substring lookup length.
 * - Space Complexity: O(N) for the 1D dp table + O(dictionary_size) for the hash set.
 */
