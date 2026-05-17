/*
Problem: Perfect Square String

GFG: https://www.geeksforgeeks.org/problems/perfect-square-string/1

Description:
Given a string S, compute the sum of ASCII values of all characters.
Return 1 if this sum is a perfect square, otherwise return 0.

Examples:

Input: S = "d"
Output: 1

Input: S = "1Qy"
Output: 0

Constraints:
1 <= |S| <= 10^5

Approach:
1. Sum ASCII values of all characters.
2. Compute integer square root of sum.
3. If root * root == sum, return 1 else 0.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int isSquare(string S) {

        long long asciiSum = 0;

        for(char ch : S) {
            asciiSum += (unsigned char)ch;
        }

        long long root = (long long)sqrt((long double)asciiSum);
        return (root * root == asciiSum) ? 1 : 0;
    }
};
