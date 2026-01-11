/*
Problem:
Previous Smaller Element

Given an array of integers, for each element find the
previous element to its left that is smaller than it.
If no such element exists, output -1 for that position.

Rules:
- Traverse from left to right.
- Previous element must be strictly smaller.

Example:
Input:
arr = [4, 5, 2, 10, 8]

Output:
[-1, 4, -1, 2, 2]

Approach:
- Use a monotonic increasing stack.
- Traverse the array from left to right.
- For each element:
  - Pop elements from stack while they are >= current element.
  - Top of stack (if exists) is the previous smaller element.
- Push current element into stack.

GeeksforGeeks:
https://www.geeksforgeeks.org/previous-smaller-element/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
    public:
        vector<int> previousSmallerElement(vector<int>& arr) {
    
            stack<int> st;
            vector<int> ans;
    
            for (int x : arr) {

                while (!st.empty() && st.top() >= x) {
                    st.pop();
                }
    
                if (st.empty()) ans.push_back(-1);
                else ans.push_back(st.top());
    
                st.push(x);
            }
    
            return ans;
        }
    };
    