/*
Problem: Stack designer

GFG: https://www.geeksforgeeks.org/problems/stack-designer/1

Description:
Given an array arr[], push all elements into a stack and then return/print
elements while popping from stack (LIFO order).

Examples:
arr = [1, 2, 3, 4, 5] -> 5 4 3 2 1
arr = [1, 6, 43, 1, 2, 0, 5] -> 5 0 2 1 43 6 1

Constraints:
1 <= arr[i] <= 10^7

Approach:
1) Push all array elements into stack.
2) Pop until empty and store in answer.

Time Complexity: O(N)
Space Complexity: O(N)

Pattern: Stack Simulation (LIFO)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> reverseArrayUsingStack(vector<int>& arr) {
        stack<int> st;
        vector<int> ans;
        ans.reserve(arr.size());

        for (int x : arr) {
            st.push(x);
        }

        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};

