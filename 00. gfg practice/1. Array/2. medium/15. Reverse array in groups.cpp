/*
Problem: Reverse Array in Groups

GFG: https://www.geeksforgeeks.org/reverse-an-array-in-groups-of-given-size/

Description: Given an array arr[] of positive integers. Reverse every sub-array group of size k.
Note: If at any instance, k is greater or equal to the array size, then reverse the entire array.

Examples:

Input: arr[] = [1, 2, 3, 4, 5], k = 3
Output: [3, 2, 1, 5, 4]
Explanation: First group consists of elements 1, 2, 3. Second group consists of 4, 5.
Input: arr[] = [5, 6, 8, 9], k = 5
Output: [9, 8, 6, 5]
Explanation: Since k is greater than array size, entire array is reversed.
Input: arr[] = [1, 2, 3, 4, 5, 6], k = 4
Output: [4, 3, 2, 1, 6, 5]
Explanation: First group [1,2,3,4] reversed to [4,3,2,1], second group [5,6] reversed to [6,5].

Constraints:
1 ≤ arr.size(), k ≤ 105
1 ≤ arr[i] ≤ 105

Striver Intuition:

This is a simple simulation problem.

We just need to reverse the array in chunks of size k.

For example:
arr = [1 2 3 4 5 6 7 8], k = 3

We reverse:
[1 2 3] → [3 2 1]
[4 5 6] → [6 5 4]
[7 8]   → [8 7]

So we move in steps of k and reverse each block.

Pattern:
Array + Reverse in fixed size window → Two Pointer / Simulation

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverseArray(vector<int> &arr, int start, int end) {
        while (start < end) {
            swap(arr[start], arr[end]);
            start++;
            end--;
        }
    }

    vector<int> reverseInGroups(vector<int> &arr, int k) {
        int n = arr.size();

        // Traverse array in steps of k
        for (int i = 0; i < n; i += k) {
            int start = i;
            int end = min(i + k - 1, n - 1);
            reverseArray(arr, start, end);
        }

        return arr;
    }
};

/*
Final Summary (Interview Revision):

1. Move in steps of k.
2. Reverse from i to min(i+k-1, n-1).
3. Use two-pointer reverse.
4. If k >= n → whole array reversed automatically.
5. Pattern = Fixed Window + Reverse

Memory Trick:
"Group banao → Reverse karo → aage badho"
*/
