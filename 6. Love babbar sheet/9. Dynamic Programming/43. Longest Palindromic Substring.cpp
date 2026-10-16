#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Problem: Longest Palindromic Substring (LPSubstring)
 * 
 * Given a string S, find the longest palindromic substring in S.
 * A substring must be strictly CONTIGUOUS. Return the actual substring.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "41. Longest Palindromic Subsequence", characters could be non-contiguous.
 * - Here, characters MUST be contiguous.
 * - While 2D DP takes O(N^2) space, the Expand Around Center algorithm achieves 
 *   O(1) auxiliary space and cache-friendly performance!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Expand Around Center in O(N^2) Time and O(1) Space:
 *   A palindrome is mirrored around its center.
 *   There are 2N - 1 possible centers in a string of length N:
 *   - N odd-length centers: single character at index i.
 *   - N - 1 even-length centers: between character i and i + 1.
 *   
 *   Algorithm:
 *     Helper expand(left, right):
 *       While left >= 0 and right < N and S[left] == S[right]:
 *         left--, right++
 *       Returns length (right - left - 1).
 *     
 *     For each center i from 0 to N - 1:
 *       len1 = expand(i, i)       (odd length palindrome)
 *       len2 = expand(i, i + 1)   (even length palindrome)
 *       cur_len = max(len1, len2)
 *       If cur_len > max_len:
 *         Update best starting index: start = i - (cur_len - 1) / 2
 *         max_len = cur_len
 *     
 *     Return S.substr(start, max_len).
 */

class Solution {
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < (int)s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Length of palindrome found
        return right - left - 1;
    }

public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) return s;

        int start = 0;
        int max_len = 1;

        for (int i = 0; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check both odd-length (center at i) and even-length (center between i and i+1) palindromes
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            int len = max(len1, len2);

            if (len > max_len) {
                max_len = len;
                // *** CRUCIAL LINE: Calculate starting index from center i and length len ***
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, max_len);
    }
};

int main() {
    Solution sol;
    string s1 = "babad";
    cout << "Longest Palindromic Substring of \"" << s1 << "\": \"" << sol.longestPalindrome(s1) << "\"\n";
    // Expected: "bab" or "aba"

    string s2 = "cbbd";
    cout << "Longest Palindromic Substring of \"" << s2 << "\": \"" << sol.longestPalindrome(s2) << "\"\n";
    // Expected: "bb"

    string s3 = "forgeeksskeegfor";
    cout << "Longest Palindromic Substring of \"" << s3 << "\": \"" << sol.longestPalindrome(s3) << "\"\n";
    // Expected: "geeksskeeg"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2). There are 2N - 1 centers, and expanding from each center takes at most O(N).
 * - Space Complexity: O(1) auxiliary space (no extra matrices or string copies).
 */
