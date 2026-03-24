/*
Problem: Majority Element (> n/2 times)

GFG: https://www.geeksforgeeks.org/problems/majority-element-1587115620/1

Description: Given an array arr[]. Find the majority element in the array. If no majority element exists, return -1.

Note: A majority element in an array is an element that appears strictly more than arr.size()/2 times in the array.

Examples:

Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
Output: 1
Explanation: Since, 1 is present more than 7/2 times, so it is the majority element.
Input: arr[] = [7]
Output: 7
Explanation: Since, 7 is single element and present more than 1/2 times, so it is the majority element.
Input: arr[] = [2, 13]
Output: -1
Explanation: Since, no element is present more than 2/2 times, so there is no majority element.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i] ≤ 105

Approach:
Moore's Voting Algorithm (Optimal):
Step 1: Find candidate using voting
Step 2: Verify candidate by counting

Why it works:
Majority element count > n/2
So it cannot be fully cancelled by other elements.
The voting process ensures majority element survives.

Algorithm:
1. Initialize candidate = -1, count = 0
2. For each element:
   - If count == 0: candidate = element, count = 1
   - If element == candidate: count++
   - Else: count--
3. Verify candidate by counting its occurrences
4. Return candidate if count > n/2, else -1

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& arr) {
        int candidate = -1;
        int count = 0;

        // Step 1: Find candidate
        for (int num : arr) {
            if (count == 0) {
                candidate = num;
                count = 1;
            }
            else if (num == candidate) {
                count++;
            }
            else {
                count--;
            }
        }

        // Step 2: Verify candidate
        count = 0;
        for (int num : arr) {
            if (num == candidate)
                count++;
        }

        if (count > arr.size() / 2)
            return candidate;
        else
            return -1;
    }
};
