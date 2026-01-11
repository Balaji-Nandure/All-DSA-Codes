/*
Problem:
Valid Parentheses in an Expression

Given an expression string consisting of parentheses:
'(', ')', '{', '}', '[', ']',
check whether the expression has valid (balanced) parentheses.

Rules:
- Every opening bracket must be closed by the same type.
- Closing brackets must be in the correct order.
- An empty expression is valid.

Example 1:
Input:  "{[()]}"
Output: true

Example 2:
Input:  "{[(])}"
Output: false

Example 3:
Input:  "()[]{}"
Output: true

Approach:
- Use a stack to track opening brackets.
- Traverse the string:
  - If opening bracket, push onto stack.
  - If closing bracket:
    - Stack must not be empty.
    - Top of stack must match the closing bracket.
- After traversal, stack must be empty for a valid expression.

GeeksforGeeks:
https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/

LeetCode:
https://leetcode.com/problems/valid-parentheses/

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
    public:
        bool isValid(string s) {
            stack<char> st;
    
            for (char ch : s) {
    
                if (ch == '(' || ch == '{' || ch == '[') {
                    st.push(ch);
                } else {
                    if (st.empty()) return false;
    
                    if ((ch == ')' && st.top() != '(') ||
                        (ch == '}' && st.top() != '{') ||
                        (ch == ']' && st.top() != '[')) {
                        return false;
                    }
    
                    st.pop();
                }
            }
    
            return st.empty();
        }
    };
    