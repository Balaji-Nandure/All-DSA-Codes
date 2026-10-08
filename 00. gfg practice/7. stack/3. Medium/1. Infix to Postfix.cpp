/*
    Problem Name: Infix to Postfix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string `s` representing an infix expression, convert this infix expression into a postfix expression.

    Precedence & Associativity Rules:
    1. `^` (exponentiation): Precedence 3, Right-to-Left associativity.
    2. `*` and `/`: Precedence 2, Left-to-Right associativity.
    3. `+` and `-`: Precedence 1, Left-to-Right associativity.
    4. `(` has lowest precedence inside the stack.

    Examples:
    Input: s = "a*(b+c)/d"
    Output: "abc+*d/"
    Explanation: Inside brackets (b+c) -> bc+. a*(bc+) -> abc+*. (abc+*)/d -> abc+*d/.

    Input: s = "a+b*c+d"
    Output: "abc*+d+"

    Input: s = "(a+b)*(c+d)"
    Output: "ab+cd+*"

    Constraints:
    1 <= s.length <= 5 * 10^3
    s[i] can be an operand (a–z, A–Z, 0–9), an operator (+, -, *, /, ^) or a parenthesis ((, ))

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space for operators)

    Approach: Stack-based Shunting-Yard Algorithm (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Maintain an operator stack `stack<char> st` and a result string `result`.
    2. Traverse the infix string character by character:
       - If character is an Operand (alphanumeric `isalnum(ch)`): Append directly to `result`.
       - If character is `'('`: Push onto stack.
       - If character is `')'`: Pop and append to `result` until `'('` is encountered, then pop `'('`.
       - If character is an Operator:
         * Pop operators with higher precedence from stack to `result`.
         * If top of stack has EQUAL precedence, pop if the operator is Left-to-Right associative (`!= '^'`).
         * For Right-to-Left associativity (`'^'`), do NOT pop equal precedence.
         * Push current operator onto stack.
    3. After traversal, pop all remaining operators from stack and append to `result`.
    4. Time: O(N), Space: O(N).

    DRY RUN:
    Example: s = "a*(b+c)/d"
    - 'a': result = "a", st = []
    - '*': st = ['*']
    - '(': st = ['*', '(']
    - 'b': result = "ab", st = ['*', '(']
    - '+': st = ['*', '(', '+']
    - 'c': result = "abc", st = ['*', '(', '+']
    - ')': pop '+' -> result = "abc+", pop '(' -> st = ['*']
    - '/': prec('/') == prec('*') and left-associative -> pop '*' -> result = "abc+*", push '/' -> st = ['/']
    - 'd': result = "abc+*d", st = ['/']
    - End: pop '/' -> result = "abc+*d/".
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// ============================================================================
// Approach: Shunting-Yard Algorithm using Stack (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
private:
    // Helper function to return precedence of operators
    int getPrecedence(char ch) {
        if (ch == '^') return 3;
        if (ch == '*' || ch == '/') return 2;
        if (ch == '+' || ch == '-') return 1;
        return -1; // For '(' and others
    }

public:
    string infixToPostfix(string s) {
        stack<char> st;
        string result = "";

        for (char ch : s) {
            // Case 1: If operand, add directly to result
            if (isalnum(ch)) {
                result += ch;
            }
            // Case 2: If '(', push onto stack
            else if (ch == '(') {
                st.push(ch);
            }
            // Case 3: If ')', pop until '('
            else if (ch == ')') {
                while (!st.empty() && st.top() != '(') {
                    result += st.top();
                    st.pop();
                }
                if (!st.empty() && st.top() == '(') {
                    st.pop(); // Remove '('
                }
            }
            // Case 4: If operator
            else {
                // Pop operators with higher precedence, or same precedence if Left-to-Right associative
                while (!st.empty() && (getPrecedence(ch) < getPrecedence(st.top()) ||
                      (getPrecedence(ch) == getPrecedence(st.top()) && ch != '^'))) {
                    result += st.top();
                    st.pop();
                }
                st.push(ch);
            }
        }

        // Pop all remaining operators in the stack
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }

        return result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string infixToPostfix(string s) {
        SolutionStack solver;
        return solver.infixToPostfix(s);
    }
};
