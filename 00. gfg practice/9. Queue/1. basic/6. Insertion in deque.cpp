/*
Problem: Insertion in Deque

GFG: https://www.geeksforgeeks.org/problems/insertion-in-deque/1

Description:
Given an array arr[] containing non-negative integers, insert all elements
into a deque and return it.

Examples:
Input: arr[] = [1, 2, 3, 4, 5]
Output: [1, 2, 3, 4, 5]

Input: arr[] = [1]
Output: [1]

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5

Approach:
Iterate through the array and push each element to the back of the deque
using push_back().

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    deque<int> dqInsertion(vector<int>& arr) {
        deque<int> dq;
        for (int i = 0; i < arr.size(); i++) {
            dq.push_back(arr[i]);
        }
        return dq;
    }
};
