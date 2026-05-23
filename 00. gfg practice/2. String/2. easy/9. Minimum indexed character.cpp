/*
Problem: Minimum indexed character

GFG: https://www.geeksforgeeks.org/problems/minimum-indexed-character-1587115620/1

Description:
Given strings s1 and s2, find the minimum index in s1 of a character
that is also present in s2. Return -1 if no common character.

Examples:

Input: s1 = "geeksforgeeks", s2 = "set"  Output: 1  ('e' at index 1)
Input: s1 = "adcffaet", s2 = "onkl"      Output: -1

Constraints:
1 ≤ s1.size(), s2.size() ≤ 10^5

Approach (Hash Set):
- Store all chars of s2 in a set (bool array)
- Traverse s1 left to right, return first index where char exists in set

Dry Run: s1 = "geeksforgeeks", s2 = "set"
  Set: {s, e, t}
  i=0: 'g' not in set → skip
  i=1: 'e' in set → return 1 ✅

Time Complexity: O(n + m)  where n=|s1|, m=|s2|
Space Complexity: O(1) — fixed 26-size array
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n + m)  SC: O(1)
    int minIndexChar(string& s1, string& s2) {

        bool present[26] = {false};

        for(char ch : s2) present[ch - 'a'] = true;

        for(int i = 0; i < s1.size(); i++) {
            if(present[s1[i] - 'a']) return i;
        }

        return -1;
    }
};
