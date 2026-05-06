/*
Problem: K Sized Subarray Maximum

GFG: https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1

Description:
Given an array arr[] of positive integers and an integer k. You have to find the maximum value for each contiguous subarray of size k. Return an array of maximum values corresponding to each contiguous subarray.

Examples:

Input: arr[] = [1, 2, 3, 1, 4, 5, 2, 3, 6], k = 3
Output: [3, 3, 4, 5, 5, 5, 6]
Explanation: 
1st contiguous subarray [1, 2, 3], max = 3
2nd contiguous subarray [2, 3, 1], max = 3
3rd contiguous subarray [3, 1, 4], max = 4
4th contiguous subarray [1, 4, 5], max = 5
5th contiguous subarray [4, 5, 2], max = 5
6th contiguous subarray [5, 2, 3], max = 5
7th contiguous subarray [2, 3, 6], max = 6

Input: arr[] = [5, 1, 3, 4, 2], k = 1
Output: [5, 1, 3, 4, 2]
Explanation: When k = 1, each element in the array is its own subarray, so output is simply the same array.

Constraints:
1 ≤ arr.size() ≤ 10^6
1 ≤ k ≤ arr.size()
0 ≤ arr[i] ≤ 10^9

Approach (Monotonic Deque):
Use sliding window with monotonic deque to find maximum in each window efficiently.

For every index i:
1. Remove indices outside window: dq.front() <= i-k
2. Remove smaller elements from back: arr[dq.back()] <= arr[i]
3. Insert current index: dq.push_back(i)
4. If window formed (i >= k-1): ans.push_back(arr[dq.front()])

Why it works:
- Deque maintains decreasing order of values
- Front always contains maximum of current window
- Each element inserted and removed once → O(n) total

Time Complexity: O(n)
Space Complexity: O(k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        deque<int> dq;   // stores indices
        
        vector<int> ans;
        
        for (int i = 0; i < n; i++) {
            
            // Remove out-of-window indices
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove smaller elements
            while (!dq.empty() && arr[dq.back()] <= arr[i]) {
                dq.pop_back();
            }
            
            // Insert current index
            dq.push_back(i);
            
            // Window formed
            if (i >= k - 1) {
                ans.push_back(arr[dq.front()]);
            }
        }
        
        return ans;
    }
};
