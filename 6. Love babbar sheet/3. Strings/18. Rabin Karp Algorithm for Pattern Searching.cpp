// Problem: Rabin-Karp Algorithm for Pattern Searching
// Link (GFG): https://www.geeksforgeeks.org/problems/search-pattern-rabin-karp-algorithm--141631/1
// Article: https://www.geeksforgeeks.org/dsa/rabin-karp-algorithm-for-pattern-searching/
// Difficulty: Medium / Hard
// Topic: String, Rolling Hash, Number Theory, Pattern Searching

/*
Problem Statement:
Given two strings: a text string `txt` and a pattern string `pat`.
Find all 1-based (or 0-based) starting index positions where `pat` appears as a substring 
in `txt` using the Rabin-Karp Rolling Hash algorithm.

Example 1:
Input: txt = "geeksforgeeks", pat = "geek"
Output: [1, 9] (1-based index)
Explanation: "geek" appears at index 1 and index 9.

Example 2:
Input: txt = "ababab", pat = "aba"
Output: [1, 3]

Constraints:
- 1 <= pat.length() <= txt.length() <= 10^5
- Strings consist of lowercase English alphabets.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Naive Substring Matching:
//   * Comparing a pattern of length M against every window in text of length N takes 
//     O(N * M) time due to full string comparisons at each index.
// - In Rabin-Karp:
//   * We assign a numeric HASH VALUE to the pattern and each sliding window of the text.
//   * Sliding the window does NOT require recomputing the hash from scratch in O(M)!
//   * Instead, we use a "ROLLING HASH" in O(1): subtract the leaving character's weighted contribution, 
//     shift left (multiply by base `d`), and add the entering character's value modulo a prime `q`!
//   * Full string comparison is only performed when hashes match (filtering spurious collisions).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Rolling Hash Mathematics:
//   - Let base `d = 256` (number of characters in ASCII).
//   - Let prime `q = 101` (or 10^9 + 7 to minimize collisions).
//   - Pattern hash: `p = sum(pat[i] * d^(m - 1 - i)) % q`.
//   - High-order multiplier: `h = d^(m - 1) % q`.
//   - Rolling to next window:
//       `next_hash = (d * (current_hash - txt[i] * h) + txt[i + m]) % q`.
//       (Add `q` if result is negative to keep within modulo field).
//   - Average Time Complexity: O(N + M).
//   - Space Complexity: O(1) auxiliary space.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> search(string pat, string txt) {
        vector<int> result;
        int m = pat.length();
        int n = txt.length();

        if (m == 0 || n < m) return result;

        int d = 256;      // Base: Number of characters in the alphabet
        int q = 101;      // Modulo: A prime number to avoid overflow

        int p = 0;        // Hash value for pattern
        int t = 0;        // Hash value for current window of text
        int h = 1;        // Multiplier: pow(d, m - 1) % q

        // Compute h = pow(d, m - 1) % q
        for (int i = 0; i < m - 1; ++i) {
            h = (h * d) % q;
        }

        // Calculate initial hash value for pattern and first window of text
        for (int i = 0; i < m; ++i) {
            p = (d * p + pat[i]) % q;
            t = (d * t + txt[i]) % q;
        }

        // Slide the pattern over text one by one
        for (int i = 0; i <= n - m; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Hash check: Only if the rolling hash matches do we verify characters individually.
            // This filters out 99% of mismatches in O(1) time without reading the characters!
            if (p == t) {
                bool match = true;
                for (int j = 0; j < m; ++j) {
                    if (txt[i + j] != pat[j]) {
                        match = false;
                        break; // Spurious hit / hash collision
                    }
                }
                if (match) {
                    result.push_back(i + 1); // 1-based index (GFG standard)
                }
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Rolling Hash Formula: O(1) constant time transition to next window
            // 1. Remove leading digit: (t - txt[i] * h)
            // 2. Shift base left: multiply by d
            // 3. Add trailing digit: + txt[i + m]
            if (i < n - m) {
                t = (d * (t - txt[i] * h) + txt[i + m]) % q;

                // Handle negative value in C++ modulo arithmetic
                if (t < 0) {
                    t = (t + q);
                }
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    string txt = "geeksforgeeks";
    string pat = "geek";

    vector<int> matches = sol.search(pat, txt);
    cout << "Matches for \"" << pat << "\" in \"" << txt << "\" at 1-based indices:\n";
    for (int idx : matches) {
        cout << idx << " ";
    }
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * Best / Average Case: O(N + M) when hash collisions are rare.
  * Worst Case: O(N * M) when all substrings produce identical hash collisions (e.g., txt = "aaaaa", pat = "aaa").
- Space Complexity: O(1) auxiliary space (excluding the output matches vector).

Key Takeaways:
- Rolling hash turns substring comparison from an O(M) operation into an O(1) arithmetic update.
- Used in plagiarism detection, bio-informatics (searching multiple DNA motifs simultaneously).
*/
