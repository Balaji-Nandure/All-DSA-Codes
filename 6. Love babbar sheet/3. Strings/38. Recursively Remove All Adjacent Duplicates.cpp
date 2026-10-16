// Problem: Recursively Remove All Adjacent Duplicates
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/consecutive-elements2306/1
// Article: https://www.geeksforgeeks.org/dsa/remove-consecutive-duplicates-string/
// Difficulty: Medium / Hard
// Topic: String, Recursion, Stack, String Reduction

/*
Problem Statement:
Given a string s, remove all adjacent duplicate characters recursively.
That is, if a block of 2 or more identical consecutive characters is found, 
remove the ENTIRE block.
If removing adjacent duplicates causes newly adjacent characters to become identical duplicates, 
repeat the process until no adjacent duplicates remain.

Example 1:
Input: s = "geeksforgeek"
Output: "gksforgk"
Explanation:
"g(ee)ksforg(ee)k" -> "gksforgk".

Example 2:
Input: s = "abccba"
Output: ""
Explanation:
"ab(cc)ba" -> "a(bb)a" -> "(aa)" -> "".

Example 3:
Input: s = "acaaabbbacdddd"
Output: "acac"
Explanation:
"ac(aaa)(bbb)ac(dddd)" -> "ac(aa)c" -> "acac".

Constraints:
- 1 <= s.length() <= 10^5
- s consists of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 30 (Minimum Swaps for Balancing):
//   * Characters were moved via adjacent swaps without deletion.
// - In Problem 38 (Recursive Adjacent Duplicate Removal):
//   * Deletion of a contiguous identical segment causes a CASCADING COLLAPSE:
//     Characters originally separated by the deleted block suddenly become adjacent!
//   * E.g., in "abccba", deleting "cc" makes the two 'b's touch, which delete each other, 
//     making the two 'a's touch, which also delete each other.
//   * A single linear pass without recursion or a backtrackable stack cannot detect 
//     these newly formed adjacencies!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Recursive String Reduction
//   - In each recursive pass, scan `s`:
//       * If `s[i] == s[i+1]`: skip the entire contiguous duplicate block.
//       * Else: append `s[i]`.
//   - If the newly formed string is identical to `s`, terminate (no more duplicates).
//   - Otherwise, recurse on the new string.
//   - Complexity: O(N * depth) where depth is the number of cascade rounds.
//
// Approach 2: Stack-Based In-Place Simulation (Optimal for LeetCode 1047 / 1209)
//   - Use a vector/string as a stack.
//   - Maintain `{char, count}` on the stack to dynamically pop when count >= 2.
//   - Complexity: O(N) time, O(N) auxiliary space.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // Recursive Cascading Elimination (GFG Standard Problem)
    string rremove(string s) {
        string res = "";
        int n = s.length();
        int i = 0;

        while (i < n) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if s[i] starts a contiguous run of 2 or more identical characters
            if (i < n - 1 && s[i] == s[i + 1]) {
                // Advance pointer i to bypass the ENTIRE block of duplicates
                while (i < n - 1 && s[i] == s[i + 1]) {
                    i++;
                }
            } else {
                // Character is unique in its neighborhood; keep it
                res += s[i];
            }
            i++;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Termination condition: If the length of the string did not change,
        // no duplicates were removed in this pass, meaning reduction is complete!
        // Otherwise, recurse on the condensed string to catch newly created adjacencies.
        if (res.length() == s.length()) {
            return res;
        }

        return rremove(res);
    }

    // Alternative: Stack-based Pairwise Removal (LeetCode 1047)
    string removeDuplicatesPairwise(string s) {
        string st = "";
        for (char ch : s) {
            if (!st.empty() && st.back() == ch) {
                st.pop_back(); // Pop adjacent pair
            } else {
                st.push_back(ch);
            }
        }
        return st;
    }
};

int main() {
    Solution sol;
    string s1 = "geeksforgeek";
    cout << "rremove(\"" << s1 << "\"): " << sol.rremove(s1) << "\n";

    string s2 = "abccba";
    cout << "rremove(\"" << s2 << "\"): \"" << sol.rremove(s2) << "\"\n";

    string s3 = "acaaabbbacdddd";
    cout << "rremove(\"" << s3 << "\"): " << sol.rremove(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * D) where N is length of string and D is depth of cascading reductions.
  * In practice, D is typically small (< 5-10 passes).
- Space Complexity: O(N * D) due to recursion stack frames and temporary string copies.

Key Takeaways:
- Detecting whether `res.length() == s.length()` is the clean recursive fixpoint indicator 
  for multi-round string reductions.
*/
