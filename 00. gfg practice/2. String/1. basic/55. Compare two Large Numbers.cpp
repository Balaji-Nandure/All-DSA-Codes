/*
Problem: Compare two Large Numbers

GFG: https://www.geeksforgeeks.org/problems/compare-two-large-numbers/1

Description:
Given two non-negative integers as strings a and b:
- return 1 if a < b
- return 2 if a > b
- return 3 if a == b

Examples:

Input: a = "1234", b = "12345"
Output: 1

Input: a = "100", b = "1"
Output: 2

Constraints:
1 <= |a|, |b| <= 155

Approach:
1. Trim leading zeros for safe comparison.
2. If lengths differ, longer string is larger.
3. If lengths equal, compare lexicographically.

Time Complexity: O(|a| + |b|)
Space Complexity: O(|a| + |b|) in worst case due to substr calls
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string trimLeadingZeros(const string &num) {
        int i = 0;
        while(i < (int)num.size() && num[i] == '0') {
            i++;
        }
        if(i == (int)num.size()) {
            return "0";
        }
        return num.substr(i);
    }

    int check(string a, string b) {

        a = trimLeadingZeros(a);
        b = trimLeadingZeros(b);

        if(a.size() < b.size()) {
            return 1;
        }
        if(a.size() > b.size()) {
            return 2;
        }

        if(a < b) {
            return 1;
        }
        if(a > b) {
            return 2;
        }

        return 3;
    }
};
