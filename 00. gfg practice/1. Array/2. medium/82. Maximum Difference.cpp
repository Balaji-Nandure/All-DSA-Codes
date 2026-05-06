/*
Problem: Maximum Difference

GFG: https://www.geeksforgeeks.org/problems/maximum-difference-1587115620/1

Description:
Given an integer array arr of integers, the task is to find the maximum absolute difference between the nearest left smaller element and the nearest right smaller element of every element in array arr. If for any component of the arr, the nearest smaller element doesn't exist then consider it as 0.

Examples:

Input: arr = [2, 1, 8]
Output: 1
Explanation: left smaller array ls = [0, 0, 1], right smaller array rs = [1, 0, 0]. Maximum Diff of abs(ls[i] - rs[i]) = 1

Input: arr = [2, 4, 8, 7, 7, 9, 3]
Output: 4
Explanation: left smaller array ls = [0, 2, 4, 4, 4, 7, 2], right smaller rs = [0, 3, 7, 3, 3, 3, 0]. Maximum Diff of abs(ls[i] - rs[i]) = abs(7 - 3) = 4

Constraints:
1 ≤ arr.size() ≤ 10^6
1 ≤ arr[i] ≤ 10^9

Approach (Monotonic Stack):
Step 1: Nearest Smaller Left
Traverse LEFT → RIGHT
Maintain increasing stack
For each element:
- Pop until top < current
- Top = nearest smaller
- If stack empty → 0

Step 2: Nearest Smaller Right
Traverse RIGHT → LEFT
Same logic as left but in reverse

Step 3: Find maximum absolute difference

Why it works:
- Stack maintains candidates for nearest smaller element
- Monotonic increasing stack ensures we find the nearest smaller efficiently
- Two passes give us both left and right smaller elements

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxDiff(vector<int>& arr) {
        
        int n = arr.size();
        
        vector<int> right(n, 0);
        
        stack<int> st;
        
        // Compute nearest smaller right
        for (int i = n - 1; i >= 0; i--) {
            
            while (!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }
            
            if (!st.empty()) {
                right[i] = st.top();
            }
            
            st.push(arr[i]);
        }
        
        while (!st.empty()) st.pop();
        
        int ans = 0;
        
        // Compute left on the fly
        for (int i = 0; i < n; i++) {
            
            while (!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }
            
            int leftSmaller = 0;
            
            if (!st.empty()) {
                leftSmaller = st.top();
            }
            
            st.push(arr[i]);
            
            ans = max(ans, abs(leftSmaller - right[i]));
        }
        
        return ans;
    }
};
