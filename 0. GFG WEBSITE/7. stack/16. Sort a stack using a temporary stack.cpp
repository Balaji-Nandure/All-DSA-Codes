/*
Problem:
Sort a Stack Using a Temporary Stack

Given a stack of integers, sort the stack in ascending order
(using only stack operations) with the help of a temporary stack.

Rules:
- You can use only one extra stack.
- Only push, pop, top operations are allowed.
- No arrays or other data structures.

Example:
Input stack (top → bottom):
3  1  4  2

Output stack (top → bottom):
1  2  3  4

Approach:
- Use an auxiliary stack temp.
- Pop elements one by one from original stack.
- While temp stack is not empty and its top is greater than current element:
  move elements back to original stack.
- Push current element into temp stack.
- Finally, transfer all elements from temp stack back to original stack.

GeeksforGeeks:
https://www.geeksforgeeks.org/sort-a-stack-using-temporary-stack/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N^2)

Space Complexity:
O(N)
*/

class Solution {
public:
    void sortStack(stack<int>& st) {

        stack<int> temp;

        while (!st.empty()) {

            int curr = st.top();
            st.pop();

            while (!temp.empty() && temp.top() > curr) {
                st.push(temp.top());
                temp.pop();
            }

            temp.push(curr);
        }

        while (!temp.empty()) {
            st.push(temp.top());
            temp.pop();
        }
    }
};
    