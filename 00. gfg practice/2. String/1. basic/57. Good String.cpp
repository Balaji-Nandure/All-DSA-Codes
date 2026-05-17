/*
Problem: Good String

GFG: https://www.geeksforgeeks.org/problems/good-string3035/1

Description:
A string is good if the cyclic alphabet distance between every adjacent pair is
exactly 1. Return "YES" if good, otherwise "NO".

Examples:

Input: s = "aaa"
Output: "NO"

Input: s = "cbc"
Output: "YES"

Constraints:
1 <= N <= 10^5
String contains lowercase English letters only.

Approach:
For each adjacent pair:
- diff = abs(s[i] - s[i - 1])
- cyclicDistance = min(diff, 26 - diff)
If cyclicDistance is not 1 for any pair, return "NO"; otherwise "YES".

Time Complexity: O(N)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(N)
    // SC: O(1)

    string isGoodString(string s) {

        for(int i = 1; i < (int)s.size(); i++) {

            int diff = abs(s[i] - s[i - 1]);
            int cyclicDistance = min(diff, 26 - diff);

            if(cyclicDistance != 1) {
                return "NO";
            }
        }

        return "YES";
    }
};
