/*
Problem:
Index of Closing Bracket for a Given Opening Bracket

Given a string expression containing parentheses '(' and ')',
and an index pos pointing to an opening bracket '(',
find the index of the corresponding closing bracket ')'.

Indexes are 0-based.

Rules:
- The given index always contains '('.
- Parentheses are properly nested.
- Return -1 if no matching closing bracket exists.

Example 1:
Input:
expr = "(a+b)*(c+d)"
pos = 0
Output:
4

Example 2:
Input:
expr = "(a(b)c)"
pos = 0
Output:
6

Approach:
- Use a stack (or counter).
- Traverse the expression starting from pos.
- Push '(' onto stack when found.
- Pop stack when ')' is found.
- When stack becomes empty, current index is the answer.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-index-closing-bracket-given-opening-bracket-expression/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    int findClosingBracket(string expr, int pos) {

        stack<char> st;

        for (int i = pos; i < expr.size(); i++) {

            if (expr[i] == '(') {
                st.push('(');
            }
            else if (expr[i] == ')') {
                st.pop();
                if (st.empty()) {
                    return i;
                }
            }
        }

        return -1;
    }
};
    