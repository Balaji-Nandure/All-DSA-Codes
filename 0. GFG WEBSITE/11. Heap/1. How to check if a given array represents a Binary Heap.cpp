/*
Problem:
Check if a Given Array Represents a Binary Heap

Given an array arr[] of size N, check whether it represents
a Binary Heap (Max Heap).

Rules for Max Heap:
1) It must be a Complete Binary Tree.
2) Every parent node must be greater than or equal to its children.

Array Representation Insight:
- In array form, a binary heap is always complete by definition.
- So we ONLY need to check the heap property.

Index relations:
- Left child  = 2*i + 1
- Right child = 2*i + 2

Approach (Optimal – Single Pass):
- Traverse all non-leaf nodes (i from 0 to (N/2 - 1)).
- For each node:
  - If left child exists and arr[i] < arr[left], return false.
  - If right child exists and arr[i] < arr[right], return false.
- If all nodes satisfy the condition, it is a heap.

Example:
Input:
arr = [90, 15, 10, 7, 12, 2]

Output:
true

GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-a-given-array-represents-a-binary-heap/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(1)
*/

class Solution {
public:
    bool isHeap(vector<int>& arr) {

        int n = arr.size();

        // Only need to check non-leaf nodes
        for (int i = 0; i <= (n - 2) / 2; i++) {

            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && arr[i] < arr[left])
                return false;

            if (right < n && arr[i] < arr[right])
                return false;
        }

        return true;
    }
};
