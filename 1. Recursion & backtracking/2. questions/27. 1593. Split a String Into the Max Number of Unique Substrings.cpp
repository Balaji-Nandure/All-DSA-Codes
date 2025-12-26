/*
 * Problem: Split a String Into the Max Number of Unique Substrings
 * 
 * LeetCode 1593: Split a String Into the Max Number of Unique Substrings
 * 
 * Given a string s, return the maximum number of unique substrings that the 
 * string can be split into.
 * 
 * You can split string s into any list of non-empty substrings, where the 
 * concatenation of the substrings forms the original string. However, you must 
 * split the string such that after splitting, each substring is unique.
 * 
 * Note: s contains only lowercase English letters.
 * 
 * Example 1:
 * Input: s = "ababccc"
 * Output: 5
 * Explanation: One way to split is ["a","b","ab","c","cc"]. 
 * Splitting like ["a","b","a","b","c","cc"] is not valid because "a" and "b" 
 * appear twice.
 * 
 * Example 2:
 * Input: s = "aba"
 * Output: 2
 * Explanation: One way to split is ["a","ba"].
 * 
 * Example 3:
 * Input: s = "aa"
 * Output: 1
 * Explanation: It is impossible to split the string any further.
 * 
 * Constraints:
 * - 1 <= s.length <= 16
 * - s contains only lowercase English letters.
 * 
 * Approach:
 * - Use backtracking to try all possible ways to split the string
 * - At each position, try all possible substring lengths
 * - Use a set to track unique substrings seen so far
 * - If a substring is already seen, skip it (backtrack)
 * - When we reach the end of string, update the maximum count
 * - Return the maximum number of unique substrings
 * 
 * Time: O(2^n) - exponential due to backtracking, trying all splits
 * Space: O(n) - recursion stack + set to store unique substrings
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Backtracking helper: try all possible splits starting from 'start'
    void backtrack(int start, const string& s, unordered_set<string>& seen, int& maxCount) {
        // Base case: reached the end of string
        if (start == s.length()) {
            maxCount = max(maxCount, (int)seen.size());
            return;
        }

        // Try all possible substring lengths starting from 'start'
        for (int end = start + 1; end <= s.length(); ++end) {
            string substring = s.substr(start, end - start);
            
            // Only proceed if this substring hasn't been seen before
            if (seen.find(substring) == seen.end()) {
                // Pick: add substring to set and recurse
                seen.insert(substring);
                backtrack(end, s, seen, maxCount);
                // Backtrack: remove substring from set
                seen.erase(substring);
            }
        }
    }

public:
    int maxUniqueSplit(string s) {
        unordered_set<string> seen;
        int maxCount = 0;
        backtrack(0, s, seen, maxCount);
        return maxCount;
    }
};
