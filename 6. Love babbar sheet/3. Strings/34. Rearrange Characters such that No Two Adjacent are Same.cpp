// Problem: Rearrange Characters in a String such that No Two Adjacent are Same
// Link (GFG): https://www.geeksforgeeks.org/problems/rearrange-characters4649/1
// Article: https://www.geeksforgeeks.org/dsa/rearrange-characters-string-no-two-adjacent/
// Difficulty: Medium / Hard
// Topic: String, Greedy, Max-Heap, Pigeonhole Principle, Slot Filling

/*
Problem Statement:
Given a string s with repeated characters, rearrange the characters of s so that 
no two adjacent characters are identical.
If it is impossible to satisfy this condition, return "" (or "0" depending on platform).

Example 1:
Input: s = "aaabc"
Output: "abaca" (or "acaba")
Explanation: No two adjacent characters are identical.

Example 2:
Input: s = "aaabb"
Output: "ababa"

Example 3:
Input: s = "aa"
Output: "-1" (or "")
Explanation: Character 'a' appears 2 times in string of length 2. 
By Pigeonhole Principle, they must be adjacent.

Constraints:
- 1 <= s.length() <= 10^5
- s consists of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 20 (Rearrange Array Alternately):
//   * Array elements were rearranged based on their positive/negative sign.
// - In Problem 34 (No Two Adjacent Same):
//   * The constraint is ADJACENCY CONFLICT.
//   * Pigeonhole Invariant: If ANY character has frequency `f > (N + 1) / 2`, 
//     it is mathematically IMPOSSIBLE to avoid adjacent duplicates!
//   * To construct the string, we must greedily interleave the most frequent characters first!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Max-Heap (Priority Queue)
//   - Push `{freq, char}` into max-heap.
//   - Pop top 2 characters, append both, decrement counts, push back if count > 0.
//   - Complexity: O(N log 26) = O(N) time, O(26) space.
//
// Approach 2: Greedy Even-Odd Index Slot Filling (Optimal & Chosen)
//   - Step 1: Count frequency of all 26 characters. Find max frequency character `maxChar` with count `maxFreq`.
//   - Step 2: Feasibility Guard: `if (maxFreq > (n + 1) / 2) return "";`
//   - Step 3: Fill `maxChar` at EVEN indices: `0, 2, 4, ...`
//   - Step 4: Fill all remaining characters at the remaining even indices, and once even indices 
//     are exhausted, fill odd indices `1, 3, 5, ...`!
//   - Why this works: Because `maxFreq <= (n + 1) / 2`, placing `maxChar` at even indices 
//     guarantees that none of them touch each other. All other characters have smaller frequencies, 
//     so they cannot wrap around and touch themselves either!
//   - Complexity: Strict O(N) single pass, O(26) = O(1) space, ZERO heap overhead!

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string rearrangeString(string s) {
        int n = s.length();
        if (n <= 1) return s;

        // Count frequencies of all lowercase characters
        int freq[26] = {0};
        int maxFreq = 0;
        char maxChar = 'a';

        for (char ch : s) {
            freq[ch - 'a']++;
            if (freq[ch - 'a'] > maxFreq) {
                maxFreq = freq[ch - 'a'];
                maxChar = ch;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Pigeonhole Principle Feasibility Check:
        // If the most frequent character appears more than ceil(N / 2) times,
        // it is impossible to separate them without two becoming adjacent.
        if (maxFreq > (n + 1) / 2) {
            return "-1"; // Impossible
        }

        string result(n, ' ');
        int idx = 0;

        // Step 1: Fill the most frequent character at even indices (0, 2, 4, ...)
        while (freq[maxChar - 'a'] > 0) {
            result[idx] = maxChar;
            idx += 2;
            freq[maxChar - 'a']--;
        }

        // Step 2: Fill remaining characters
        for (int i = 0; i < 26; ++i) {
            while (freq[i] > 0) {
                // If even indices are filled, switch to odd indices (1, 3, 5, ...)
                if (idx >= n) {
                    idx = 1;
                }
                result[idx] = (char)('a' + i);
                idx += 2;
                freq[i]--;
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    string s1 = "aaabc";
    cout << "Rearranged \"" << s1 << "\": " << sol.rearrangeString(s1) << "\n";

    string s2 = "aaabb";
    cout << "Rearranged \"" << s2 << "\": " << sol.rearrangeString(s2) << "\n";

    string s3 = "aa";
    cout << "Rearranged \"" << s3 << "\": " << sol.rearrangeString(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N is length of string.
  * Frequency count: O(N).
  * Filling result string by stride 2: O(N).
- Space Complexity: O(26) = O(1) auxiliary space (excluding returned string).

Key Takeaways:
- Filling even positions first with the majority element eliminates the need for 
  a priority queue or sorting.
*/
