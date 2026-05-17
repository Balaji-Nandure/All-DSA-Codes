/*
Problem: Floating point number even or odd

GFG: https://www.geeksforgeeks.org/problems/floating-point-number-even-or-odd/1

Description:
Given a floating point number as string s, determine whether it is even or odd.
Trailing zeros after decimal point do not matter.

Examples:

Input: s = "97.8"
Output: EVEN

Input: s = "100.70"
Output: ODD

Approach:
Scan from right to left:
1. Ignore trailing '0'
2. Ignore decimal point '.'
3. First remaining digit decides parity

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Returns true for EVEN, false for ODD
    bool isEven(string s, int n) {

        for(int i = n - 1; i >= 0; i--) {

            if(s[i] == '.') {
                continue;
            }

            if(s[i] == '0') {
                continue;
            }

            int digit = s[i] - '0';
            return (digit % 2 == 0);
        }

        // For cases like "0.0" -> even
        return true;
    }
};
