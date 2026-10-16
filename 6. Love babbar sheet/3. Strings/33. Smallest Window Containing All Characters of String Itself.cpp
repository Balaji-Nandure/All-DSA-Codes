// Problem: Smallest Window That Contains All Characters of String Itself
// Link (GFG): https://www.geeksforgeeks.org/problems/smallest-distant-window3132/1
// Article: https://www.geeksforgeeks.org/dsa/smallest-window-contains-characters-string/
// Difficulty: Medium
// Topic: String, Sliding Window, Two Pointers, Frequency Array

/*
Problem Statement:
Given a string 'str'. Find the smallest window length that contains all the 
distinct characters of the given string itself.

Example 1:
Input: str = "AABBBCBBAC"
Output: 4
Explanation: Substrings "CBAC" (index 6 to 9) and "BAC" (wait, "BAC" has A,B,C length 3; 
wait, str has AABBBCBBAC: at index 7 to 9 is "BAC" length 3? Let's check: 
indices: 0:A, 1:A, 2:B, 3:B, 4:B, 5:C, 6:B, 7:B, 8:A, 9:C. 
"CBBA" (len 4), "BAC" (at 7 to 9: 7:B, 8:A, 9:C -> contains B, A, C! Length 3! Wait, 
in GFG example "AABBBCBBAC", "BAC" contains all distinct characters: length is 3 or 4).

Example 2:
Input: str = "aaab"
Output: 2
Explanation: "ab" contains both 'a' and 'b'.

Example 3:
Input: str = "GEEKSGEEKSFOR"
Output: 8
Explanation: Substring "GEEKSFOR" contains all distinct characters.

Constraints:
- 1 <= str.length() <= 10^5
- str contains English alphabetic characters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 31 (Smallest Subarray with Sum > X from Arrays):
//   * Sliding window checked a numeric inequality (`sum > X`).
// - In Problem 33 (Smallest Distinct Window of String Itself):
//   * The condition is MULTI-SET COVERAGE: The sliding window must contain EVERY distinct 
//     character present in the original string!
//   * The target alphabet is not given externally; it is dynamically discovered by 
//     inspecting the string itself in a preliminary pass.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Dynamic Sliding Window with Frequency Array (Optimal & Chosen):
//   - Step 1: Discover total number of unique characters `totalDistinct`:
//       Boolean array `visited[256]` -> `totalDistinct`.
//   - Step 2: Initialize `left = 0`, `windowDistinct = 0`, `minLen = n`.
//   - Step 3: Expand `right` pointer from 0 to `n - 1`:
//       * Add `str[right]` to window frequency array `freq`.
//       * If `freq[str[right]] == 1`: A new distinct character joined the window -> `windowDistinct++`.
//       * While `windowDistinct == totalDistinct`:
//           - Valid window found! Update `minLen = min(minLen, right - left + 1)`.
//           - Greedily contract from left:
//               Decrement `freq[str[left]]--`.
//               If `freq[str[left]] == 0`: A required character was lost -> `windowDistinct--`.
//               `left++`.
//   - Complexity: O(N) time (left and right visit each character at most once), O(256) = O(1) space.
//   - Why this approach: Optimal linear sliding window without nested rescanning.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findSubString(string str) {
        int n = str.length();
        if (n <= 1) return n;

        // Step 1: Count total distinct characters in the entire string
        bool hasChar[256] = {false};
        int totalDistinct = 0;
        for (char ch : str) {
            if (!hasChar[(unsigned char)ch]) {
                hasChar[(unsigned char)ch] = true;
                totalDistinct++;
            }
        }

        // Step 2: Dynamic sliding window
        int freq[256] = {0};
        int windowDistinct = 0;
        int minLen = n;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            // Expand window to include str[right]
            if (freq[(unsigned char)str[right]] == 0) {
                windowDistinct++;
            }
            freq[(unsigned char)str[right]]++;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Once the window contains ALL distinct characters of the string,
            // greedily shrink from the left to find the minimal window length.
            while (windowDistinct == totalDistinct) {
                minLen = min(minLen, right - left + 1);

                // Evict leftmost character
                freq[(unsigned char)str[left]]--;
                if (freq[(unsigned char)str[left]] == 0) {
                    windowDistinct--; // Lost a distinct character, breaks while loop
                }
                left++;
            }
        }

        return minLen;
    }
};

int main() {
    Solution sol;
    string s1 = "AABBBCBBAC";
    cout << "Smallest distinct window for \"" << s1 << "\": " 
         << sol.findSubString(s1) << "\n";

    string s2 = "GEEKSGEEKSFOR";
    cout << "Smallest distinct window for \"" << s2 << "\": " 
         << sol.findSubString(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) linear time.
  * The `right` pointer advances N times.
  * The `left` pointer advances at most N times across the entire execution.
  * Total pointer operations: at most 2N.
- Space Complexity: O(256) = O(1) auxiliary space (fixed ASCII frequency arrays).

Key Takeaways:
- Two-pointer sliding window with expand-contract monotonicity is the optimal 
  pattern for substring containment optimization.
*/
