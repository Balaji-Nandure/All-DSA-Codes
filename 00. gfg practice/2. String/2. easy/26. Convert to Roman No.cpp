/*
Problem: Convert to Roman No

GFG: https://www.geeksforgeeks.org/problems/convert-to-roman-no/1

Description:
Given an integer n,
convert it into Roman numeral.

Roman Symbols:

I   -> 1
V   -> 5
X   -> 10
L   -> 50
C   -> 100
D   -> 500
M   -> 1000

Special Cases:
4   -> IV
9   -> IX
40  -> XL
90  -> XC
400 -> CD
900 -> CM

Examples:

Input: n = 5
Output: "V"

--------------------------------------------------

Input: n = 3
Output: "III"

--------------------------------------------------

Input: n = 1994
Output: "MCMXCIV"

Constraints:
1 ≤ n ≤ 3999

Approach (Greedy):
- Store Roman values in descending order
- Pick largest possible value repeatedly
- Append corresponding Roman symbol
- Reduce n

Why Greedy Works?
- Roman numeral system always uses
  largest possible symbol first.

Dry Run:
n = 58

50 -> L
remaining = 8

5 -> V
remaining = 3

1 -> I
1 -> I
1 -> I

Answer = "LVIII" ✅

--------------------------------------------------

Dry Run:
n = 1994

1000 -> M
900  -> CM
90   -> XC
4    -> IV

Answer = "MCMXCIV" ✅

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(1)  SC: O(1)
    string convertToRoman(int n) {

        vector<int> val = {
            1000, 900, 500, 400,
            100, 90, 50, 40,
            10, 9, 5, 4, 1
        };

        vector<string> sym = {
            "M", "CM", "D", "CD",
            "C", "XC", "L", "XL",
            "X", "IX", "V", "IV", "I"
        };

        string ans = "";

        for(int i = 0; i < val.size(); i++) {

            while(n >= val[i]) {

                ans += sym[i];

                n -= val[i];
            }
        }

        return ans;
    }
};