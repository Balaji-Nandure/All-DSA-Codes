/*
    Problem Name: Prefix to Infix Conversion
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string `s` representing a valid mathematical expression in prefix notation.
    The string consists of uppercase and lowercase English letters as operands, and the operators +, -, *, /, %, and ^.
    Convert the given prefix expression into its equivalent fully parenthesized infix expression and return the resulting string.

    Examples:
    Input: s = "*-A/BC-/AKL"
    Output: ((A-(B/C))*((A/K)-L))
    Explanation: The prefix expression starts with '*', so the final operation is multiplication.
                 The left subexpression '-A/BC' converts to '(A-(B/C))', and the right subexpression '-/AKL' converts to '((A/K)-L)'.
                 Combining these two subexpressions with '*' gives: ((A-(B/C))*((A/K)-L))

    Input: s = "+A*BC"
    Output: (A+(B*C))
    Explanation: The prefix expression starts with '+', so the final operation is addition.
                 The left operand is 'A', and the right subexpression '*BC' converts to '(B*C)'.
                 Combining them with '+' gives: (A+(B*C))

    Constraints:
    3 <= |s| <= 10^5

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space for strings)

    Approach: Stack-based Right-to-Left Traversal (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. In Prefix notation, an operator precedes its operands (e.g., `+ A B`).
    2. Traversing from right to left (end to beginning):
       - Any operands encountered are pushed onto a stack of strings.
       - When an operator is encountered:
         * The first popped string `op1` is the LEFT operand.
         * The second popped string `op2` is the RIGHT operand.
         * Combine them into a parenthesized infix string: `"(" + op1 + ch + op2 + ")"`.
         * Push this combined string back onto the stack.
    3. After iterating through the entire string, the stack will contain exactly one element,
       which is the fully parenthesized infix expression.

    DRY RUN:
    Example: s = "+A*BC", n = 5
    - i = 4 (ch = 'C'): operand -> push("C") -> st = ["C"]
    - i = 3 (ch = 'B'): operand -> push("B") -> st = ["C", "B"]
    - i = 2 (ch = '*'): operator ->
      op1 = top() = "B", pop()
      op2 = top() = "C", pop()
      new_str = "(" + "B" + "*" + "C" + ")" = "(B*C)"
      push("(B*C)") -> st = ["(B*C)"]
    - i = 1 (ch = 'A'): operand -> push("A") -> st = ["(B*C)", "A"]
    - i = 0 (ch = '+'): operator ->
      op1 = top() = "A", pop()
      op2 = top() = "(B*C)", pop()
      new_str = "(" + "A" + "+" + "(B*C)" + ")" = "(A+(B*C))"
      push("(A+(B*C))") -> st = ["(A+(B*C))"]
    - Return st.top() = "(A+(B*C))".
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// ============================================================================
// Approach: Stack-based Prefix to Infix (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    string preToInfix(string s) {
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
            // Operator: Pop top two operands, combine them with 'ch', and push back
            else {
                // First popped element is the left operand
                string op1 = st.top();
                st.pop();

                // Second popped element is the right operand
                string op2 = st.top();
                st.pop();

                string result = "(" + op1 + ch + op2 + ")";
                st.push(result);
            }
        }

        // The final element in the stack is the complete infix expression
        return st.top();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string preToInfix(string s) {
        SolutionStack solver;
        return solver.preToInfix(s);
    }
};
