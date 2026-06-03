/*
GeeksforGeeks: Longest Palindrome in a String
Difficulty: Medium

Problem:
Given a string s, your task is to find the longest palindromic substring within s.
A palindrome is a string that reads the same forward and backward.
Note: If there are multiple palindromic substrings with the same length, return the first occurrence of the longest palindromic substring from left to right.

Examples:
Input: s = “forgeeksskeegfor” 
Output: “geeksskeeg”
Explanation: There are several possible palindromic substrings like “kssk”, “ss”, “eeksskee” etc. 
But the substring “geeksskeeg” is the longest among all.

Input: s = “Geeks” 
Output: “ee”
Explanation: "ee" is the longest palindromic substring of "Geeks". 

Input: s = “abc” 
Output: “a”
Explanation: "a", "b" and "c" are longest palindromic substrings of same length. 
So, the first occurrence is returned.

Core Idea:
A palindrome exactly mirrors around its center. A center can either be a single character (for odd-length palindromes like "aba") or directly between two characters (for even-length palindromes like "abba").
Therefore, there are exactly `2N - 1` possible centers in a string of length `N`.
We can simply iterate through all possible centers and expand outwards to the left and right simultaneously as long as the characters match.
During this expansion, we keep track of the maximum length found and its starting index.
By strictly updating our maximum ONLY when we find a *longer* palindrome (`> max_len`), we naturally satisfy the condition to keep the *first* occurrence (since our outer loop evaluates centers strictly from left-to-right).

Approach:
1. Initialize `start = 0` and `max_len = 1` (every single character is inherently a palindrome of length 1).
2. Loop through each character index `i` from `0` to `N-1`.
3. Check Odd-Length Palindromes:
   - Set left pointer `l = i`, right pointer `r = i`.
   - While `l >= 0`, `r < N`, and `s[l] == s[r]`:
     - If current length `(r - l + 1)` is greater than `max_len`:
       - Update `max_len` and `start = l`.
     - Expand outwards: `l--` and `r++`.
4. Check Even-Length Palindromes:
   - Set left pointer `l = i`, right pointer `r = i + 1`.
   - Expand similarly and update `max_len` and `start` if a strictly longer palindrome is found.
5. Return the substring using `s.substr(start, max_len)`.

Time Complexity: O(N^2), where N is the length of the string. Expanding around all 2N - 1 centers takes at most O(N) operations each. For N <= 1000, this is blazing fast.
Space Complexity: O(1) auxiliary space, as we are simply dragging two pointers across the string.

GFG Link: https://www.geeksforgeeks.org/problems/longest-palindrome-in-a-string3411/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        
        int start = 0;
        int max_len = 1;
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            // Check for odd-length palindromes (centered at character i)
            int l = i, r = i;
            while (l >= 0 && r < n && s[l] == s[r]) {
                // Strictly greater ensures we keep the first occurrence of the maximum length
                if (r - l + 1 > max_len) {
                    max_len = r - l + 1;
                    start = l;
                }
                l--;
                r++;
            }
            
            // Check for even-length palindromes (centered between character i and i+1)
            l = i;
            r = i + 1;
            while (l >= 0 && r < n && s[l] == s[r]) {
                if (r - l + 1 > max_len) {
                    max_len = r - l + 1;
                    start = l;
                }
                l--;
                r++;
            }
        }
        
        return s.substr(start, max_len);
    }
};

/*
Dry Run — Example 2:
Input: s = "Geeks"

Initialization: start = 0, max_len = 1.

i = 0 ('G'):
  Odd: l=0, r=0 ('G'=='G'). len = 1. Not > max_len(1). Expands out of bounds.
  Even: l=0, r=1 ('G'!='e'). Loop ends.

i = 1 ('e'):
  Odd: l=1, r=1 ('e'=='e'). len = 1. Expands to l=0, r=2 ('G'!='e'). Loop ends.
  Even: l=1, r=2 ('e'=='e'). len = 2. 2 > max_len(1), so max_len = 2, start = 1.
        Expands to l=0, r=3 ('G'!='k'). Loop ends.

i = 2 ('e'):
  Odd: l=2, r=2 ('e'=='e'). len = 1. Expands to l=1, r=3 ('e'!='k'). Loop ends.
  Even: l=2, r=3 ('e'!='k'). Loop ends.

i = 3 ('k'):
  Odd: l=3, r=3 ('k'=='k'). len = 1. Expands to l=2, r=4 ('e'!='s'). Loop ends.
  Even: l=3, r=4 ('k'!='s'). Loop ends.

i = 4 ('s'):
  Odd: l=4, r=4 ('s'=='s'). len = 1. Expands out of bounds.
  Even: l=4, r=5 (out of bounds).

End Loop.
Return s.substr(1, 2) which evaluates to "ee".

Output: "ee"
*/
