#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Expression contains redundant bracket or not (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/expression-contains-redundant-bracket-or-not/1
 *
 * Problem Statement:
 *   Given a string of balanced expression s, check if it contains a redundant parenthesis or not.
 *   A set of parenthesis are redundant if the same sub-expression is surrounded by unnecessary or multiple brackets.
 *   Note: Expression may contain +, -, *, and / operators. Given expression is valid and there are no white spaces present.
 *
 * Core Intuition / Idea:
 *   - Brackets are redundant if the sub-expression enclosed within them does not contain any operator.
 *   - For example, in `((a+b))`, the outer brackets enclose `a+b` which has the operator `+`.
 *     However, the inner brackets also enclose `a+b`. When we pop for the outer bracket, there are no operators
 *     left between `(` and `)`. Hence, redundant.
 *   - We use a stack to push all opening brackets and operators. When we encounter a closing bracket,
 *     we check if any operator exists between this closing bracket and its matching opening bracket.
 *     If no operator exists, it means the brackets are redundant.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Push Elements:** Iterate through the expression character-by-character.
 *       If the character is an opening bracket `'('` or an operator (`'+'`, `'-'`, `'*'`, `'/'`), push it onto the stack.
 *   2️⃣ **Pop & Validate on Closing Bracket:** When we see `')'`, we check the top of the stack:
 *       - If the top of the stack is `'('`, it means no operator was found inside these brackets. Return `1` (redundant).
 *       - Otherwise, pop all operators from the stack until we hit `'('`, then pop `'('` itself.
 *   3️⃣ **Return Result:** If the loop finishes without finding any redundant brackets, return `0`.
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N) where N is the length of the string `s`. Each character is pushed and popped from the stack at most once.
 *   - Space Complexity (SC): O(N) in the worst case for stack storage when all characters are pushed.
 *
 * Dry Run:
 *   s = "((a+b))"
 *   - i=0: '(' -> push '('. Stack: ['(']
 *   - i=1: '(' -> push '('. Stack: ['(', '(']
 *   - i=2: 'a' -> operand, ignore.
 *   - i=3: '+' -> push '+'. Stack: ['(', '(', '+']
 *   - i=4: 'b' -> operand, ignore.
 *   - i=5: ')' -> top is '+'. Pop '+'. Now top is '('. Pop '('. Stack: ['(']
 *   - i=6: ')' -> top is '('. Since top of stack is '(', it is redundant! Return 1.
 */

class Solution {
public:
    int checkRedundancy(string s) {
        stack<char> st;
        
        for (char ch : s) {
            // Push opening brackets and operators onto the stack
            if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                st.push(ch);
            } 
            // If it is a closing bracket, check for redundancy
            else if (ch == ')') {
                // If top of stack is '(' immediately, it means there are no operators inside
                if (st.top() == '(') {
                    return 1; // Redundant brackets found
                }
                
                // Pop all operators until we find the matching '('
                while (!st.empty() && st.top() != '(') {
                    st.pop();
                }
                
                // Pop the matching '('
                if (!st.empty()) {
                    st.pop();
                }
            }
        }
        
        return 0; // No redundant brackets found
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    vector<string> tests = {
        "((a+b))",     // Expected: 1 (redundant)
        "(a+(b)/c)",   // Expected: 1 (redundant)
        "(a+b+(c+d))"  // Expected: 0 (not redundant)
    };
    
    for (string s : tests) {
        cout << "Expression: " << s << " -> Redundant? " << (sol.checkRedundancy(s) ? "Yes" : "No") << endl;
    }
    return 0;
}
