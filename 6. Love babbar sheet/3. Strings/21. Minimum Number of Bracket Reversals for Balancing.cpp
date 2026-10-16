// Problem: Minimum Number of Bracket Reversals Needed to Make Expression Balanced
// Link (GFG): https://www.geeksforgeeks.org/problems/count-the-reversals0401/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-number-of-bracket-reversals-needed-to-make-an-expression-balanced/
// Difficulty: Medium
// Topic: String, Stack, Greedy, Invariant Math

/*
Problem Statement:
Given a string s consisting only of '{' and '}'. 
Find the minimum number of reversals of brackets required to make the string balanced.
A reversal means turning a '{' into '}' or '}' into '{'.
If it is impossible to balance the string, return -1.

Example 1:
Input: s = "}{{}}{{"
Output: 2
Explanation:
Change the first bracket '}' to '{', and the last bracket '{' to '}'.
The string becomes "{{{}}}", which is balanced.

Example 2:
Input: s = "{{}{{{}{{}}{{"
Output: -1 (Length is 11, which is odd. An odd number of brackets cannot be paired up).

Example 3:
Input: s = "{{{{"
Output: 2
Explanation: Change 3rd and 4th '{' to '}' -> "{{}}".

Constraints:
- 1 <= s.length() <= 10^5
- s consists only of '{' and '}'
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 16 (Balanced Parenthesis):
//   * We only verified whether the string was already balanced (boolean predicate).
// - In Problem 21 (Count Reversals):
//   * The string is NOT balanced, and we must calculate the MINIMAL MUTATIONS (reversals) 
//     to MAKE it balanced.
//   * Key invariant: Once all valid pairs `{}` are eliminated, the remaining unmatched 
//     brackets strictly form the pattern:
//       `}}...}{{...{`  (m closing brackets followed by n opening brackets).
//     Any `{` appearing before a `}` would have already cancelled out!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Stack Simulation
//   - Push unmatched brackets into a stack. Count remaining `{` and `}`.
//   - Complexity: O(N) time, O(N) space.
//
// Approach 2: O(1) Space Counter Cancellation (Optimal & Chosen)
//   - Guard: If `s.length() % 2 != 0`, return -1 immediately.
//   - Track two counters: `openCount = 0` (unmatched '{') and `closeCount = 0` (unmatched '}').
//   - Iterate through `s`:
//       * If `ch == '{'`: `openCount++`.
//       * If `ch == '}'`:
//           - If `openCount > 0`: Match made! `openCount--`.
//           - Else: No open bracket available, so `closeCount++`.
//   - Analysis of remaining unmatched brackets:
//       * Each pair of `}}` requires 1 reversal to become `{}` -> `closeCount / 2`.
//       * Each pair of `{{` requires 1 reversal to become `{}` -> `openCount / 2`.
//       * If both are odd (e.g. `}{`), they share 1 remainder each, requiring 2 reversals to become `{}`!
//       * Closed mathematical formula:
//         `reversals = (closeCount + 1) / 2 + (openCount + 1) / 2`
//   - Complexity: O(N) time, O(1) auxiliary space!
//   - Why this approach: Avoids stack memory allocation entirely.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int countRev(string s) {
        int n = s.length();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard 1: An odd-length bracket string can NEVER be balanced because every open
        // bracket requires a partner closing bracket.
        if (n % 2 != 0) {
            return -1;
        }

        int openCount = 0;  // Tracks available unmatched '{'
        int closeCount = 0; // Tracks unmatched '}'

        for (char ch : s) {
            if (ch == '{') {
                openCount++;
            } else {
                // If there's an available opening bracket, pair it up
                if (openCount > 0) {
                    openCount--;
                } else {
                    // Otherwise, this closing bracket is permanently unmatched
                    closeCount++;
                }
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Formula: Ceiling division of both unmatched groups.
        // E.g., `}}` takes 1 reversal -> ceil(2/2) = 1.
        // E.g., `}{` takes 2 reversals -> ceil(1/2) + ceil(1/2) = 1 + 1 = 2.
        return (closeCount + 1) / 2 + (openCount + 1) / 2;
    }
};

int main() {
    Solution sol;
    string s1 = "}{{}}{{";
    cout << "Reversals needed for \"" << s1 << "\": " << sol.countRev(s1) << "\n";

    string s2 = "{{{{";
    cout << "Reversals needed for \"" << s2 << "\": " << sol.countRev(s2) << "\n";

    string s3 = "{{}{{{}{{}}{{";
    cout << "Reversals needed for \"" << s3 << "\": " << sol.countRev(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single pass over string.
- Space Complexity: O(1) auxiliary space (no stack used).

Key Takeaways:
- Once valid pairs are cancelled, the residual unmatched string is strictly `}}...}{{...{`,
  which allows a direct closed-form mathematical solution in O(1) space.
*/
