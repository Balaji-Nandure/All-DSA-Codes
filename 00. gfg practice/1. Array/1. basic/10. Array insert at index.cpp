/*
Problem: Array insert at index

You are given an array arr (0-based index) and two positive integers: index and val.
You need to insert val at the given index.

Examples:

Input: arr[] = [1, 2, 3, 4, 5], index = 5, val = 90
Output: 1 2 3 4 5 90

Input: arr[] = [1, 2, 3, 4, 5], index = 2, val = 90
Output: 1 2 90 3 4 5

Constraints:
  1 ≤ arr.size() ≤ 10^5
  0 ≤ element, arr[i] ≤ 10^6
  0 ≤ index ≤ arr.size()
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    void insertAtIndex(vector<int> &arr, int index, int val) {
        int n = arr.size();
        arr.push_back(0);
        for (int i = n; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = val;
    }
};
