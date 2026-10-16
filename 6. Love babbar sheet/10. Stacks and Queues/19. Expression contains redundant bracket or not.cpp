/**
 * Problem: Expression contains redundant bracket or not
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Balanced Parenthesis problem", any valid nesting was considered correct.
 * - Here, even if parentheses are syntactically balanced, a pair is deemed REDUNDANT if:
 *   1. It encloses an expression that is already enclosed by another pair, e.g., `((a+b))`
 *   2. It wraps a single variable or contains NO operators at all, e.g., `(a)`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Operator-Tracking Stack:
 *   - Traverse string character by character:
 *     - If `(`, `+`, `-`, `*`, or `/`, push onto the stack.
 *     - If `)` is encountered:
 *       - Check the stack top:
 *         - If the immediate top is `(`, there are ZERO operators between them -> REDUNDANT!
 *         - Otherwise, pop elements and flag if any valid operator was present before reaching `(`.
 *         - If no operator was between them -> REDUNDANT!
 *         - Pop the opening `(`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each character is pushed and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the stack.
 */

#include <iostream>
#include <stack>
#include <string>

bool checkRedundancy(const std::string& s) {
    std::stack<char> st;

    for (char ch : s) {
        // Push opening brackets and all arithmetic operators
        if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            st.push(ch);
        } else if (ch == ')') {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If the top element is immediately '(', no operator was enclosed -> strictly redundant!
            if (st.top() == '(') {
                return true;
            }

            bool hasOperator = false;
            while (!st.empty() && st.top() != '(') {
                char top = st.top();
                if (top == '+' || top == '-' || top == '*' || top == '/') {
                    hasOperator = true;
                }
                st.pop();
            }

            // Pop the opening '('
            if (!st.empty()) st.pop();

            if (!hasOperator) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    std::string s1 = "((a+b))";
    std::string s2 = "(a+(b)/c)";
    std::string s3 = "(a+b*(c-d))";

    std::cout << s1 << " contains redundant: " << (checkRedundancy(s1) ? "Yes" : "No") << "\n"; // Yes
    std::cout << s2 << " contains redundant: " << (checkRedundancy(s2) ? "Yes" : "No") << "\n"; // Yes (around b)
    std::cout << s3 << " contains redundant: " << (checkRedundancy(s3) ? "Yes" : "No") << "\n"; // No

    return 0;
}
