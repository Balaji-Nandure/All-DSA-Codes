/*
Problem: Triplet Sum in Array

GFG: https://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/

Description: Given an array arr[] and an integer target, determine if there exists a triplet in the array whose sum equals the given target.

Return true if such a triplet exists, otherwise, return false.

Examples:

Input: arr[] = [1, 4, 45, 6, 10, 8], target = 13
Output: true 
Explanation: The triplet {1, 4, 8} sums up to 13.
Input: arr[] = [1, 2, 4, 3, 6, 7], target = 10
Output: true 
Explanation: The triplets {1, 3, 6} and {1, 2, 7} both sum to 10.
Input: arr[] = [40, 20, 10, 3, 6, 7], target = 24
Output: false 
Explanation: No triplet in the array sums to 24.

Constraints:
3 ≤ arr.size() ≤ 5*103
0 ≤ arr[i], target ≤ 105

Striver Intuition:

This is a classic 3-Sum problem.

Brute Force:
- Try all triplets using 3 loops.
- TC = O(n^3)

Better (Hashing):
- Fix one element.
- Use HashSet for 2-sum on remaining array.
- TC = O(n^2), SC = O(n)

Optimal (Striver Approach):
- Sort the array.
- Fix one element (i).
- Use two pointers (j = i+1, k = n-1).
- If sum == target → found
- If sum < target → j++
- If sum > target → k--

Why sorting?
Because two-pointer works only on sorted arrays.

Pattern:
3 Sum → Sort + Two Pointer

Time Complexity: O(n^2)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasTripletSum(vector<int>& arr, int target) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                if (sum == target) {
                    return true;
                }
                else if (sum < target) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }

        return false;
    }
};

/*
Final Summary (Interview Revision):

1. 3 Sum problem → Sort + Two Pointer.
2. Fix first element, then solve 2-sum using two pointers.
3. If sum < target → move left pointer.
4. If sum > target → move right pointer.
5. Time = O(n^2), Space = O(1).

Memory Trick:
3 Sum → Fix one + Two Pointer
*/
