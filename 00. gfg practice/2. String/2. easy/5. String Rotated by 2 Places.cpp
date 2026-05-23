/*
Problem: String Rotated by 2 Places

GFG: https://www.geeksforgeeks.org/problems/check-if-string-is-rotated-by-two-places-1587115620/1

Description:
Given two strings s1 and s2, return true if s2 can be obtained by rotating
s1 by exactly 2 places (clockwise OR anti-clockwise). Both rotations in same direction.

Examples:

Input: s1 = "amazon", s2 = "azonam"    Output: true   (anti-clockwise by 2)
Input: s1 = "geeksforgeeks", s2 = "geeksgeeksfor"  Output: false
Input: s1 = "ab", s2 = "ab"            Output: true

Constraints:
1 ≤ s1.length, s2.length ≤ 10^5

Approach (Direct Rotation Check):
- If lengths differ → false
- Anti-clockwise by 2: move first 2 chars to end → s1[2..n-1] + s1[0..1]
- Clockwise by 2: move last 2 chars to front → s1[n-2..n-1] + s1[0..n-3]
- Check if either rotation matches s2

Dry Run: s1 = "amazon", s2 = "azonam"
  n = 6
  Anti-clockwise: s1[2..5] + s1[0..1] = "azon" + "am" = "azonam" == s2 ✅

Dry Run: s1 = "ab", s2 = "ab"
  n = 2
  Anti-clockwise: s1[2..1] + s1[0..1] = "" + "ab" = "ab" == s2 ✅

Time Complexity: O(n)
Space Complexity: O(n) — for substr (unavoidable for comparison)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(n)
    bool isRotated(string& s1, string& s2) {

        int n = s1.size();
        if(n != s2.size()) return false;
        if(n < 2) return s1 == s2;

        // Anti-clockwise by 2: first 2 go to end
        string antiClock = s1.substr(2) + s1.substr(0, 2);

        // Clockwise by 2: last 2 come to front
        string clockwise = s1.substr(n - 2) + s1.substr(0, n - 2);

        return (antiClock == s2 || clockwise == s2);
    }
};
