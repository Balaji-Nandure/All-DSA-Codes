/*
 * Problem: Word Break
 * 
 * LeetCode 139: Word Break
 * 
 * Given a string s and a dictionary of strings wordDict, return true if s 
 * can be segmented into a space-separated sequence of one or more 
 * dictionary words.
 * 
 * Note that the same word in the dictionary may be reused multiple times 
 * in the segmentation.
 * 
 * Example 1:
 * Input: s = "leetcode", wordDict = ["leet","code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 * 
 * Example 2:
 * Input: s = "applepenapple", wordDict = ["apple","pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as 
 * "apple pen apple". Note that you are allowed to reuse a dictionary word.
 * 
 * Example 3:
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: false
 * 
 * Constraints:
 * - 1 <= s.length <= 300
 * - 1 <= wordDict.length <= 1000
 * - 1 <= wordDict[i].length <= 20
 * - s and wordDict[i] consist of only lowercase English letters.
 * - All the strings of wordDict are unique.
 * 
 * Approach:
 * - Use pure backtracking to explore all partitionings of the string
 * - At each position, try every possible split and check if the substring exists in the dictionary
 * - If we can segment the entire string fully with dictionary words, return true
 * - There is no memoization in this approach
 * - Use a set for O(1) dictionary lookup
 * 
 * Time: O(2^n) (exponential - tries all possible splits)
 * Space: O(n) recursion stack
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Pure backtracking: try every possible split at each position
    bool canBreak(int start, const string& s, const unordered_set<string>& wordSet) {
        if (start == (int)s.length()) {
            return true;
        }
        for (int end = start + 1; end <= (int)s.length(); ++end) {
            string word = s.substr(start, end - start);
            if (wordSet.count(word)) {
                if (canBreak(end, s, wordSet)) {
                    return true;
                }
            }
        }
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return canBreak(0, s, wordSet);
    }
};
