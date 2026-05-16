/*
Problem: Find the Number which contain the digit d

GFG: https://www.geeksforgeeks.org/problems/find-the-number-which-contain-the-digit-d/1

Description:
Given n and d, return all numbers in range [0, n] that contain digit d.

Examples:

Input: n = 20, d = 5
Output: 5 15

Input: n = 50, d = 2
Output: 2 12 20 21 22 23 24 25 26 27 28 29 32 42

Constraints:
0 <= n <= 10^3
0 <= d <= 9

Approach:
Check each number from 0 to n. A number matches if any of its decimal digits
equals d.

Time Complexity: O(n * digits)
Space Complexity: O(1) auxiliary (excluding output vector)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool containsDigit(int number, int digit) {

        if(number == 0) {
            return digit == 0;
        }

        while(number > 0) {
            if(number % 10 == digit) {
                return true;
            }
            number /= 10;
        }

        return false;
    }

    vector<int> solve(int n, int d) {

        vector<int> ans;

        for(int value = 0; value <= n; value++) {
            if(containsDigit(value, d)) {
                ans.push_back(value);
            }
        }

        return ans;
    }
};
