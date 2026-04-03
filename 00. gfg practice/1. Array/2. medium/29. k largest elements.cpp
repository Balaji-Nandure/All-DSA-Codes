/*
Problem: k largest elements

GFG: https://www.geeksforgeeks.org/problems/k-largest-elements4206/1

Description: Given an array arr[] of positive integers and an integer k, return the k largest values in
decreasing order (largest first).

Examples:

Input: arr[] = [12, 5, 787, 1, 23], k = 2
Output: [787, 23]

Input: arr[] = [1, 23, 12, 9, 30, 2, 50], k = 3
Output: [50, 30, 23]

Input: arr[] = [12, 23], k = 1
Output: [23]

Constraints:
1 ≤ k ≤ arr.size() ≤ 10^6
1 ≤ arr[i] ≤ 10^6

Striver Intuition:

This is a classic Top-K / Heap problem (or sorting / quickselect variants).

Brute Force:
Sort the entire array in descending order, take first k elements.
Time = O(n log n), Space = O(1) extra if sorting in place (often avoid mutating input — copy first).

Better — Min-Heap of size k:
Idea: Keep a min-heap holding the k largest values seen so far. The root is the smallest among those k.
For each x: if heap has fewer than k elements, push x; else if x is larger than the root, pop root and push x.
After one pass, the heap contains the k largest. Pop all into a vector — they come out ascending; reverse to get decreasing order.

Why min-heap (not max-heap)?
We want to evict the smallest among the current “top k” when a better candidate arrives — that smallest is at the root of a min-heap.

Alternative: Max-heap of all n elements, pop k times → O(n + k log n) time, O(n) space for heap.

Pattern:
Top-K largest → min-heap of size k (or sort / quickselect depending on constraints).

Time Complexity: O(n log k) with min-heap; O(n log n) with full sort
Space Complexity: O(k) for the heap approach

GFG:
https://www.geeksforgeeks.org/problems/k-largest-elements4206/1

Related:
https://leetcode.com/problems/kth-largest-element-in-an-array/  (find one kth largest, not all k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> kLargest(vector<int>& arr, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int x : arr) {
            if ((int)pq.size() < k) {
                pq.push(x);
            } else if (x > pq.top()) {
                pq.pop();
                pq.push(x);
            }
        }

        vector<int> ans;
        ans.reserve(k);
        while (!pq.empty()) {
            ans.push_back(pq.top());
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. Min-heap size k tracks the k largest; root = smallest among them.
2. If x beats that smallest, replace it.
3. Pop order is ascending → reverse for decreasing output.
4. If k ≈ n, sorting can be simpler; if k ≪ n, heap wins.

Memory Trick:
"k largest → min-heap of k → reverse pops"
*/
