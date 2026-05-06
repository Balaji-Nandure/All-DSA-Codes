/*
Problem: Nearly Sorted Array

GFG: https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1

Description:
Given an array arr[], where each element is at most k positions away from its correct position in the sorted order.
Your task is to restore the sorted order of arr[] by rearranging the elements in place.

Note: Don't use any sort() method.

Examples:

Input: arr[] = [2, 3, 1, 4], k = 2
Output: [1, 2, 3, 4]
Explanation: All elements are at most k = 2 positions away from their correct positions.
Element 1 moves from index 2 to 0
Element 2 moves from index 0 to 1
Element 3 moves from index 1 to 2
Element 4 stays at index 3

Input: arr[]= [7, 9, 14], k = 1
Output: [7, 9, 14]
Explanation: All elements are already stored in the sorted order.

Constraints:
1 ≤ arr.size() ≤ 10^6
0 ≤ k < arr.size()
1 ≤ arr[i] ≤ 10^6

Approach (Min Heap):
1. Create a min heap
2. Push first (k+1) elements into heap
3. For remaining elements:
   - Pop smallest → put in array
   - Push new element
4. After loop → pop remaining heap elements

Why it works:
- Correct element for index i lies within next k+1 elements
- Heap gives smallest in O(log k)
- Since each element is at most k positions away, the smallest element for position i must be within the window [i, i+k]
- Maintaining a heap of size k+1 ensures we always have access to the correct element for current position

Time Complexity:
- O(n log k)

Space Complexity:
- O(k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void nearlySorted(vector<int>& arr, int k) {
        int n = arr.size();
        
        // Min heap
        priority_queue<int, vector<int>, greater<int>> pq;
        
        int i = 0;
        
        // Step 1: push first k+1 elements
        for (; i < min(n, k + 1); i++) {
            pq.push(arr[i]);
        }
        
        int index = 0;
        
        // Step 2: process remaining elements
        while (i < n) {
            arr[index++] = pq.top();
            pq.pop();
            
            pq.push(arr[i]);
            i++;
        }
        
        // Step 3: empty remaining heap
        while (!pq.empty()) {
            arr[index++] = pq.top();
            pq.pop();
        }
    }
};
