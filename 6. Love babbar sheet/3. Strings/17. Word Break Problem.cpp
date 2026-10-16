// Problem: Word Break Problem [Very Imp]
// Link (GFG): https://www.geeksforgeeks.org/problems/word-break1352/1
// Article: https://www.geeksforgeeks.org/dsa/word-break-problem-dp-32/
// Difficulty: Medium / Hard
// Topic: String, Dynamic Programming, Trie / Hash Set

/*
Problem Statement:
Given a string s and a dictionary of words `dictionary`. 
Determine if s can be segmented into a space-separated sequence of one or more dictionary words.
The same word in the dictionary may be reused multiple times in the segmentation.

Example 1:
Input:
s = "leetcode"
dictionary = ["leet", "code"]
Output: true
Explanation: "leetcode" can be segmented as "leet code".

Example 2:
Input:
s = "applepenapple"
dictionary = ["apple", "pen"]
Output: true
Explanation: "applepenapple" can be segmented as "apple pen apple".

Example 3:
Input:
s = "catsandog"
dictionary = ["cats", "dog", "sand", "and", "cat"]
Output: false

Constraints:
- 1 <= s.length <= 1000
- 1 <= dictionary.size() <= 1000
- 1 <= dictionary[i].length <= 100
- s and dictionary words consist of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Word Wrap Problem (Problem 13):
//   * Words were given in fixed sequential order; we chose where to break lines.
// - In Word Break Problem:
//   * There are NO spaces in the input string `s`! We must discover whether ANY valid 
//     sequence of dictionary words can stitch together to form `s`.
//   * A naive greedy prefix match fails:
//     E.g., s = "cars", dict = ["car", "ca", "rs"].
//     Matching "car" first leaves "s", which cannot be formed. But matching "ca" allows "rs"!
//   * Therefore, DP is required to verify all viable partition prefixes.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: 1D Dynamic Programming with Hash Set (Optimal & Chosen)
//   - Convert `dictionary` into an `unordered_set<string> dict` for O(1) lookups.
//   - Find `maxWordLen` among dictionary words to cap inner loop checks.
//   - Let `dp[i]` be a boolean indicating whether prefix `s[0 .. i - 1]` can be segmented.
//   - Base case: `dp[0] = true` (empty prefix is trivially valid).
//   - For `i` from 1 to `n`:
//       * Check previous split point `j` from `i - 1` down to `max(0, i - maxWordLen)`:
//           If `dp[j]` is true AND `dict.count(s.substr(j, i - j))`:
//             `dp[i] = true; break;`
//   - Return `dp[n]`.
//   - Complexity: O(N * maxWordLen) time, O(N + D) auxiliary space.
//   - Why this approach: Pruning inner loop with `maxWordLen` makes it blazingly fast.

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, const vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.length();

        // Find the maximum length of a word in the dictionary for loop bounding
        int maxWordLen = 0;
        for (const string& w : wordDict) {
            maxWordLen = max(maxWordLen, (int)w.length());
        }

        // dp[i] is true if prefix s[0 .. i-1] can be segmented using dictionary words
        vector<bool> dp(n + 1, false);
        dp[0] = true; // Base case: empty string

        for (int i = 1; i <= n; ++i) {
            // Only search backwards up to maxWordLen characters
            int startBound = max(0, i - maxWordLen);

            for (int j = i - 1; j >= startBound; --j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Subproblem decomposition: If the prefix up to index j is ALREADY validly segmented (dp[j] == true),
                // and the remaining piece s[j .. i-1] exists as a standalone dictionary word,
                // then the prefix up to index i is also completely valid!
                if (dp[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
                    dp[i] = true;
                    break; // Found one valid decomposition, no need to check other j values
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};
    cout << "WordBreak (\"" << s1 << "\"): " 
         << (sol.wordBreak(s1, dict1) ? "True" : "False") << "\n";

    string s2 = "applepenapple";
    vector<string> dict2 = {"apple", "pen"};
    cout << "WordBreak (\"" << s2 << "\"): " 
         << (sol.wordBreak(s2, dict2) ? "True" : "False") << "\n";

    string s3 = "catsandog";
    vector<string> dict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << "WordBreak (\"" << s3 << "\"): " 
         << (sol.wordBreak(s3, dict3) ? "True" : "False") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * maxWordLen * L) where N is length of s, and maxWordLen is longest word.
  * For N = 1000 and maxWordLen = 20: ~20,000 iterations (executes in < 1 ms).
- Space Complexity: O(N + D) where N is for the DP vector and D is for the hash set of dictionary words.

Key Takeaways:
- Capping the backward scan `j >= max(0, i - maxWordLen)` turns an O(N^2) quadratic algorithm 
  into a near-linear O(N * K) practical routine.
*/
