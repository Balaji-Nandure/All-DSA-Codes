/*
GeeksforGeeks: Valid Substring
Difficulty: Medium

Problem:
Given a string s consisting only of opening and closing parentheses '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Examples:
Input: s = "(()("
Output: 2
Explanation: The longest valid substring is "()". Its length is 2.

Input: s = "()(())("
Output: 6
Explanation: The longest valid substring is "()(())". Its length is 6.

Input: s = "(()())"
Output: 6
Explanation: The longest valid substring is "(()())". Its length is 6.

Constraints:
1 <= s.size() <= 10^5
s[i] is either '(' or ')'.

Core Idea:
Use a stack to track indices of unmatched characters.
- Push -1 onto the stack initially as a base index (acts as a boundary before any valid substring).
- For each character at index `i`:
  - If it is '(', push its index `i` onto the stack.
  - If it is ')':
    - Pop the top element (trying to match a '(').
    - If the stack is now empty, push the current index `i` as the new base boundary.
    - If the stack is not empty, the current valid substring length is `i - stack.top()`.
      Update `maxLen` accordingly.
- This way, `stack.top()` always holds the index of the last unmatched character.

Approach:
1. Initialize `stack<int>` and push `-1` as base.
2. Initialize `maxLen = 0`.
3. Loop `i` from 0 to n - 1:
   - If `s[i] == '('`: push `i`.
   - Else (')'): pop the top.
     - If stack is empty: push `i` as the new base.
     - Else: `maxLen = max(maxLen, i - stack.top())`.
4. Return `maxLen`.

Time Complexity: O(N) — single pass through the string.
Space Complexity: O(N) — for the stack, which can hold at most N indices.

GFG Link: https://www.geeksforgeeks.org/problems/valid-substring0624/1
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxLen(string s) {
        stack<int> st;
        st.push(-1); // Base boundary index
        int maxLen = 0;
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                // Try to match this ')' with the top '('
                st.pop();
                
                if (st.empty()) {
                    // No matching '(' found; this ')' becomes the new base boundary
                    st.push(i);
                } else {
                    // Current valid substring stretches from just after stack.top() to i
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }
        
        return maxLen;
    }
};

/*
Dry Run — Example:
s = "()(())("

Initial: stack = [-1], maxLen = 0

- i = 0, '(': push 0       -> stack = [-1, 0]
- i = 1, ')': pop 0        -> stack = [-1], not empty -> maxLen = max(0, 1 - (-1)) = 2
- i = 2, '(': push 2       -> stack = [-1, 2]
- i = 3, '(': push 3       -> stack = [-1, 2, 3]
- i = 4, ')': pop 3        -> stack = [-1, 2], not empty -> maxLen = max(2, 4 - 2) = 2
- i = 5, ')': pop 2        -> stack = [-1], not empty -> maxLen = max(2, 5 - (-1)) = 6
- i = 6, '(': push 6       -> stack = [-1, 6]

Output: 6
*/
