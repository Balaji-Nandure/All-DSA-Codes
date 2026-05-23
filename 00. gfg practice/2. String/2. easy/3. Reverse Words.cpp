/*
Problem: Reverse Words

GFG: https://www.geeksforgeeks.org/problems/reverse-words-in-a-given-string5459/1

Description:
Given a string s, reverse the string without reversing its individual words.
Words are separated by dots(.).
Remove leading/trailing/extra dots — output should have single dot between words.

Examples:

Input: s = "i.like.this.program.very.much"
Output: "much.very.program.this.like.i"

Input: s = "..geeks..for.geeks."
Output: "geeks.for.geeks"

Input: s = "..home....."
Output: "home"

Constraints:
1 ≤ s.length() ≤ 10^6

Approach (Extract words + Reverse):
- Split string by '.' to extract words (skip empty tokens)
- Reverse the words vector
- Join with '.'

Dry Run: s = "i.like.this.program.very.much"
  Split → ["i", "like", "this", "program", "very", "much"]
  Reverse → ["much", "very", "program", "this", "like", "i"]
  Join → "much.very.program.this.like.i" ✅

Dry Run: s = "..geeks..for.geeks."
  Split (skip empty) → ["geeks", "for", "geeks"]
  Reverse → ["geeks", "for", "geeks"]
  Join → "geeks.for.geeks" ✅

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1) extra (result string is required output)
    string reverseWords(string& s) {

        string result = "";
        int n = s.size();
        int i = n - 1;

        while(i >= 0) {

            // Skip dots
            while(i >= 0 && s[i] == '.') i--;

            if(i < 0) break;

            // Find word end and start
            int end = i;
            while(i >= 0 && s[i] != '.') i--;
            int start = i + 1;

            // Append separator if result not empty
            if(!result.empty()) result += ".";
            result += s.substr(start, end - start + 1);
        }

        return result;
    }
};
