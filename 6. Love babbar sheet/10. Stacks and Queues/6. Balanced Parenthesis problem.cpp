/**
 * Problem: Balanced Parenthesis Problem
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems involved structure construction (building stacks/queues).
 * - Here, we apply the LIFO property to grammar/syntax validation where every closing delimiter
 *   must match the MOST RECENT unmatched opening delimiter.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Why not simple integer counters?
 *   - A simple count works if there is only ONE bracket type `(` and `)`.
 *   - With multiple bracket types `()`, `[]`, `{}` counters fail because they cannot enforce correct nesting order
 *     (e.g., `[(])` has equal counts of each type but is invalid).
 * - Stack Solution:
 *   - Push opening brackets `(`, `{`, `[`.
 *   - On closing bracket, stack must NOT be empty and top must match corresponding opening bracket.
 *   - At the end, stack must be completely empty.
 * 
 * TIME COMPLEXITY:
 * - O(N) where N is string length (single pass).
 * 
 * SPACE COMPLEXITY:
 * - O(N) in worst case (e.g. all opening brackets `(((((`).
 */

#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string& s) {
    std::stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (st.empty()) return false; // Closing without opening

            char top = st.top();
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Validate that the most recent opening bracket strictly matches the current closing type.
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                st.pop();
            } else {
                return false; // Mismatched type e.g. `[)`
            }
        }
    }

    // Must be completely emptied to be balanced
    return st.empty();
}

int main() {
    std::string s1 = "{([])}";
    std::string s2 = "([)]";
    std::string s3 = "((())";

    std::cout << s1 << " is balanced: " << (isBalanced(s1) ? "true" : "false") << "\n"; // true
    std::cout << s2 << " is balanced: " << (isBalanced(s2) ? "true" : "false") << "\n"; // false
    std::cout << s3 << " is balanced: " << (isBalanced(s3) ? "true" : "false") << "\n"; // false

    return 0;
}
