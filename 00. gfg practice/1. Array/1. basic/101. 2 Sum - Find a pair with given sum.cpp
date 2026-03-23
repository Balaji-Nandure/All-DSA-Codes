/*
Problem: 2 Sum - Find a pair with given sum

GFG: https://www.geeksforgeeks.org/problems/2-sum-find-a-pair-with-given-sum/1

Description: Given an array arr[] and an integer target. You have to return pair of elements which sum upto target. You cannot use the same element twice.
Note: Inputs are given such that only one valid answer exists.

Examples:

Input: arr[] = [2, 9, 10, 4, 15], target = 12
Output: [2, 10]
Explanation: Pair with sum equal to 12 is (2, 10).
Input: arr[] = [3, 2, 4], target = 8
Output: []
Explanation: No pair exists with sum equal to 8.
Input: arr[] = [1, 4, 5, 6, 1], target = 2
Output: [1, 1]
Explanation: Pair with sum equal to 2 is (1, 1).

Constraints:
1 <= arr.size() <= 105
0 <= arr[i] <= 104
1 <= target <= 104

Approach:
Return pair whose sum = target.
Only one valid answer exists.
Cannot use same element twice.

Optimal Approach:
Use HashSet.
For each element x:
    check if (target - x) exists
    if yes -> return pair
    else insert x

Why it works:
- HashSet provides O(1) lookup for complement
- Single pass through array ensures O(n) time
- We insert after checking to avoid using same element twice

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& arr, int target) {
        unordered_set<int> st;

        for (int x : arr) {
            int need = target - x;

            if (st.count(need)) {
                return {need, x};
            }

            st.insert(x);
        }

        return {};
    }
};
