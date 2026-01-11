/*
Problem:
Next Greater Element in Array

Given an array of integers, for each element find the
next element to its right that is greater than it.
If no such element exists, output -1 for that position.

Rules:
- Traverse from right to left.
- Next element must be strictly greater.

Example:
Input:
arr = [1, 3, 2, 4]

Output:
[3, 4, 4, -1]

Approach:
- Use a monotonic decreasing stack.
- Traverse the array from right to left.
- For each element:
  - Pop elements from stack while they are <= current element.
  - Top of stack (if exists) is the next greater element.
- Push current element into stack.

GeeksforGeeks:
https://www.geeksforgeeks.org/next-greater-element/

LeetCode:
https://leetcode.com/problems/next-greater-element-i/

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& arr) {

        int n = arr.size();
        vector<int> ans(n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {

            while (!st.empty() && st.top() <= arr[i]) {
                st.pop();
            }

            if (st.empty()) ans[i] = -1;
            else ans[i] = st.top();

            st.push(arr[i]);
        }

        return ans;
    }
};
    