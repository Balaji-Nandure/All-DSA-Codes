/*
Problem: Special String Comparison

In a native language, the increasing order of priority of characters is a, b, c, d, e, f, g, h, i, j, k, l, m, n, ng, o, p, q, r, s, t, u, v, w, x, y, z. You are given two strings s1 and s2 and your task is to compare them on the basis of the given priority order.

Note: Function must return 0 if both the strings are equal, 1 if s1 is greater than s2, and -1 if s1 is lesser than s2.

Constraints:
1 <= |s1|, |s2| <= 10^5
The string contains lower case English alphabets

--------------------------------------------------

Pattern:
String Processing + Custom Sorting/Lexicographical Comparison

--------------------------------------------------

Key Observation:
- The custom alphabet contains a double-character symbol "ng" which is ordered between 'n' and 'o'.
- We can assign a rank (integer value) to each symbol to facilitate comparison.
- 'a' to 'm' map to 1 to 13.
- 'n' maps to 14.
- "ng" maps to 15.
- 'o' to 'z' map to 16 to 27.
- We iterate through both strings simultaneously, extracting one symbol at a time and comparing their ranks.

--------------------------------------------------

Approach:
1. Define a helper function `getRank(string& s, int& i)` that reads the symbol starting at index `i` from string `s`, returns its rank, and increments `i` by 1 or 2 depending on whether the symbol was a single letter or "ng".
2. Use two pointers `i` and `j` starting at 0 for `s1` and `s2`.
3. Loop while both `i < s1.length()` and `j < s2.length()`:
    a. Get the rank of the next symbol in `s1` using the helper, which advances `i`.
    b. Get the rank of the next symbol in `s2` using the helper, which advances `j`.
    c. If `r1 < r2`, return -1.
    d. If `r1 > r2`, return 1.
4. If the loop terminates without returning, it means all compared symbols were equal up to the length of the shorter string.
5. In this case, the shorter string is considered smaller. If `i == s1.length() && j == s2.length()`, return 0. If `s1` is exhausted first, return -1. Otherwise, return 1.

--------------------------------------------------

Time Complexity: O(|s1| + |s2|) as we traverse both strings at most once.
Space Complexity: O(1) as we only use a few integer variables.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/special-string-comparison/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    int getRank(const string& s, int& i) {
        if (i + 1 < s.length() && s[i] == 'n' && s[i+1] == 'g') {
            i += 2;
            return 15;
        }
        char c = s[i];
        i++;
        if (c < 'n') return c - 'a' + 1;
        if (c == 'n') return 14;
        return c - 'a' + 2;
    }

public:
    int compare(string s1, string s2) {
        int i = 0, j = 0;
        int len1 = s1.length(), len2 = s2.length();
        
        while (i < len1 && j < len2) {
            int r1 = getRank(s1, i);
            int r2 = getRank(s2, j);
            
            if (r1 < r2) return -1;
            if (r1 > r2) return 1;
        }
        
        if (i == len1 && j == len2) return 0;
        if (i == len1) return -1;
        return 1;
    }
};
