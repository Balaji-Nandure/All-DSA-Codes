/*
Problem: Next Smaller Element

GFG: https://www.geeksforgeeks.org/problems/next-smaller-element-1587115620/1
Visualizer (HTML, same folder): 26. Next Smaller Element - visualizer.html

Description: Given an integer array arr[], determine the Next Smaller Element (NSE) for every element.
The NSE of element x is the first element that appears to the right of x and is strictly smaller than x.
If no such element exists, return -1.

Examples:

Input: arr[] = [4, 8, 5, 2, 25]
Output: [2, 5, 2, -1, -1]
Explanation:
For 4: First smaller element on right is 2.
For 8: First smaller element on right is 5.
For 5: First smaller element on right is 2.
For 2: No smaller element on right, so -1.
For 25: No smaller element on right, so -1.

Input: arr[] = [13, 7, 6, 12]
Output: [7, 6, -1, -1]
Explanation:
For 13: First smaller element on right is 7.
For 7: First smaller element on right is 6.
For 6: No smaller element on right, so -1.
For 12: No smaller element on right, so -1.

Input: arr[] = [4, 1]
Output: [1, -1]
Explanation:
For 4: First smaller element on right is 1.
For 1: No smaller element on right, so -1.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5

Striver Intuition:

This is a classic Monotonic Stack problem.

Brute Force:
For each element, traverse to the right and find first smaller element.
Time = O(n^2)

Optimal Approach:
Use Monotonic Stack. Key insight: We need to traverse from RIGHT to LEFT.

Why Right to Left?
Because for each element, we need to find the next smaller element on its right.
By building the stack from right, we ensure we always have candidates on the right.

Algorithm:
1. Traverse array from RIGHT to LEFT (i = n-1 to 0)
2. For current element arr[i]:
   - Pop all elements from stack that are >= arr[i] (they are useless for left elements)
   - If stack is empty → NSE = -1
   - Else → NSE = stack.top()
   - Push arr[i] into stack
3. Return answer array

Why This Works?
- Stack maintains a decreasing order of elements (elements that could be NSE for someone)
- When we pop elements >= arr[i], we remove elements that will never be NSE for left elements
- Top of stack is always the first smaller element on the right
- We maintain O(n) because each element is pushed and popped once

Pattern: Monotonic Increasing Stack (for Next Smaller)

Monotonic Stack Types:
- Next Smaller → Increasing Stack, Right to Left, pop condition: >=
- Next Greater → Decreasing Stack, Right to Left, pop condition: <=
- Previous Smaller → Increasing Stack, Left to Right, pop condition: >=
- Previous Greater → Decreasing Stack, Left to Right, pop condition: <=

Time Complexity: O(n)
Space Complexity: O(n)

GFG:
https://www.geeksforgeeks.org/problems/next-smaller-element-1587115620/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextSmallerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> ans(n);
        stack<int> st;  // stores values of elements (not indices)
        
        // Traverse from RIGHT to LEFT
        for(int i = n - 1; i >= 0; i--) {
            // Step 1: Pop all elements >= current element
            // These elements can never be NSE for anyone on the left
            while(!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }
            
            // Step 2: If stack empty → no smaller element on right
            if(st.empty()) {
                ans[i] = -1;
            } else {
                // Stack.top() is the first smaller element on right
                ans[i] = st.top();
            }
            
            // Step 3: Push current element into stack
            st.push(arr[i]);
        }
        
        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. This is a Monotonic Increasing Stack problem.
2. Traverse from RIGHT to LEFT to find next smaller on right.
3. Pop condition: Remove all elements >= current element.
4. Top of stack after popping is the answer (or -1 if empty).
5. Each element pushed and popped once → O(n) time.

Dry Run Example:
arr = [4, 8, 5, 2, 25]

i=4 (25): Stack empty → ans[4]=-1, push 25 → Stack: [25]
i=3 (2):  Pop 25 (>=2) → Stack empty → ans[3]=-1, push 2 → Stack: [2]
i=2 (5):  5 > 2, no pop → ans[2]=2, push 5 → Stack: [2, 5]
i=1 (8):  Pop 5 (>=8? No) → 8 > 5 → ans[1]=5, push 8 → Stack: [2, 5, 8]
i=0 (4):  Pop 8 (>=4? Yes), pop 5 (>=4? Yes) → Stack: [2] → ans[0]=2, push 4 → Stack: [2, 4]

Output: [2, 5, 2, -1, -1] ✓

Important Pattern Recognition:
- "Next Smaller" → Use Stack, traverse right-to-left, pop >=
- Stack maintains elements in INCREASING order
- Each element enters and exits stack ONCE

Memory Trick:
"Right → Left, Pop >=, Next Smaller" → Monotonic Stack
*/
