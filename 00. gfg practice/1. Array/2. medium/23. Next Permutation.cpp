/*
Problem: Next Permutation

GFG: https://www.geeksforgeeks.org/problems/next-permutation5226/1

Description: Given an array of integers arr[] representing a permutation, implement a next permutation that rearranges the numbers into the lexicographically next greater permutation. If no such permutation exists, rearrange the numbers into the lowest possible order (i.e., sorted in ascending order).

Note: A permutation of an array of integers refers to a specific arrangement of its elements in a sequence or linear order.

Examples:

Input: arr[] = [2, 4, 1, 7, 5, 0]
Output: [2, 4, 5, 0, 1, 7]
Explanation: The next permutation of the given array is [2, 4, 5, 0, 1, 7].
Input: arr[] = [3, 2, 1]
Output: [1, 2, 3]
Explanation: As arr[] is the last permutation, the next permutation is the lowest one.
Input: arr[] = [3, 4, 2, 5, 1]
Output: [3, 4, 5, 1, 2]
Explanation: The next permutation of the given array is [3, 4, 5, 1, 2].

Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ arr[i] ≤ 105

Striver Intuition:

We need to find the next lexicographically greater permutation.

Key insight: Find the first position from right where arr[i] < arr[i+1].
This is called the "breakpoint".

Algorithm:
1. Find breakpoint: Traverse from right and find first i where arr[i] < arr[i+1].
2. If no breakpoint → array is in descending order → reverse entire array.
3. If breakpoint exists:
   - Find the smallest element greater than arr[i] on right side.
   - Swap them.
   - Reverse the right part to get smallest order.

Why this works:
Right side of breakpoint is always in descending order.
To get next permutation, we increase the number slightly and then
make the remaining part smallest by reversing.

Pattern:
Permutation Manipulation → Breakpoint + Swap + Reverse

Time Complexity: O(n)
Space Complexity: O(1)

GFG:
https://www.geeksforgeeks.org/problems/next-permutation5226/1

LeetCode:
https://leetcode.com/problems/next-permutation/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& arr) {
        int n = arr.size();
        int indx = -1;

        for(int i = n - 2; i >= 0; i--){
            if(arr[i] < arr[i + 1]){
                indx = i;
                break;
            }
        }

        if(indx != -1){
            for(int i = n - 1; i > indx; i--){
                if(arr[i] > arr[indx]){
                    swap(arr[i], arr[indx]);
                    break;
                }
            }
        }

        reverse(arr.begin() + indx + 1, arr.end());
    }
};

/*
Final Summary (Interview Revision):

1. Find breakpoint from right where arr[i] < arr[i+1].
2. If no breakpoint → reverse entire array (smallest permutation).
3. If breakpoint exists:
   - Find smallest element > arr[breakpoint] on right side.
   - Swap them.
   - Reverse right part.
4. Time = O(n), Space = O(1).

Memory Trick:
"Breakpoint → Swap → Reverse"
*/
