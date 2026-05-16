/*
Problem: Pattern of Strings

GFG: https://www.geeksforgeeks.org/problems/pattern-of-strings3829/1

Description:
Given a string s, print the pattern by decreasing one character after each line.

Examples:

Input: s = "GeeK"
Output:
GeeK
Gee
Ge
G

Input: s = "G*g"
Output:
G*g
G*
G

Constraints:
1 <= |s| <= 10^3

Approach (Shrinking Prefix):
Print the prefix of length n, then n-1, then n-2, until 1.

Key insight:
- Each line is just a prefix of the original string
- The length decreases by one each time

Algorithm:
1. Find the length n of the string
2. For i from n down to 1:
   - Print the substring s[0..i-1]
3. Move to the next line after each print

Time Complexity: O(n^2)
Space Complexity: O(1)

Pattern: String Pattern Printing / Prefix Shrinking
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
SHRINKING PREFIX PATTERN
=====================================================

TC: O(n^2)
SC: O(1)

PATTERN IDEA
- Print the full string
- Remove one character from the end each line
- Continue until only one character remains

DRY RUN:
s = "GeeK"

GeeK
Gee
Ge
G
*/

class Solution {
public:

    // TC: O(n^2)
    // SC: O(n)

    vector<string> pattern(string& s) {

        vector<string> ans;
        int n = s.size();

        for(int len = n; len >= 1; len--) {
            ans.push_back(s.substr(0, len));
        }

        return ans;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    PRINTING SUCCESSIVE PREFIXES
    + STRING SHRINKING
    + PATTERN OUTPUT

Think immediately:
    PREFIX LOOP

-----------------------------------------------------

KEY OBSERVATIONS:

1. Each output line is a prefix of the input string.
2. The prefix length decreases by exactly one.
3. No extra storage is needed.

-----------------------------------------------------

COMMON MISTAKES:

1. Printing suffixes instead of prefixes.
2. Forgetting to print a newline after each line.
3. Starting from length 0 instead of 1.

-----------------------------------------------------
*/
