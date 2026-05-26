/*
GeeksforGeeks: Minimum indexed character
Difficulty: Easy

Given a string s1 and another string s2. Find the minimum index of the character in s1 that is also present in s2. If no character is common in both, then return -1.

Examples:

Input: s1 = "geeksforgeeks", s2 = "set"
Output: 1
Explanation: 'e' is the character which is present in given s1 "geeksforgeeks" and is also present in s2 "set". Minimum index of e is 1. 

Input: s1 = "adcffaet", s2 = "onkl"
Output: -1
Explanation: There are none of the characters which are common in s1 and s2.

Constraints:
1 <= s1.size(), s2.size() <= 10^5 
'a' <= s1_i, s2_i <= 'z'
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * Problem: Minimum indexed character
     * 
     * Find the minimum index of the character in s1 that is also present in s2.
     * 
     * Time Complexity: O(|s1| + |s2|) - single pass through both strings
     * Space Complexity: O(1) - auxiliary space for frequency/lookup array (size 26)
     */
    int minIndexChar(string &s1, string &s2) {
        vector<bool> present(26, false);
        
        // Mark all characters present in s2
        for (char c : s2) {
            present[c - 'a'] = true;
        }
        
        // Find the first character in s1 that is marked as present
        for (int i = 0; i < s1.length(); i++) {
            if (present[s1[i] - 'a']) {
                return i;
            }
        }
        
        return -1;
    }
};

/*
Approach: Boolean Lookup Array (Hash Set)
- We want to find the first character in `s1` (from left to right) that is present in `s2`.
- To do this efficiently:
  1. We construct a boolean array `present` of size 26 (since the inputs only contain lowercase English alphabets `'a'` to `'z'`).
  2. We iterate through `s2` and mark `present[c - 'a'] = true` for each character `c` in `s2`.
  3. We then iterate through `s1` from index `0` to `s1.length() - 1`. The first index `i` where `present[s1[i] - 'a']` is true is our answer, as it represents the minimum index in `s1` of a common character.
  4. If the loop completes without finding any matching character, we return `-1`.

Complexity:
- Time Complexity: O(|s1| + |s2|). We traverse `s2` once to build the lookup array, and then traverse `s1` once in the worst case to find the minimum index.
- Space Complexity: O(1) auxiliary space, as the lookup array requires a constant size of 26 booleans.
*/
