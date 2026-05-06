/*
Problem: Previous Smaller Element

GFG: https://www.geeksforgeeks.org/problems/previous-smaller-element/1

Description:
You are given an integer array arr[ ]. For every element in the array, your task is to determine its Previous Smaller Element (PSE).

The Previous Smaller Element (PSE) of an element x is the first element that appears to the left of x in the array and is strictly smaller than x.

Note: If no such element exists, assign -1 as the PSE for that position.

Examples:

Input: arr[] = [1, 6, 2]
Output: [-1, 1, 1]
Explanation:
For 1, there is no element on the left, so answer is -1.
For 6, previous smaller element is 1.
For 2, previous smaller element is 1.

Input: arr[] = [1, 5, 0, 3, 4, 5]
Output: [-1, 1, -1, 0, 3, 4]
Explanation:
For 1, no element on the left, so answer is -1.
For 5, previous smaller element is 1.
For 0, no element on the left smaller than 0, so answer is -1.
For 3, previous smaller element is 0.
For 4, previous smaller element is 3.
For 5, previous smaller element is 4.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5

Approach (Stack):
1. Use a stack to keep track of elements in increasing order
2. For each element arr[i]:
   - While stack is not empty and stack.top() >= arr[i], pop from stack
   - If stack is empty, PSE is -1
   - Else, PSE is stack.top()
   - Push arr[i] onto stack
3. Store results in answer array

Why it works:
- Stack maintains elements in strictly increasing order from bottom to top
- When we encounter arr[i], all elements >= arr[i] cannot be PSE for future elements
- The remaining top element (if any) is the closest smaller element to the left
- This gives us the first smaller element to the left for each position

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> prevSmaller(vector<int>& arr) {
        int n = arr.size();
        vector<int> result(n);
        stack<int> st;
        
        for (int i = 0; i < n; i++) {
            // Remove elements that are >= current element
            while (!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }
            
            // If stack is empty, no previous smaller element
            if (st.empty()) {
                result[i] = -1;
            } else {
                // Stack top is the previous smaller element
                result[i] = st.top();
            }
            
            // Push current element onto stack
            st.push(arr[i]);
        }
        
        return result;
    }
};
