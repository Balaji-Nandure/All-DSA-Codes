/*
Problem: Duck Number

GFG: https://www.geeksforgeeks.org/problems/duck-number/1

Description:
A Duck number is a positive number that contains at least one zero, but not as
the leading digit. Given num as string, return "YES" if it is a Duck number,
otherwise return "NO".

Examples:

Input: num = "707069"
Output: "YES"

Input: num = "02364"
Output: "NO"

Constraints:
1 <= |num| <= 10^4

Approach:
1. If first character is '0', return "NO".
2. Check remaining characters for '0'.
3. If found, return "YES", else "NO".

Time Complexity: O(|num|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string checkDuck(string num) {

        if(num.empty()) {
            return "NO";
        }

        // Leading zero is not allowed for Duck numbers, and "0" itself is not
        // a positive number.
        if(num[0] == '0') {
            return "NO";
        }

        for(int i = 1; i < (int)num.size(); i++) {
            if(num[i] == '0') {
                return "YES";
            }
        }

        return "NO";
    }
};
