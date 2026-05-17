/*
Problem: Check if divisible by 11

GFG: https://www.geeksforgeeks.org/problems/check-if-divisible-by-11/1

Description:
Given a very large number as string S, return 1 if it is divisible by 11,
otherwise return 0.

Examples:

Input: S = "76945"
Output: 1

Input: S = "12"
Output: 0

Constraints:
1 <= S <= 10^1000+5

Approach (Divisibility Rule of 11):
A number is divisible by 11 if the absolute difference between:
- sum of digits at odd positions and
- sum of digits at even positions
is divisible by 11.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int divisibleBy11(string S) {

        int oddSum = 0;
        int evenSum = 0;

        for(int i = 0; i < (int)S.size(); i++) {
            int digit = S[i] - '0';

            if(i % 2 == 0) {
                oddSum += digit;
            } else {
                evenSum += digit;
            }
        }

        int diff = abs(oddSum - evenSum);
        return (diff % 11 == 0) ? 1 : 0;
    }
};
