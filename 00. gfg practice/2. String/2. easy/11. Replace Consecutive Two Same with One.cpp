/*
Problem: Replace Consecutive Two Same with One

GFG: https://www.geeksforgeeks.org/problems/consecutive-elements2306/1

Description:
Given a string s of lowercase alphabets, remove consecutive duplicate characters.

Examples:

Input: s = "aabb"   Output: "ab"
Input: s = "aabaa"  Output: "aba"
Input: s = "aaaa"   Output: "a"

Constraints:
1 ≤ n ≤ 10^6

Approach (Single Pass):
- Build result: add char only if it differs from last added char
- No extra data structure needed

Dry Run: s = "aabaa"
  i=0: 'a' → result="a"
  i=1: 'a' == last 'a' → skip
  i=2: 'b' != 'a' → result="ab"
  i=3: 'a' != 'b' → result="aba"
  i=4: 'a' == last 'a' → skip
  Result: "aba" ✅

Time Complexity: O(n)
Space Complexity: O(1) extra (result is required output)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1) extra
    string removeConsecutiveDuplicates(string& s) {

        string result = "";
        result += s[0];

        for(int i = 1; i < s.size(); i++) {
            if(s[i] != s[i - 1]) result += s[i];
        }

        return result;
    }
};
