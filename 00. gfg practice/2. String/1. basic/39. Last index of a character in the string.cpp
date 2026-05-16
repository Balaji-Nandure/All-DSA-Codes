/*
Problem: Last index of a character in the string

GFG: https://www.geeksforgeeks.org/problems/last-index-of-a-character-in-the-string4516/1

Description:
Given a string S and a character P, return the last index (0-based) of P in S.
If P does not occur in S, return -1.

Examples:

Input: S = "Geeks", P = 'e'
Output: 2

Input: S = "okiyh", P = 'z'
Output: -1

Constraints:
1 <= |S| <= 10^5

Approach (Reverse Scan):
Scan the string from right to left and return the first position where S[i] == P.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int LastIndex(string s, char p) {

        for(int i = (int)s.size() - 1; i >= 0; i--) {
            if(s[i] == p) {
                return i;
            }
        }

        return -1;
    }
};
