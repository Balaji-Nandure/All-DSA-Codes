/*
 * Problem: Word Break II
 * 
 * LeetCode 140: Word Break II
 * 
 * Given a string s and a dictionary of strings wordDict, add spaces in s 
 * to construct a sentence where each word is a valid dictionary word. 
 * Return all such possible sentences in any order.
 * 
 * Note that the same word in the dictionary may be reused multiple times 
 * in the segmentation.
 * 
 * Example 1:
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 * 
 * Example 2:
 * Input: s = "pineapplepenapple", 
 *        wordDict = ["apple","pen","applepen","pine","pineapple"]
 * Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
 * Explanation: Note that you are allowed to reuse a dictionary word.
 * 
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: []
 * 
 * Constraints:
 * - 1 <= s.length <= 20
 * - 1 <= wordDict.length <= 1000
 * - 1 <= wordDict[i].length <= 10
 * - s and wordDict[i] consist of only lowercase English letters.
 * - All the strings of wordDict are unique.
 * 
 * Approach:
 * - Use backtracking to try all possible word segmentations
 * - For each position, try all words from dictionary that match the substring
 * - Build the sentence as we go, adding spaces between words
 * - When we reach the end of string, add the sentence to result
 * - Use a set for O(1) dictionary lookup
 * - Backtrack by removing the last word from current sentence
 * 
 * Time: O(2^n) in worst case - exponential due to backtracking
 * Space: O(2^n) for storing all possible sentences + O(n) recursion stack
 */

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// Solution2: Pick and not pick method with meaningful names and clarity
// -----------------------------------------------------------------------------
class Solution2 {
private:
    // Backtracking helper: explore all splits between start and end
    void backtrack(int start, int end, string& s, unordered_set<string>& dict,
                   vector<string>& path, vector<string>& sentences) {
        // Base case: reached the end of the string
        if (end == s.size()) {
            if (start == end) {
                // Join current words with spaces
                stringstream sentence;
                for (int i = 0; i < path.size(); ++i) {
                    if (i) sentence << " ";
                    sentence << path[i];
                }
                sentences.push_back(sentence.str());
            }
            return;
        }

        // Not pick: extend the substring
        backtrack(start, end + 1, s, dict, path, sentences);

        // Pick: take substring as a word if present in dictionary
        string word = s.substr(start, end - start + 1);
        if (dict.count(word)) {
            path.push_back(word);
            backtrack(end + 1, end + 1, s, dict, path, sentences);
            path.pop_back();
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<string> sentences, path;
        backtrack(0, 0, s, dict, path, sentences);
        return sentences;
    }
};

// -----------------------------------------------------------------------------
// Solution: Elegant, clean backtracking using split positions
// -----------------------------------------------------------------------------
class Solution {
private:
    void backtrack(int start, const string& s, const unordered_set<string>& wordSet,
                   vector<string>& path, vector<string>& result) {
        if (start == s.length()) {
            // Join path into a sentence
            stringstream sentence;
            for (int i = 0; i < path.size(); ++i) {
                if (i) sentence << " ";
                sentence << path[i];
            }
            result.push_back(sentence.str());
            return;
        }

        // Try all possible ends for a word starting at 'start'
        for (int end = start + 1; end <= s.length(); ++end) {
            string word = s.substr(start, end - start);
            if (wordSet.count(word)) {
                path.push_back(word);
                backtrack(end, s, wordSet, path, result);
                path.pop_back();
            }
        }
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<string> result, path;
        backtrack(0, s, wordSet, path, result);
        return result;
    }
};

