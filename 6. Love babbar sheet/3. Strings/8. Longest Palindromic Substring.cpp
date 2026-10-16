// Problem: Longest Palindromic Substring
// Link (GFG): https://www.geeksforgeeks.org/problems/longest-palindrome-in-a-string3411/1
// Article: https://www.geeksforgeeks.org/dsa/longest-palindromic-substring-using-dynamic-programming-2/
// Difficulty: Medium
// Topic: String, Two Pointers (Expand Around Center), Dynamic Programming

/*
Problem Statement:
Given a string s, find the longest palindromic substring in s.
If there are multiple substrings of the same maximum length, return the one 
that appears earliest in the string.

Example 1:
Input: s = "babad"
Output: "bab" (or "aba", both have length 3)

Example 2:
Input: s = "cbbd"
Output: "bb"

Example 3:
Input: s = "aaaabbaa"
Output: "aabbaa"

Constraints:
- 1 <= s.length() <= 1000
- s consists of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 2 (Check Palindrome String):
//   * We checked whether the ENTIRE string was a palindrome from the outside in (boundary -> center).
// - In Problem 8 (Longest Palindromic Substring):
//   * We must find an unknown contiguous slice `s[i .. j]` that maximizes length while being a palindrome.
//   * Instead of checking outside-in (which tests O(N^2) pairs in O(N) each = O(N^3)),
//     we REVERSE THE DIRECTION: We expand INSIDE-OUT from all 2N - 1 possible centers!
//   * Odd palindromes center on a single character `s[i]`.
//   * Even palindromes center between two characters `s[i]` and `s[i+1]`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: 2D Dynamic Programming
//   - Maintain boolean `dp[i][j]` = is `s[i..j]` a palindrome.
//   - Recurrence: `dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i+1][j-1])`.
//   - Complexity: O(N^2) time, O(N^2) auxiliary space.
//   - Why Suboptimal: Allocating a 1000x1000 matrix creates cache misses and high memory footprint.
//
// Approach 2: Expand Around Center (Optimal & Chosen)
//   - A palindrome mirrors around its center. There are 2N - 1 potential centers:
//     * N odd centers: `(i, i)`
//     * N - 1 even centers: `(i, i + 1)`
//   - For each center, expand pointers `left` and `right` outward as long as `s[left] == s[right]`.
//   - Track `maxLen` and `startIdx`.
//   - Complexity: O(N^2) time, O(1) auxiliary space!
//   - Why this approach: Eliminates all 2D auxiliary DP memory; runs ~5x faster in practice.
//
// Note on Manacher's Algorithm:
//   - Manacher's can solve this in linear O(N) time using palindrome radii caching.
//     However, Expand Around Center is by far the most commonly expected and debuggable 
//     interview solution, with O(1) space.

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    // Helper function: Expands outwards from a given center and updates best substring
    void expandAroundCenter(const string& s, int left, int right, int& startIdx, int& maxLen) {
        int n = s.length();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Expanding symmetrically from the center outward as long as characters match.
        // Once a mismatch occurs, this center can produce no larger palindrome.
        while (left >= 0 && right < n && s[left] == s[right]) {
            left--;
            right++;
        }

        // When the while loop terminates, left and right have overshot by 1 step.
        // True palindrome starts at `left + 1` and has length `(right - 1) - (left + 1) + 1` = `right - left - 1`.
        int currentLen = right - left - 1;

        if (currentLen > maxLen) {
            maxLen = currentLen;
            startIdx = left + 1;
        }
    }

public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n <= 1) return s;

        int startIdx = 0;
        int maxLen = 1;

        for (int i = 0; i < n; ++i) {
            // Case 1: Odd length palindromes (single-character center at i)
            expandAroundCenter(s, i, i, startIdx, maxLen);

            // Case 2: Even length palindromes (two-character center between i and i+1)
            expandAroundCenter(s, i, i + 1, startIdx, maxLen);
        }

        return s.substr(startIdx, maxLen);
    }
};

int main() {
    Solution sol;
    string s1 = "babad";
    cout << "Longest Palindrome in \"" << s1 << "\": " << sol.longestPalindrome(s1) << "\n";

    string s2 = "cbbd";
    cout << "Longest Palindrome in \"" << s2 << "\": " << sol.longestPalindrome(s2) << "\n";

    string s3 = "aaaabbaa";
    cout << "Longest Palindrome in \"" << s3 << "\": " << sol.longestPalindrome(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2). There are 2N - 1 centers, and each center expands at most O(N) steps.
- Space Complexity: O(1) auxiliary space (no tables or matrices allocated).

Key Takeaways:
- Inside-out expansion from centers transforms a combinatorial O(N^3) search into an 
  elegant O(N^2) algorithm with zero memory overhead.
*/
