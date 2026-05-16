/*
Problem: Length of Last word

GFG: https://www.geeksforgeeks.org/problems/length-of-last-word5632/1

Description:
Given a string s with letters and spaces (including possible trailing spaces),
return the length of the last word.

Examples:

Input: s = "Geeks for Geeks"
Output: 5

Input: s = "Start Coding Here "
Output: 4

Constraints:
1 <= |s| <= 100

Approach:
Start from the end, skip trailing spaces, then count characters of the last
word until a space or beginning is reached.

Time Complexity: O(|s|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int findLength(string s) {

        int i = (int)s.size() - 1;

        while(i >= 0 && s[i] == ' ') {
            i--;
        }

        int length = 0;

        while(i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }

        return length;
    }
};
