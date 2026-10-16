// Problem: Balanced Parenthesis Problem [Imp]
// Link (GFG): https://www.geeksforgeeks.org/problems/parenthesis-checker2744/1
// Article: https://www.geeksforgeeks.org/dsa/check-for-balanced-parentheses-in-an-expression/
// Difficulty: Easy / Medium
// Topic: String, Stack, LIFO Invariant

/*
Problem Statement:
Given a string s composed of bracket characters: '(', ')', '{', '}', '[' and ']'.
Determine if the input string is balanced.
A string is balanced if:
  1. Open brackets are closed by the same type of brackets.
  2. Open brackets are closed in the correct order (LIFO - Last In, First Out).
  3. Every closing bracket has a corresponding open bracket of the same type.

Example 1:
Input: s = "{([])}"
Output: true

Example 2:
Input: s = "()"
Output: true

Example 3:
Input: s = "([]"
Output: false (unclosed '[')

Example 4:
Input: s = "(]"
Output: false (mismatched bracket types)

Constraints:
- 1 <= s.length() <= 10^5
- s consists only of '(', ')', '{', '}', '[', ']'
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 12 (Split Binary String with Equal 0s and 1s):
//   * A simple integer counter was sufficient because '0' and '1' had no nesting syntax.
// - In Problem 16 (Balanced Parentheses with Multiple Types):
//   * An integer counter FAILS for multi-bracket expressions!
//     E.g., for "([)]", count of '(' matches ')' and count of '[' matches ']', 
//     yet the string is NOT valid because '[' and ')' cross each other!
//   * A Stack is strictly required to enforce the LIFO nesting property: 
//     The MOST RECENTLY OPENED bracket must be the FIRST ONE CLOSED!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach: Monotonic Stack (Optimal & Standard)
//   - Initialize an empty `stack<char> st`.
//   - For each character `ch` in `s`:
//       * If `ch` is an opening bracket ('(', '{', '['):
//           Push onto the stack.
//       * If `ch` is a closing bracket (')', '}', ']'):
//           - If the stack is empty: Unmatched closing bracket -> return `false`!
//           - If `st.top()` does not match `ch`: Type mismatch -> return `false`!
//           - Otherwise: Matching pair found, pop `st.pop()`.
//   - After the loop:
//       * Return `st.empty()` (ensures no unclosed opening brackets linger).
//   - Complexity: O(N) time, O(N) auxiliary space.

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool ispar(string x) {
        stack<char> st;

        for (char ch : x) {
            // Opening brackets: Push to maintain nesting history
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } 
            // Closing brackets: Must match the topmost open bracket
            else {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Guard 1: If stack is empty when a closing bracket arrives, there is no opening pair!
                if (st.empty()) {
                    return false;
                }

                char top = st.top();

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Guard 2: The most recently opened bracket must be the exact complementary opening type!
                if ((ch == ')' && top == '(') ||
                    (ch == '}' && top == '{') ||
                    (ch == ']' && top == '[')) {
                    st.pop(); // Successful match, resolve this nested pair
                } else {
                    return false; // Mismatched bracket type (e.g., '(' closed by ']')
                }
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard 3: If stack is not empty after scanning the full string, some opening brackets were never closed!
        return st.empty();
    }
};

int main() {
    Solution sol;
    string s1 = "{([])}";
    cout << s1 << " is balanced? " << (sol.ispar(s1) ? "Yes" : "No") << "\n";

    string s2 = "([)]";
    cout << s2 << " is balanced? " << (sol.ispar(s2) ? "Yes" : "No") << "\n";

    string s3 = "((";
    cout << s3 << " is balanced? " << (sol.ispar(s3) ? "Yes" : "No") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single pass over string of length N; each character is pushed and popped at most once.
- Space Complexity: O(N) auxiliary space for the stack in the worst case (e.g., "(((((").

Key Takeaways:
- Counters only work for single bracket types; stacks are mandatory for multiple interleaved bracket types.
*/
