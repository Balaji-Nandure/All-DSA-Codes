// Problem: Number of Flips to Make Binary String Alternate (Min Number of Flips)
// Link (GFG): https://www.geeksforgeeks.org/problems/min-number-of-flips3210/1
// Article: https://www.geeksforgeeks.org/dsa/number-flips-make-binary-string-alternate/
// Difficulty: Easy
// Topic: String, Bit Invariant, Greedy, Complement Counting

/*
Problem Statement:
Given a binary string S consisting of '0's and '1's.
Find the minimum number of bit flips required to make the string alternating 
(i.e. no two adjacent characters are identical).

Example 1:
Input: S = "001"
Output: 1
Explanation: Flip the second '0' to '1' -> "011" (wait, "010" by flipping 1st or 2nd bit takes 1 flip).
Result is "010", which is alternating.

Example 2:
Input: S = "0001010111"
Output: 2
Explanation: "0101010101" takes 2 flips.

Constraints:
- 1 <= S.length() <= 10^5
- S consists only of '0' and '1'
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Split Binary String (Problem 12):
//   * We counted cuts where 0s and 1s balanced out dynamically.
// - In Problem 28 (Alternating Binary String):
//   * There are ONLY TWO possible valid alternating states for any string of length N:
//       Target Pattern A: Starts with '0' -> "01010101..."
//       Target Pattern B: Starts with '1' -> "10101010..."
//   * Beautiful mathematical complement property:
//     Target Pattern B is the EXACT BITWISE INVERSE of Target Pattern A!
//     Therefore, any bit that matches Pattern A WILL MISMATCH Pattern B, and vice-versa!
//     This means: `flipsB = N - flipsA`. We only need to count flips for ONE pattern!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Single-Pass Invariant Complement Counting (Optimal & Chosen):
//   - Traverse the string from `i = 0` to `n - 1`.
//   - Compare `S[i]` with Target Pattern A ("010101..."):
//       * If `i % 2 == 0`: Expected character is `'0'`. If `S[i] != '0'`, `flipsA++`.
//       * If `i % 2 != 0`: Expected character is `'1'`. If `S[i] != '1'`, `flipsA++`.
//   - Calculate flips for Target Pattern B:
//       `flipsB = n - flipsA`.
//   - Return `min(flipsA, flipsB)`.
//   - Complexity: O(N) time, O(1) space.
//   - Why this approach: Eliminates generating target strings or making two independent passes.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minFlips(string S) {
        int n = S.length();
        int flipsStartingWith0 = 0;

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Target pattern A expects '0' at even indices and '1' at odd indices:
            // char expected = (i % 2 == 0) ? '0' : '1';
            char expected = (i % 2 == 0) ? '0' : '1';

            if (S[i] != expected) {
                flipsStartingWith0++;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Complementary invariant: Since pattern B ("101010...") is the exact opposite at every
        // index, any bit that didn't need flipping for pattern A MUST be flipped for pattern B!
        int flipsStartingWith1 = n - flipsStartingWith0;

        return min(flipsStartingWith0, flipsStartingWith1);
    }
};

int main() {
    Solution sol;
    string s1 = "001";
    cout << "Min flips for \"" << s1 << "\": " << sol.minFlips(s1) << "\n";

    string s2 = "0001010111";
    cout << "Min flips for \"" << s2 << "\": " << sol.minFlips(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single linear pass of N iterations.
- Space Complexity: O(1) auxiliary space (a single integer accumulator).

Key Takeaways:
- Recognizing dual complementary target states allows solving binary optimization 
  problems in N - X operations without secondary passes.
*/
