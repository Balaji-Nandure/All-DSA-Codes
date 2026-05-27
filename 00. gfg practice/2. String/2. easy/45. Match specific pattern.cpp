/*
Problem: Match specific pattern

Given a dictionary of words and a pattern. Every character in the pattern is uniquely mapped to a character in the dictionary. Find all such words in the dictionary that match the given pattern. 

Examples :

Input: n = 4, dict[] = {abb,abc,xyz,xyy}, pattern  = foo
Output: abb xyy
Explanation: xyy and abb have the same character at index 1 and 2 like the pattern.

Constraints:
1 <= N <= 10^4
1 <= |word|, |pattern| <= 100

--------------------------------------------------

Pattern:
String Processing + Hashing (Isomorphic Strings)

--------------------------------------------------

Key Observation:
- This is a direct application of the "Isomorphic Strings" concept.
- A word from the dictionary matches the pattern if:
  1. It has the same length as the pattern.
  2. Each character in the pattern maps uniquely to a character in the word, and vice versa (bijection).
- We can use two hash maps (or arrays of size 256 for ASCII characters) to keep track of the character mappings from the word to the pattern and from the pattern to the word.

--------------------------------------------------

Approach:
1. Create a helper function `isMatch(string word, string pattern)`:
   - If the lengths of `word` and `pattern` are different, return `false`.
   - Initialize two arrays `mapWordToPattern` and `mapPatternToWord` of size 256 with 0s.
   - Iterate through each character `w` in `word` and `p` in `pattern`:
     - If neither `w` nor `p` has been mapped yet (value is 0), map them to each other.
     - If they have been mapped, check if `w` maps to `p` and `p` maps to `w`. If not, return `false`.
   - If the loop finishes without mismatches, return `true`.
2. Iterate through each string in the given `dict`.
3. If `isMatch` returns `true`, add the string to the answer list.
4. Return the answer list.

--------------------------------------------------

Time Complexity: O(N * K) where N is the number of words in the dictionary and K is the length of the pattern.
Space Complexity: O(N) to store the result vector, and O(1) auxiliary space for the constant size hash arrays (256).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/match-specific-pattern/1
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool isMatch(const string& word, const string& pattern) {
        if (word.length() != pattern.length()) {
            return false;
        }
        
        vector<int> m1(256, 0);
        vector<int> m2(256, 0);
        
        for (int i = 0; i < word.length(); i++) {
            char w = word[i];
            char p = pattern[i];
            
            // If neither character has been mapped yet
            if (m1[w] == 0 && m2[p] == 0) {
                m1[w] = p;
                m2[p] = w;
            } 
            // If they are mapped, check if the mapping is correct
            else if (m1[w] != p || m2[p] != w) {
                return false;
            }
        }
        
        return true;
    }

public:
    /*The structure of the function may slightly vary on GFG.
      Sometimes it passes `int n` as the first argument.
      If it does, just update the function signature accordingly.*/
    vector<string> findMatchedWords(vector<string> dict, string pattern) {
        vector<string> ans;
        for (const string& word : dict) {
            if (isMatch(word, pattern)) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};
