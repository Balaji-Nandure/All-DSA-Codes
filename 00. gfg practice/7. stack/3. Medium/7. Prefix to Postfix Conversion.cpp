/*
    Problem Name: Prefix to Postfix Conversion
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given a string `s` that represents the prefix form of a valid mathematical expression.
    Convert it to its postfix form.

    Examples:
    Input: s = "+AB"
    Output: "AB+"
    Explanation: In postfix form, operands come first followed by the operator.
                 Prefix: +AB -> Infix: A + B -> Postfix: AB+

    Input: s = "*+ABC"
    Output: "AB+C*"
    Explanation: Prefix: *+ABC -> Infix: (A + B) * C -> Postfix: AB+C*

    Input: s = "*-A/BC-/AKL"
    Output: "ABC/-AK/L-*"
    Explanation: Prefix: *-A/BC-/AKL -> Infix: (A - (B / C)) * ((A / K) - L)
                 Left part: (A - (B / C)) -> Postfix: ABC/-
                 Right part: ((A / K) - L) -> Postfix: AK/L-
                 Combine with '*': ABC/-AK/L-*

    Constraints:
    3 <= s.size() <= 10^5

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space for strings)

    Approach: Stack-based Right-to-Left Traversal (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. In Prefix notation, the operator appears before operands: `op op1 op2`.
    2. In Postfix notation, operands appear before the operator: `op1 op2 op`.
    3. Scanning the prefix string from right to left (index n-1 down to 0):
       - If the current character is an operand (alphanumeric):
         * Push it as a single-character string onto the stack.
       - If the current character is an operator (`+`, `-`, `*`, `/`, `^`, `%`, etc.):
         * Pop the first element from the stack as `op1` (left operand).
         * Pop the second element from the stack as `op2` (right operand).
         * Combine them into postfix form: `op1 + op2 + ch`.
         * Push this combined postfix string back onto the stack.
    4. At the end of traversal, `st.top()` contains the complete postfix expression.

    DRY RUN:
    Example: s = "*+ABC", n = 5
    - i = 4 (ch = 'C'): operand -> push("C") -> st = ["C"]
    - i = 3 (ch = 'B'): operand -> push("B") -> st = ["C", "B"]
    - i = 2 (ch = 'A'): operand -> push("A") -> st = ["C", "B", "A"]
    - i = 1 (ch = '+'): operator ->
      op1 = top() = "A", pop()
      op2 = top() = "B", pop()
      new_str = "A" + "B" + "+" = "AB+"
      push("AB+") -> st = ["C", "AB+"]
    - i = 0 (ch = '*'): operator ->
      op1 = top() = "AB+", pop()
      op2 = top() = "C", pop()
      new_str = "AB+" + "C" + "*" = "AB+C*"
      push("AB+C*") -> st = ["AB+C*"]
    - Return st.top() = "AB+C*".
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// ============================================================================
// Approach: Stack-based Prefix to Postfix (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    string preToPost(string s) {
        stack<string> st;
        int n = s.length();

        // Traverse the prefix expression from right to left
        for (int i = n - 1; i >= 0; i--) {
            char ch = s[i];

            // Operand: Convert char 'ch' into a string of length 1 and push onto stack
            if (isalnum(ch)) {
                // string(1, ch) is the fill constructor: creates a string of size 1 with character 'ch'
                // Needed because 'st' is stack<string> and cannot push a raw 'char'
                st.push(string(1, ch));
            }
            // Operator: Pop top two operands, combine as (op1 + op2 + ch), and push back
            else {
                // First popped element is the left operand
                string op1 = st.top();
                st.pop();

                // Second popped element is the right operand
                string op2 = st.top();
                st.pop();

                string result = op1 + op2 + ch;
                st.push(result);
            }
        }

        // The final element in the stack is the complete postfix expression
        return st.top();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string preToPost(string s) {
        SolutionStack solver;
        return solver.preToPost(s);
    }
};
