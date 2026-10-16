// Problem: Smallest Window in a String Containing All Characters of Another String (Minimum Window Substring)
// Link (GFG): https://www.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/find-the-smallest-window-in-a-string-containing-all-characters-of-another-string/
// Difficulty: Hard
// Topic: String, Dynamic Sliding Window, Two Pointers, Frequency Multiset

/*
Problem Statement:
Given two strings s and p. Find the smallest window in the string s consisting of 
all the characters (including duplicates) of the string p.
If no such window exists, return "-1".
If multiple windows exist of the same minimum length, return the one with the smallest starting index.

Example 1:
Input: s = "timetopractice", p = "toc"
Output: "toprac"
Explanation: "toprac" (index 4 to 9) contains 't', 'o', 'c' and has length 6.

Example 2:
Input: s = "zoomlazapzo", p = "oza"
Output: "apzo"
Explanation: "apzo" contains 'o', 'z', 'a' and has length 4.

Constraints:
- 1 <= s.length(), p.length() <= 10^5
- Strings consist of lowercase/uppercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 33 (Smallest Distinct Window of String Itself):
//   * We only needed 1 copy of each distinct character.
// - In Problem 37 (Minimum Window Substring with Multiset Frequencies):
//   * String `p` may contain DUPLICATE characters (e.g. p = "AAB" requires AT LEAST two 'A's and one 'B').
//   * A single boolean or simple distinct count is insufficient.
//   * We maintain a demand frequency counter `requiredCount = p.length()`:
//     Every time an incoming character helps satisfy a deficit (`patFreq[ch] > 0`), 
//     `requiredCount` decrements. When `requiredCount == 0`, ALL multiset requirements are met!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Dynamic Sliding Window with Multiset Deficit Tracking (Optimal & Chosen):
//   - Array `patFreq[256]` initialized with frequencies of all characters in `p`.
//   - Variable `requiredCount = p.length()` (number of needed character slots).
//   - Two pointers `left = 0`, `right = 0`, `minLen = infinity`, `startIdx = -1`.
//   - As `right` advances:
//       * If `patFreq[s[right]] > 0`: A needed character joined -> `requiredCount--`.
//       * Decrement `patFreq[s[right]]--`. (Can go negative, representing surplus).
//       * While `requiredCount == 0`:
//           - Valid window `[left .. right]` identified!
//           - If `right - left + 1 < minLen`: update `minLen` and `startIdx = left`.
//           - Contract from left:
//               Increment `patFreq[s[left]]++`.
//               If `patFreq[s[left]] > 0`: A critical required character was removed -> `requiredCount++`.
//               `left++`.
//   - Complexity: O(N) linear time, O(256) = O(1) space.
//   - Why this approach: Operates in a single scan with zero memory reallocation.

#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string smallestWindow(string s, string p) {
        int n = s.length();
        int m = p.length();
        if (n < m) return "-1";

        // Frequency table for pattern p (stores demand count)
        int patFreq[256] = {0};
        for (char ch : p) {
            patFreq[(unsigned char)ch]++;
        }

        int requiredCount = m; // Total character matches needed
        int minLen = INT_MAX;
        int startIdx = -1;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If the incoming character currently has a positive demand in patFreq,
            // it contributes towards fulfilling the required multiset count of p!
            if (patFreq[(unsigned char)s[right]] > 0) {
                requiredCount--;
            }

            // Decrement demand (negative values signify surplus of this character in window)
            patFreq[(unsigned char)s[right]]--;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When requiredCount reaches 0, the current window [left .. right] contains
            // ALL characters of p with required multiplicities! We greedily shrink from left.
            while (requiredCount == 0) {
                int currentLen = right - left + 1;
                if (currentLen < minLen) {
                    minLen = currentLen;
                    startIdx = left;
                }

                // Evict s[left] from window
                patFreq[(unsigned char)s[left]]++;

                // If demand becomes positive, we have lost an essential character
                if (patFreq[(unsigned char)s[left]] > 0) {
                    requiredCount++; // Window is no longer fully valid, loop breaks
                }
                left++;
            }
        }

        if (startIdx == -1) return "-1";
        return s.substr(startIdx, minLen);
    }
};

int main() {
    Solution sol;
    string s1 = "timetopractice";
    string p1 = "toc";
    cout << "Smallest window in \"" << s1 << "\" for \"" << p1 << "\": " 
         << sol.smallestWindow(s1, p1) << "\n";

    string s2 = "zoomlazapzo";
    string p2 = "oza";
    cout << "Smallest window in \"" << s2 << "\" for \"" << p2 << "\": " 
         << sol.smallestWindow(s2, p2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N is length of string s.
  * The `right` pointer moves 0 to N-1 (N steps).
  * The `left` pointer moves at most N steps forward across the entire algorithm.
  * Total time is strictly O(N) linear.
- Space Complexity: O(256) = O(1) auxiliary space (fixed ASCII array).

Key Takeaways:
- Allowing demand to become negative elegantly encodes character surplus inside 
  the sliding window without secondary lookups or nested maps.
*/
