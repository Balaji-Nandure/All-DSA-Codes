/*
Problem: Roman to Integer

GFG: https://www.geeksforgeeks.org/problems/roman-number-to-integer3201/1

Description:
Given a string s in Roman numeral format, convert it to an integer.
I=1, V=5, X=10, L=50, C=100, D=500, M=1000

Examples:

Input: s = "IX"     Output: 9      (10-1)
Input: s = "XL"     Output: 40     (50-10)
Input: s = "MCMIV"  Output: 1904   (1000+900+4)

Constraints:
1 ≤ roman number ≤ 3999

Approach (Left to Right):
- If current value < next value → subtract current (e.g., I before V = 4)
- Else → add current
- This handles all subtractive cases: IV, IX, XL, XC, CD, CM

Dry Run: s = "MCMIV"
  M(1000) < C(100)? No  → +1000  result=1000
  C(100)  < M(1000)? Yes → -100  result=900
  M(1000) < I(1)? No    → +1000  result=1900
  I(1)    < V(5)? Yes   → -1     result=1899
  V(5)    last char      → +5    result=1904 ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1)
    int romanToDecimal(string& s) {

        unordered_map<char, int> val = {
            {'I',1}, {'V',5}, {'X',10}, {'L',50},
            {'C',100}, {'D',500}, {'M',1000}
        };

        int result = 0;
        int n = s.size();

        for(int i = 0; i < n; i++) {

            // If current < next → subtract (subtractive case)
            if(i + 1 < n && val[s[i]] < val[s[i + 1]])
                result -= val[s[i]];
            else
                result += val[s[i]];
        }

        return result;
    }
};
