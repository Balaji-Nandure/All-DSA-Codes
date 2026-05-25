/*
GeeksforGeeks: Pattern Searching
Difficulty: Easy

Given a text and a pattern, the task is to check if the pattern exists in the text or not.

Example 1:
Input: text = "geeksforgeeks"
       pat = "geek"
Output: 1
Explanation: "geek" exists in "geeksforgeeks"

Example 2:
Input: text = "geeksforgeeks"
       pat = "gfg"
Output: 0
Explanation: "gfg" does not exists in "geeksforgeeks"

Constraints:
1 <= |text|, |pat| <= 10^5
Both of the string contains lower case English alphabets
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to compute the LPS (Longest Prefix Suffix) array for KMP algorithm
    vector<int> computeLPS(const string &pat) {
        int m = pat.length();
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;
        
        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

public:
    /*
     * Problem: Pattern Searching
     * 
     * Determine if pat exists in text or not.
     * 
     * Time Complexity: O(N + M) where N = |text|, M = |pat| (using KMP algorithm)
     * Space Complexity: O(M) auxiliary space for LPS array
     */
    int search(string text, string pat) {
        int n = text.length();
        int m = pat.length();
        
        if (m == 0) return 1;
        if (n < m) return 0;
        
        vector<int> lps = computeLPS(pat);
        int i = 0; // index for text
        int j = 0; // index for pat
        
        while (i < n) {
            if (pat[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                return 1; // Pattern found
            } else if (i < n && pat[j] != text[i]) {
                if (j != 0) {
                    // Mismatch after j matches, look up next comparison position in lps
                    j = lps[j - 1];
                } else {
                    // Mismatch at start of pattern, advance in text
                    i++;
                }
            }
        }
        
        return 0; // Pattern not found
    }
};

/*
Approach: Knuth-Morris-Pratt (KMP) Pattern Matching
- A naive pattern matching algorithm takes O(N * M) time in the worst case (e.g. text = "aaaaa", pat = "aab").
- To achieve O(N + M) time complexity, we use the KMP algorithm.
- KMP preprocessing phase:
  - We construct an LPS (Longest Prefix Suffix) array for the pattern.
  - `lps[i]` stores the length of the longest proper prefix of `pat[0..i]` that is also a suffix of `pat[0..i]`.
- KMP search phase:
  - We traverse the `text` and `pattern` with indices `i` and `j` respectively.
  - When characters match, we advance both indices.
  - When we find a match of the full pattern (`j == m`), we return 1.
  - On a character mismatch at `pat[j] != text[i]`:
    - If `j > 0`, we shift the pattern right using `lps[j-1]` to skip unnecessary character comparisons.
    - If `j == 0`, we simply increment `i` to look for a start match at the next character of `text`.
- If the loop completes without returning 1, the pattern is not present, so we return 0.

Complexity:
- Time Complexity: O(N + M) where N = |text| and M = |pat|.
- Space Complexity: O(M) auxiliary space for the LPS array.
*/
