/*
Problem: Isomorphic Strings

GFG: https://www.geeksforgeeks.org/problems/isomorphic-strings-1587115620/1

Description:
Given two equal-length strings s1 and s2 of lowercase letters, check if they are isomorphic.
Two strings are isomorphic if characters in s1 can be mapped to s2 such that:
- Each char maps to exactly one char (one-to-one)
- No two different chars map to the same char

Examples:

Input: s1 = "aab", s2 = "xxy"  Output: true   (a→x, b→y)
Input: s1 = "aab", s2 = "xyz"  Output: false  (a maps to both x,y)
Input: s1 = "abc", s2 = "xxz"  Output: false  (a,b both map to x)

Constraints:
1 ≤ s1.size() = s2.size() ≤ 10^5

Approach (Two Hash Maps):
- Need bidirectional mapping: s1→s2 AND s2→s1
- map1[a] = x means 'a' in s1 maps to 'x' in s2
- map2[x] = a means 'x' in s2 maps to 'a' in s1
- If conflict in either direction → false

Dry Run: s1 = "aab", s2 = "xxy"
  i=0: a→x (new), x→a (new)     map1:{a:x} map2:{x:a}
  i=1: a→? map1[a]=x == x ✅    map2[x]=a == a ✅
  i=2: b→y (new), y→b (new)     map1:{a:x,b:y} map2:{x:a,y:b}
  All good → true ✅

Dry Run: s1 = "abc", s2 = "xxz"
  i=0: a→x (new), x→a (new)     map1:{a:x} map2:{x:a}
  i=1: b→x (new in map1), but map2[x]=a != b ❌ → false

Time Complexity: O(n)
Space Complexity: O(1) — at most 26 entries in each map
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1)
    bool areIsomorphic(string& s1, string& s2) {

        if(s1.size() != s2.size()) return false;

        char map1[128] = {0};  // s1 → s2
        char map2[128] = {0};  // s2 → s1

        for(int i = 0; i < s1.size(); i++) {

            char c1 = s1[i], c2 = s2[i];

            if(map1[c1] && map1[c1] != c2) return false;
            if(map2[c2] && map2[c2] != c1) return false;

            map1[c1] = c2;
            map2[c2] = c1;
        }

        return true;
    }
};
