// Problem: Convert Sentence into Equivalent Mobile Numeric Keypad Sequence
// Link (GFG): https://www.geeksforgeeks.org/problems/convert-a-sentence-into-its-equivalent-mobile-numeric-keypad-sequence0547/1
// Article: https://www.geeksforgeeks.org/dsa/convert-sentence-equivalent-mobile-numeric-keypad-sequence/
// Difficulty: Easy
// Topic: String, Hash Table / Direct Index Mapping, Simulation

/*
Problem Statement:
Given a sentence in the form of a string in UPPERCASE letters, convert it into its 
equivalent mobile numeric keypad sequence (classic 12-key telephone keypad / T9).

Keypad Mapping:
  2: A, B, C       -> "2", "22", "222"
  3: D, E, F       -> "3", "33", "333"
  4: G, H, I       -> "4", "44", "444"
  5: J, K, L       -> "5", "55", "555"
  6: M, N, O       -> "6", "66", "666"
  7: P, Q, R, S    -> "7", "77", "777", "7777"
  8: T, U, V       -> "8", "88", "888"
  9: W, X, Y, Z    -> "9", "99", "999", "9999"
  0: ' ' (Space)   -> "0"

Example 1:
Input: S = "GEEKSFORGEEKS"
Output: "4333355777733366677743333557777"
Explanation:
'G' = "4", 'E' = "33", 'K' = "55", 'S' = "7777", etc.

Example 2:
Input: S = "HELLO WORLD"
Output: "4433555555666096667775553"

Constraints:
- 1 <= S.length() <= 10^5
- S contains uppercase English characters and spaces.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In previous algorithmic string questions:
//   * Decisions were stateful, dynamic, or combinatorial.
// - In Problem 20 (Keypad Encoding):
//   * This is a 1-to-many DETERMINISTIC LOOKUP mapping.
//   * The key design decision is avoiding expensive multiple `if-else` or `switch` branches 
//     by precomputing a static 26-element lookup table indexed directly by `ch - 'A'`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Direct Index Lookup Table (Optimal & Chosen):
//   - Array `keypad[26]` where `keypad[ch - 'A']` holds the digit string.
//   - Iterate through sentence:
//       * If `ch == ' '`: Append `"0"`.
//       * If `'A' <= ch <= 'Z'`: Append `keypad[ch - 'A']`.
//   - Complexity: O(N) time, O(1) auxiliary space (excluding result string).
//   - Why this approach: O(1) table lookup with zero hashing overhead.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string printSequence(string S) {
        // Precomputed lookup array for all 26 uppercase English letters
        static const string keypad[26] = {
            "2",    // A
            "22",   // B
            "222",  // C
            "3",    // D
            "33",   // E
            "333",  // F
            "4",    // G
            "44",   // H
            "444",  // I
            "5",    // J
            "55",   // K
            "555",  // L
            "6",    // M
            "66",   // N
            "666",  // O
            "7",    // P
            "77",   // Q
            "777",  // R
            "7777", // S
            "8",    // T
            "88",   // U
            "888",  // V
            "9",    // W
            "99",   // X
            "999",  // Y
            "9999"  // Z
        };

        string output = "";
        output.reserve(S.length() * 3); // Pre-allocate to prevent repeated memory re-allocations

        for (char ch : S) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Direct O(1) array index mapping: 'ch - 'A'' transforms character into table index.
            if (ch == ' ') {
                output += "0";
            } else if (ch >= 'A' && ch <= 'Z') {
                output += keypad[ch - 'A'];
            }
        }

        return output;
    }
};

int main() {
    Solution sol;
    string s1 = "GEEKSFORGEEKS";
    cout << "Encoded \"" << s1 << "\":\n" << sol.printSequence(s1) << "\n\n";

    string s2 = "HELLO WORLD";
    cout << "Encoded \"" << s2 << "\":\n" << sol.printSequence(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N is the length of the string. Each character is converted in O(1).
- Space Complexity: O(1) auxiliary space (lookup table is static 26 strings).

Key Takeaways:
- Static arrays indexed by `ch - 'A'` are the fastest possible mapping mechanism in C++.
*/
