// Problem: Minimum Characters to be Added at Front to Make String Palindrome
// Link (GFG): https://www.geeksforgeeks.org/problems/form-a-palindrome1455/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-characters-added-front-make-string-palindrome/
// Difficulty: Hard
// Topic: String, KMP Algorithm, LPS Array, Palindromic Prefix

/*
Problem Statement:
Given a string s. Find the minimum number of characters that must be added 
AT THE FRONT of the string to make the entire string a palindrome.

Example 1:
Input: s = "ABC"
Output: 2
Explanation: Add 'C' and 'B' at front -> "CBABC", which is a palindrome of length 5.

Example 2:
Input: s = "AACECAAAA"
Output: 2
Explanation: Add 'A' and 'A' at front -> "AAACECAAAA".

Example 3:
Input: s = "ABCD"
Output: 3
Explanation: Add 'D', 'C', 'B' at front -> "DCBA ABCD".

Constraints:
- 1 <= s.length() <= 10^5
- s contains lowercase/uppercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Longest Palindromic Substring):
//   * The palindrome could appear anywhere inside the string.
// - In Problem 35 (Min Additions at Front for Palindrome):
//   * Characters can ONLY be added at the FRONT (index 0).
//   * This means any palindromic base MUST START AT INDEX 0 (it must be a Palindromic Prefix!).
//   * The characters that need to be added are simply the characters of `s` that are NOT part 
//     of the LONGEST PALINDROMIC PREFIX of `s`.
//   * Formula: `Min characters to add = s.length() - (Length of Longest Palindromic Prefix)`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Check Palindromes with Two Pointers from s.length() down to 1
//   - Complexity: O(N^2) time. TLE for N = 10^5.
//
// Approach 2: Modified KMP LPS Array (Optimal & Chosen)
//   - Concatenate: `combined = s + "$" + reverse(s)`.
//     (The delimiter '$' is critical so prefix and suffix matches don't cross into each other).
//   - Compute the KMP LPS array for `combined`.
//   - What does `lps.back()` represent?
//     * It is the longest prefix of `combined` (which starts in `s`) that is also 
//       a suffix of `combined` (which ends in `reverse(s)`).
//     * A prefix of `s` that equals a suffix of `reverse(s)` is, by definition, 
//       a PALINDROMIC PREFIX of `s`!
//     * Therefore, `lps.back()` is the length of the LONGEST palindromic prefix of `s`!
//   - Final Answer = `s.length() - lps.back()`.
//   - Complexity: Strict linear O(N) time, O(N) auxiliary space.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Standard KMP LPS builder
    vector<int> computeLPS(const string& s) {
        int n = s.length();
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;

        while (i < n) {
            if (s[i] == s[len]) {
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
    int minChar(string s) {
        int originalLen = s.length();

        // Create reversed string
        string rev = s;
        reverse(rev.begin(), rev.end());

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Concatenation with a sentinel delimiter '#':
        // The LPS of (s + "#" + rev(s)) finds the longest prefix of s that matches a suffix of rev(s),
        // which mathematically identifies the Longest Palindromic Prefix of s in linear time!
        string combined = s + "#" + rev;

        vector<int> lps = computeLPS(combined);

        int longestPalindromicPrefix = lps.back();

        // The remaining suffix of length (originalLen - longestPalindromicPrefix) must be mirrored to the front
        return originalLen - longestPalindromicPrefix;
    }
};

int main() {
    Solution sol;
    string s1 = "ABC";
    cout << "Min chars to add at front of \"" << s1 << "\": " << sol.minChar(s1) << "\n";

    string s2 = "AACECAAAA";
    cout << "Min chars to add at front of \"" << s2 << "\": " << sol.minChar(s2) << "\n";

    string s3 = "ABCD";
    cout << "Min chars to add at front of \"" << s3 << "\": " << sol.minChar(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N = s.length().
  * Reversing string: O(N).
  * Building LPS array of length 2N + 1: O(2N + 1) = O(N).
  * Strictly linear time, avoiding any quadratic substring comparisons.
- Space Complexity: O(N) auxiliary space for the combined string and LPS array.

Key Takeaways:
- Using `s + "#" + rev(s)` with KMP's LPS array is one of the most clever reductions 
  in string algorithms to find the longest palindromic prefix in O(N).
*/
