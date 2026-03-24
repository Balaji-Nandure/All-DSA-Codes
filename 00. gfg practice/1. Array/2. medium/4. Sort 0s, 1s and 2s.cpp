/*
Problem: Sort 0s, 1s and 2s (Dutch National Flag Problem)

GFG: https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s-1587115621/1

Description: Given an array arr[] containing only 0s, 1s, and 2s. Sort the array in ascending order.
Note: You need to solve this problem without utilizing the built-in sort function.

Examples:

Input: arr[] = [0, 1, 2, 0, 1, 2]
Output: [0, 0, 1, 1, 2, 2]
Explanation: 0s, 1s and 2s are segregated into ascending order.
Input: arr[] = [0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1]
Output: [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2]
Explanation: 0s, 1s and 2s are segregated into ascending order.

Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ arr[i] ≤ 2

Approach:
Dutch National Flag Algorithm:
- Use 3 pointers: low, mid, high
- Partition array into 3 parts:
  * [0, low-1]: 0s
  * [low, mid]: 1s (being processed)
  * [mid+1, high]: unknown
  * [high+1, n-1]: 2s

Algorithm:
1. Initialize low = 0, mid = 0, high = n-1
2. While mid <= high:
   - If arr[mid] == 0: swap(arr[low], arr[mid]), low++, mid++
   - If arr[mid] == 1: mid++
   - If arr[mid] == 2: swap(arr[mid], arr[high]), high--

Why it works:
- Single pass through array
- Maintains invariant that elements before low are 0, after high are 2
- Processes each element exactly once
- Constant space complexity

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sort012(vector<int>& arr) {
        int low = 0;
        int mid = 0;
        int high = arr.size() - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == 1) {
                mid++;
            }
            else // arr[mid] == 2
            {
                swap(arr[mid], arr[high]);
                high--;
            }
        }
    }
};
