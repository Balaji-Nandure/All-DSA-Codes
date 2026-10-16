#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/**
 * Problem: Word Break Problem using Backtracking (Word Break II)
 * 
 * Given a string S and a dictionary of words dict, find all possible sentences 
 * formed by breaking S into valid dictionary words separated by spaces.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Word Break I only requires a boolean: "Can S be segmented?" (Solved with 1D DP).
 * - Here, we must reconstruct ALL valid sentences. Because the number of valid sentences can be 
 *   exponential, pure DP boolean tables are insufficient; we need recursive Backtracking 
 *   with Memoization to avoid re-evaluating suffixes that yield no sentences.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Suffix Memoization:
 *   Let dfs(start_idx) return all valid segmented sentence suffixes from index start_idx to end.
 *   
 *   1. Use an unordered_set<string> for O(1) dictionary word lookups.
 *   2. For current index `start`:
 *      Check every prefix substring s[start ... end]:
 *      If substring exists in dictionary:
 *        - If end == s.length() - 1: We found a complete word ending at the string's end!
 *        - Otherwise: Recursively call dfs(end + 1).
 *          Combine the current word with each suffix returned by dfs(end + 1).
 *   3. Memoization:
 *      Store memo[start] = vector<string> of all valid sentences for s[start ... n-1].
 *      This prevents duplicate branching if the same suffix is reached through multiple word splits.
 */

class Solution {
    unordered_map<int, vector<string>> memo;

    vector<string> dfs(int start, const string& s, const unordered_set<string>& dict) {
        // Return precomputed results for this suffix
        if (memo.find(start) != memo.end()) {
            return memo[start];
        }

        vector<string> sentences;
        int n = s.length();

        // Base case: Reached end of string
        if (start == n) {
            sentences.push_back("");
            return sentences;
        }

        string word = "";
        for (int i = start; i < n; i++) {
            word += s[i];

            // If the current prefix is a valid dictionary word
            if (dict.find(word) != dict.end()) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Recursively find all valid segmentations of the remaining suffix
                vector<string> suffix_sentences = dfs(i + 1, s, dict);

                for (const string& suffix : suffix_sentences) {
                    if (suffix.empty()) {
                        sentences.push_back(word);
                    } else {
                        // Stitch prefix word with segmented suffix
                        sentences.push_back(word + " " + suffix);
                    }
                }
            }
        }

        // *** CRUCIAL LINE: Memoize all valid sentences for this starting index ***
        return memo[start] = sentences;
    }

public:
    vector<string> wordBreak(int n, vector<string>& dict_words, string s) {
        memo.clear();
        unordered_set<string> dict(dict_words.begin(), dict_words.end());
        return dfs(0, s, dict);
    }
};

int main() {
    Solution sol;
    vector<string> dict = {"cats", "dog", "sand", "and", "cat"};
    string s = "catsanddog";

    vector<string> ans = sol.wordBreak(dict.size(), dict, s);
    cout << "Valid sentences for \"" << s << "\":\n";
    for (const string& sentence : ans) {
        cout << "  \"" << sentence << "\"\n";
    }
    // Expected output:
    // "cats and dog"
    // "cat sand dog"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * 2^N) in the worst case (where every prefix is valid, e.g. "aaaa" with dict {"a", "aa"}).
 *   Memoization guarantees each unique suffix is processed once.
 * - Space Complexity: O(N * 2^N) to store all generated sentence combinations in memo table and recursion call stack.
 */
