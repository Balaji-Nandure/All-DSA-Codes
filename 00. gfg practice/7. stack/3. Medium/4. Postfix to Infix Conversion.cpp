/*
    Problem Name: Postfix to Infix Conversion
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string `s` that represents the postfix form of a valid mathematical expression. Convert it to its infix form.

    Examples:
    Input: s = "ab*c+" 
    Output: ((a*b)+c)
    Explanation: The postfix expression ab*c+ represents (a*b)+c. Therefore, its equivalent infix expression is ((a*b)+c).

    Input: s = "abc/-"
    Output: (a-(b/c))
    Explanation: The postfix expression abc/- represents a-(b/c). Therefore, its equivalent infix expression is (a-(b/c)).

    Constraints:
    3 <= s.size() <= 10^4

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space for strings)

    Approach: Stack-based Operand Combination (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. A postfix expression has operands before the operator (e.g., `AB+`).
    2. To convert it into infix form:
       - We iterate through the postfix string from left to right.
       - If the current character is an operand (alphanumeric):
         * Push it as a single-character string onto the stack.
       - If the current character is an operator (`+`, `-`, `*`, `/`, `^`, etc.):
         * Pop the top string as `right` (second operand).
         * Pop the next top string as `left` (first operand).
         * Combine them with parentheses: `"(" + left + ch + right + ")"`.
         * Push this newly formed infix string back onto the stack.
    3. At the end of the traversal, the stack contains exactly one string, which is the complete infix expression.

    DRY RUN:
    Example: s = "ab*c+"
    - 'a': operand -> push("a") -> st = ["a"]
    - 'b': operand -> push("b") -> st = ["a", "b"]
    - '*': operator -> right = "b", left = "a" -> new str = "(a*b)" -> push("(a*b)") -> st = ["(a*b)"]
    - 'c': operand -> push("c") -> st = ["(a*b)", "c"]
    - '+': operator -> right = "c", left = "(a*b)" -> new str = "((a*b)+c)" -> push("((a*b)+c)") -> st = ["((a*b)+c)"]
    - Traversal ends. Return st.top() = "((a*b)+c)".
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// ============================================================================
// Approach: Stack-based Postfix to Infix Conversion (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    string postToInfix(string exp) {
        stack<string> st;

        for (char ch : exp) {
            // Operand: Convert char 'ch' into a string of length 1 and push onto stack
            if (isalnum(ch)) {
                // string(1, ch) is the fill constructor: creates a string of size 1 with character 'ch'
                // Needed because 'st' is stack<string> and cannot push a raw 'char'
                st.push(string(1, ch));
            }
            // Operator
            else {
                string right = st.top();
                st.pop();

                string left = st.top();
                st.pop();

                string result = "(" + left + ch + right + ")";

                st.push(result);
            }
        }

        return st.top();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string postToInfix(string exp) {
        SolutionStack solver;
        return solver.postToInfix(exp);
    }
};
