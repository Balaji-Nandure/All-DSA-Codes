/*
GeeksforGeeks: Longest Palindromic Substring
Difficulty: Medium

Problem:
Given a string s, return the longest palindromic substring in s. 
If there are multiple answers, return the one that appears first in the given string s.

Examples:
Input: s = "forgeeksskeegfor"
Output: geeksskeeg

Input: s = "abacac"
Output: aba

Input: s = "geeks"
Output: ee

Constraints:
1 <= s.length() <= 10^3

Approach: Expand Around Center
- Instead of using a 2D DP table (which takes O(N^2) memory), we can solve this problem in O(N^2) time and O(1) space.
- A palindrome is symmetric about its center. For a string of length N, there are 2*N - 1 possible centers:
  - N centers at each character position: index i (for odd-length palindromes, e.g., "aba" centered at 'b').
  - N-1 centers in the gaps between character positions: index i and i+1 (for even-length palindromes, e.g., "abba" centered between 'b' and 'b').
- For each center:
  - We expand outwards in both directions as long as the characters match and we are within boundaries.
  - We keep track of the maximum length palindrome found so far.
- To handle the "first appearance" tie-breaking rule:
  - We iterate through centers from left to right (i = 0 to N-1).
  - We only update our max palindrome range when we find a length strictly greater than our current maximum (`len > max_len`).
  - This ensures that if another palindrome of equal length is found later, it won't overwrite the one we found first.

Time Complexity: O(N^2) — There are 2*N - 1 centers, and expanding from each center takes O(N) in the worst case.
Space Complexity: O(1) auxiliary space (excluding the substring used to return the output).

GFG Link: https://www.geeksforgeeks.org/problems/longest-palindromic-substring5511/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to expand around a center and return the starting index and length of the palindrome
    pair<int, int> expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        // The palindrome is s[left+1 ... right-1]
        // Starting index: left + 1
        // Length: (right - 1) - (left + 1) + 1 = right - left - 1
        return {left + 1, right - left - 1};
    }

public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n == 0) return "";
        
        int start_idx = 0;
        int max_len = 1;
        
        for (int i = 0; i < n; i++) {
            // Case 1: Odd-length palindromes (centered at s[i])
            pair<int, int> odd_palindrome = expandAroundCenter(s, i, i);
            if (odd_palindrome.second > max_len) {
                max_len = odd_palindrome.second;
                start_idx = odd_palindrome.first;
            }
            
            // Case 2: Even-length palindromes (centered between s[i] and s[i+1])
            pair<int, int> even_palindrome = expandAroundCenter(s, i, i + 1);
            if (even_palindrome.second > max_len) {
                max_len = even_palindrome.second;
                start_idx = even_palindrome.first;
            }
        }
        
        return s.substr(start_idx, max_len);
    }
};

/*
Dry Run — Example:
s = "abacac"
n = 6
Initial: start_idx = 0, max_len = 1

- i = 0:
  - expand(0, 0) -> "a" (starts at 0, len 1). Since 1 > 1 is false, no change.
  - expand(0, 1) -> mismatch -> len 0.
- i = 1:
  - expand(1, 1) -> expands to s[0] == s[2] ('a' == 'a') -> "aba" (starts at 0, len 3). 
    Since 3 > 1 is true: max_len = 3, start_idx = 0.
  - expand(1, 2) -> mismatch.
- i = 2:
  - expand(2, 2) -> "a" (starts at 2, len 1). No change.
  - expand(2, 3) -> mismatch.
- i = 3:
  - expand(3, 3) -> expands to s[2] == s[4] ('a' == 'a') -> "aca" (starts at 2, len 3). 
    Since 3 > 3 is false, no change (preserves first occurrence "aba").
  - expand(3, 4) -> mismatch.
- i = 4:
  - expand(4, 4) -> expands to s[3] == s[5] ('c' == 'c') -> "cac" (starts at 3, len 3). 
    Since 3 > 3 is false, no change.
  - expand(4, 5) -> mismatch.
- i = 5:
  - expand(5, 5) -> "c" (starts at 5, len 1). No change.

Returns s.substr(0, 3) -> "aba".
Output: "aba"
*/
