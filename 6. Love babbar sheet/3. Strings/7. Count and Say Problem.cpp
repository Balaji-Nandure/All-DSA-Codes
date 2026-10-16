// Problem: Count and Say Problem (Look-and-Say Sequence)
// Link (GFG): https://www.geeksforgeeks.org/problems/decode-the-pattern1138/1
// Article: https://www.geeksforgeeks.org/dsa/look-and-say-sequence/
// Difficulty: Medium
// Topic: String, Simulation, Run-Length Encoding

/*
Problem Statement:
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
  countAndSay(1) = "1"
  countAndSay(n) is the run-length encoding of countAndSay(n - 1).

To determine how you "say" a digit string, split it into the minimal number of substrings 
such that each substring contains exactly one unique digit. Then for each substring, 
say the number of digits, then say the digit. Finally, concatenate every saying.

Example 1:
Input: n = 1
Output: "1"

Example 2:
Input: n = 4
Output: "1211"
Explanation:
countAndSay(1) = "1"
countAndSay(2) = say "1" = one 1 = "11"
countAndSay(3) = say "11" = two 1s = "21"
countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"

Example 3:
Input: n = 5
Output: "111221"

Constraints:
- 1 <= n <= 30
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In previous string problems:
//   * The input string was provided statically, and we analyzed or searched it.
// - In Count and Say:
//   * The string is GENERATIVE and self-referential: each generation is produced by 
//     compressing the consecutive run-lengths of the previous generation!
//   * The sequence length grows by ~30% each step (known as Conway's constant λ ≈ 1.303577).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Recursive Simulation
//   - Directly translate recurrence `f(n) = encode(f(n-1))`.
//   - Why: Adds function call stack overhead without any benefit.
//
// Approach 2: Iterative Simulation with Two Pointers / Run-Length Encoding (Optimal & Chosen)
//   - Base case: `curr = "1"`.
//   - For `step = 2` to `n`:
//     * Traverse `curr` using two pointers `i` and `j` to identify blocks of identical characters.
//     * While `j < curr.length() && curr[j] == curr[i]`: `j++`.
//     * Count of character `curr[i]` is `j - i`.
//     * Append `to_string(j - i)` followed by `curr[i]` to `nextStr`.
//     * Advance `i = j`.
//     * Replace `curr = nextStr`.
//   - Why this approach: Highly efficient, avoids recursion, generates string in a single linear pass per step.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if (n <= 0) return "";
        string curr = "1";

        // Iteratively build from 2 to n
        for (int step = 2; step <= n; ++step) {
            string nextStr = "";
            int len = curr.length();
            int i = 0;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Run-length encoding: Group contiguous runs of the same digit.
            // Pointer `j` expands forward while characters match `curr[i]`.
            while (i < len) {
                int j = i;
                while (j < len && curr[j] == curr[i]) {
                    j++;
                }

                int runLength = j - i;
                nextStr += to_string(runLength);
                nextStr += curr[i];

                i = j; // Advance outer pointer to start of next run
            }

            curr = std::move(nextStr);
        }

        return curr;
    }
};

int main() {
    Solution sol;
    for (int i = 1; i <= 6; ++i) {
        cout << "n = " << i << " : " << sol.countAndSay(i) << "\n";
    }

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(Sum of lengths of strings from 1 to N).
  * For n = 30, the 30th string has length ~4462 characters.
  * The entire loop runs in under 5 milliseconds.
- Space Complexity: O(L) where L is the length of the string at step n.

Key Takeaways:
- Run-length encoding with two pointers `(j - i)` is the most reliable pattern for contiguous identical sequences.
*/
