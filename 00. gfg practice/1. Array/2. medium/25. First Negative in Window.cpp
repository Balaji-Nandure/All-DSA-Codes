/*
Problem: First Negative Integer in Every Window of Size K

GFG: https://www.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1

Description: Given an array arr[] and a positive integer k, find the first negative integer for each and every window(contiguous subarray) of size k.
Note: If a window does not contain a negative integer, then return 0 for that window.

Examples:

Input: arr[] = [-8, 2, 3, -6, 10], k = 2
Output: [-8, 0, -6, -6]
Explanation: 
Window [-8, 2] First negative integer is -8.
Window [2, 3] No negative integers, output is 0.
Window [3, -6] First negative integer is -6.
Window [-6, 10] First negative integer is -6.

Input: arr[] = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
Output: [-1, -1, -7, -15, -15, 0]
Explanation: 
Window [12, -1, -7] First negative integer is -1.
Window [-1, -7, 8] First negative integer is -1.
Window [-7, 8, -15] First negative integer is -7.
Window [8, -15, 30] First negative integer is -15.
Window [-15, 30, 16] First negative integer is -15.
Window [30, 16, 28] No negative integers, output is 0.

Input: arr[] = [12, 1, 3, 5], k = 3
Output: [0, 0]
Explanation: 
Window [12, 1, 3] No negative integers, output is 0.
Window [1, 3, 5] No negative integers, output is 0.

Constraints:
1 ≤ arr.size() ≤ 106
-105 ≤ arr[i] ≤ 105
1 ≤ k ≤ arr.size()

Striver Intuition:

This is a classic Sliding Window problem.

Brute Force:
For each window, iterate through all k elements to find first negative.
Time = O(n * k)

Optimal Approach:
Use Sliding Window + Queue to track negative numbers.

Key insight: We need to maintain the order of negative numbers in current window.
Queue stores indices of negative elements (FIFO order).

Algorithm:
1. Expand window by moving j pointer
2. If arr[j] is negative → add index j to queue
3. When window size reaches k:
   - Remove indices from queue that are out of window (< i)
   - If queue not empty → first negative = arr[q.front()]
   - Else → no negative in window, add 0
   - Slide window by moving i and j

Why Queue?
Queue maintains FIFO order, so front always has the first negative in window.

Pattern:
Sliding Window + Queue for Order Maintenance

Time Complexity: O(n)
Space Complexity: O(k)

GFG:
https://www.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> firstNegInt(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> ans;
        queue<int> q;  // stores indices of negative numbers
        
        for(int i = 0; i < n; i++) {
            // Step 1: Add current element if negative
            if(arr[i] < 0) {
                q.push(i);
            }
            
            // Step 2: Remove elements out of this window
            while(!q.empty() && q.front() <= i - k) {
                q.pop();
            }
            
            // Step 3: Window formed (when i >= k-1)
            if(i >= k - 1) {
                if(!q.empty()) {
                    ans.push_back(arr[q.front()]);
                } else {
                    ans.push_back(0);
                }
            }
        }
        
        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. Use Sliding Window + Queue to track negative numbers.
2. Queue stores indices of negative elements in current window.
3. Expand window: if arr[j] < 0, add j to queue.
4. When window size = k:
   - Remove out-of-window indices from queue front
   - If queue not empty → ans = arr[q.front()]
   - Else → ans = 0
   - Slide window (i++, j++)
5. Time = O(n), Space = O(k)

Memory Trick:
"Sliding Window + Queue → Track Negatives in Order"
*/
