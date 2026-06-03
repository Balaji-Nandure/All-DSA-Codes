/*
Problem: Height of Heap

GFG: https://www.geeksforgeeks.org/problems/height-of-heap5025/1

Description:
Given an array representation of a binary heap of size n, return height
of the heap.

Note:
- If n = 1, height = 1 (as per problem statement).
- For complete binary heap, height in edges = floor(log2(n)).

Examples:
Input: n = 6
Output: 2

Input: n = 9
Output: 3

Constraints:
1 <= n <= 10^4
1 <= arr[i] <= 10^6

Approach:
Heap stored in array is a complete binary tree.
So height can be computed directly from n:

height = floor(log2(n))

Time Complexity: O(1)
Space Complexity: O(1)

Pattern: Heap Property / Math
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int heapHeight(int n, int arr[]) {
        if (n == 1) {
            return 1;
        }
        return (int)log2(n);
    }
};
