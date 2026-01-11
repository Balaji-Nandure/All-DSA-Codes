/*
Problem:
Sliding Window Maximum (Maximum of all Subarrays of Size K)

Given an array of integers arr[] and an integer K,
find the maximum element in every contiguous subarray of size K.

Rules:
- Windows slide one element at a time.
- Return an array of maximums for each window.

Example:
Input:
arr = [1, 3, -1, -3, 5, 3, 6, 7]
K = 3

Output:
[3, 3, 5, 5, 6, 7]

Approach (Optimized – Deque / Monotonic Queue):
- Use a deque to store indices of useful elements.
- Maintain deque in decreasing order of values.
- Front of deque always stores index of current window maximum.
- For each index i:
  - Remove indices out of current window (i - K).
  - Remove smaller elements from back (they are useless).
  - Push current index.
  - Once window size reaches K, record the maximum.

GeeksforGeeks:
https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/

LeetCode:
https://leetcode.com/problems/sliding-window-maximum/

Time Complexity:
O(N)

Space Complexity:
O(K)
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> ans;   // result to store max of each window
        deque<int> dq;     // will store indices, not values

        for (int i = 0; i < n; i++) {

            // Remove indices of elements not in current window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // Remove indices whose corresponding values are less than arr[i]
            while (!dq.empty() && arr[dq.back()] <= arr[i]) {
                dq.pop_back();
            }

            // Add current index to the deque
            dq.push_back(i);

            // If window has hit size k, append current max to result
            if (i >= k - 1) {
                ans.push_back(arr[dq.front()]);
            }
        }

        return ans;
    }
};
    