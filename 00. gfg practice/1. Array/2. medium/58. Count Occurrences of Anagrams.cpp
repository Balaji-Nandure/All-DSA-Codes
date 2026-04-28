/*
PROBLEM: Count Occurrences of Anagrams
------------------------------------------------
Given:
- txt (text string)
- pat (pattern string)

Return:
- Count of substrings in txt which are anagrams of pat

Example:
txt = "forxxorfxdofr", pat = "for"
Output = 3
Explanation: "for", "orf", "ofr" are the anagrams

------------------------------------------------
INTUITION / APPROACH:
------------------------------------------------
Pattern: Sliding Window + Frequency Count

Key Idea:
- Anagrams have same frequency of characters
- Maintain frequency arrays for pattern and current window
- Use sliding window of size = pat.length()

Steps:
1. Store frequency of pattern characters
2. Initialize sliding window over txt
3. For each window:
   - Add new character to frequency
   - Remove character that slides out
   - Compare frequency arrays
   - If equal ? anagram found, increment count

Optimization:
- Instead of comparing full arrays (O(26)), use a match counter
- Track how many character frequencies match exactly

------------------------------------------------
TIME COMPLEXITY:
O(n) where n = length of txt

SPACE COMPLEXITY:
O(1) - constant space for 26 character frequencies

------------------------------------------------
GFG LINK:
https://www.geeksforgeeks.org/problems/count-occurences-of-anagrams5839/1

LeetCode (similar):
https://leetcode.com/problems/find-all-anagrams-in-a-string/

------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(string &pat, string &txt) {
        
        int k = pat.size();
        int n = txt.size();
        
        if(k > n) return 0;
        
        // Frequency arrays for pattern and current window
        vector<int> freq_pat(26, 0), freq_win(26, 0);
        
        // Fill pattern frequency
        for(char c : pat) {
            freq_pat[c - 'a']++;
        }
        
        // Initialize first window
        for(int i = 0; i < k; i++) {
            freq_win[txt[i] - 'a']++;
        }
        
        int count = 0;
        
        // Check first window
        if(freq_win == freq_pat) {
            count++;
        }
        
        // Slide remaining windows
        for(int i = k; i < n; i++) {
            // Add new character
            freq_win[txt[i] - 'a']++;
            
            // Remove old character
            freq_win[txt[i - k] - 'a']--;
            
            // Check if current window is anagram
            if(freq_win == freq_pat) {
                count++;
            }
        }
        
        return count;
    }
};

/*
ALTERNATIVE OPTIMIZED APPROACH:
--------------------------------
Instead of comparing arrays, maintain a count of matched frequencies:

int matches = 0;
for(int i = 0; i < 26; i++) {
    if(freq_pat[i] == freq_win[i]) matches++;
}

Then in sliding window:
- Update matches when adding/removing characters
- If matches == 26 ? all frequencies match

This reduces comparison from O(26) to O(1) per operation.

------------------------------------------------
TEST CASES:
--------------------------------
1. txt = "forxxorfxdofr", pat = "for" ? 3
2. txt = "aabaabaa", pat = "aaba" ? 4
3. txt = "aaaaa", pat = "aa" ? 4
4. txt = "abc", pat = "def" ? 0
5. txt = "abab", pat = "ab" ? 3

------------------------------------------------
*/
