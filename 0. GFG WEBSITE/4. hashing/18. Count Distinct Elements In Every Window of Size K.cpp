/*
Problem:
Count Distinct Elements in Every Window of Size K

Given an integer array arr[] of size n and an integer k,
find the count of distinct elements in every contiguous
subarray (window) of size k.

Examples:
Input  : arr = [1, 2, 1, 3, 4, 2, 3], k = 4
Output : [3, 4, 4, 3]
Explanation:
Window [1, 2, 1, 3] → {1,2,3} → 3
Window [2, 1, 3, 4] → {1,2,3,4} → 4
Window [1, 3, 4, 2] → {1,2,3,4} → 4
Window [3, 4, 2, 3] → {2,3,4} → 3

Input  : arr = [1, 1, 1, 1], k = 2
Output : [1, 1, 1]

Input  : arr = [1, 2, 3, 4], k = 3
Output : [3, 3]


Approach (Expected / Optimal – Sliding Window + Hashing):
1. Use an unordered_map to store frequency of elements in the current window.
2. First, process the first window of size k:
   - Insert elements into the map and record distinct count.
3. Slide the window from left to right:
   - Remove the element going out of the window:
       decrement its frequency;
       if frequency becomes 0, erase it from the map.
   - Add the new element entering the window and update frequency.
   - Store current map size as distinct count.
4. Continue until all windows are processed.

Why this works:
- Sliding window ensures each element is added and removed once.
- Hash map maintains accurate frequency and distinct count.
- Map size directly represents number of distinct elements.

Time Complexity:
O(n)

Space Complexity:
O(k)


GeeksforGeeks:
https://www.geeksforgeeks.org/count-distinct-elements-in-every-window-of-size-k/

LeetCode:
https://leetcode.com/problems/distinct-numbers-in-each-subarray/
(Related problem with same logic)
*/

vector<int> countDistinctInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result;

    if (k > n) return result;

    unordered_map<int, int> freq;

    // Step 1: First window
    for (int i = 0; i < k; i++) {
        freq[arr[i]]++;
    }
    result.push_back(freq.size());

    // Step 2: Slide the window
    for (int i = k; i < n; i++) {
        // Remove element going out
        freq[arr[i - k]]--;
        if (freq[arr[i - k]] == 0) {
            freq.erase(arr[i - k]);
        }

        // Add element coming in
        freq[arr[i]]++;

        result.push_back(freq.size());
    }

    return result;
}
