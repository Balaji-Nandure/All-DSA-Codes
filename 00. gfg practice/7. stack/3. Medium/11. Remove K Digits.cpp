/*
    Problem Name: Remove K Digits
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 402

    Problem Statement:
    Given a non-negative integer `s` represented as a string and an integer `k`,
    remove exactly `k` digits from the string so that the resulting number is the
    smallest possible, while maintaining the relative order of the remaining digits.

    Notes:
    - The resulting number must not contain any leading zeros.
    - If the resulting number is an empty string after removal, return "0".

    Examples:
    Input: s = "4325043", k = 3
    Output: "2043"
    Explanation: Removing 4, 3, and 5 results in "2043", which is the smallest possible.

    Input: s = "765028321", k = 5
    Output: "221"
    Explanation: Removing 7, 6, 5, 8, and 3 results in "0221" -> removing leading zeros gives "221".

    Input: s = "10200", k = 1
    Output: "200"
    Explanation: Removing 1 leaves "0200" -> stripping leading zeros gives "200".

    Input: s = "10", k = 2
    Output: "0"
    Explanation: Removing all 2 digits leaves "" -> return "0".

    Constraints:
    1 <= k <= |s| <= 10^6
    s consists of digits ('0'-'9').

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack / string space)

    Approach 1: Monotonic Stack using std::stack<char> (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Monotonic Stack using std::string as Stack (Optimal O(N) Time, O(1) Auxiliary Space)

    INTUITION & STRATEGY:
    1. A number is smaller when smaller digits are placed at higher significant positions (from the left).
       For example, given "43", 3 is smaller than 4, so choosing "3" is better than "4".
    2. Therefore, whenever we see a digit `s[i]` that is smaller than the preceding digit (top of stack),
       we should discard the preceding larger digit (if we still have `k > 0` removals left).
    3. This gives us a Monotonic Non-Decreasing Stack:
       - For each digit `ch` in `s`:
         * While `st` is not empty, `k > 0`, and `st.back() > ch`:
           - Pop `st.back()` and decrement `k--`.
         * Push `ch` onto the stack.
    4. Corner Cases:
       - If `k > 0` after the loop (e.g., input was already sorted like "12345"):
         * Pop the remaining `k` elements from the back (largest digits are at the end).
       - Leading Zeros:
         * Strip all leading zeros from the final result.
       - If the string becomes empty (e.g., all digits removed or all were '0'):
         * Return "0".

    DRY RUN:
    Example: s = "4325043", k = 3
    - '4': push -> st = "4"
    - '3': 4 > 3 and k > 0 -> pop 4, k = 2 -> push 3 -> st = "3"
    - '2': 3 > 2 and k > 0 -> pop 3, k = 1 -> push 2 -> st = "2"
    - '5': 2 < 5 -> push 5 -> st = "25"
    - '0': 5 > 0 and k > 0 -> pop 5, k = 0 -> push 0 -> st = "20"
    - '4': k = 0 -> push 4 -> st = "204"
    - '3': k = 0 -> push 3 -> st = "2043"
    - Strip leading zeros -> "2043".
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 2: Monotonic Stack using std::string as Stack (Optimal O(N) Time, O(1) Aux)
// ============================================================================
class SolutionStringStack {
public:
    string removeKdigits(string s, int k) {
        int n = s.length();
        if (k >= n) return "0";

        string st = "";

        // Step 1: Use string directly as a monotonic stack
        for (char ch : s) {
            while (!st.empty() && k > 0 && st.back() > ch) {
                st.pop_back();
                k--;
            }
            st.push_back(ch);
        }

        // Step 2: Remove remaining k digits from the back
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }

        // Step 3: Skip leading zeros
        int start = 0;
        while (start < st.size() && st[start] == '0') {
            start++;
        }

        string result = st.substr(start);

        return result.empty() ? "0" : result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string removeKdigits(string s, int k) {
        SolutionStringStack solver;
        return solver.removeKdigits(s, k);
    }
};
