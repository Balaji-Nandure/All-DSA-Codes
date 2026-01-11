/*
Problem:
Reverse a Stack Using Recursion

Given a stack of integers, reverse the stack using recursion.
You are NOT allowed to use any extra data structure
(other than the implicit recursion stack).

Rules:
- Only recursion is allowed.
- No loops.
- No additional stack or array.

Example:
Input stack (top → bottom):
3  2  1

Output stack (top → bottom):
1  2  3

Approach:
- Remove the top element recursively until stack is empty.
- Insert each removed element at the bottom of the stack
  using a helper recursive function.

Why this works:
- Recursion empties the stack completely.
- Insert-at-bottom rebuilds the stack in reverse order.

GeeksforGeeks:
https://www.geeksforgeeks.org/reverse-a-stack-using-recursion/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N^2)

Space Complexity:
O(N)
*/

class Solution {
    public:
        void insertAtBottom(stack<int>& st, int x) {
            if (st.empty()) {
                st.push(x);
                return;
            }
    
            int temp = st.top();
            st.pop();
            insertAtBottom(st, x);
            st.push(temp);
        }
    
        void reverse(stack<int>& st) {
            if (st.empty()) return;
    
            int temp = st.top();
            st.pop();
            reverse(st);
            insertAtBottom(st, temp);
        }
    };
    