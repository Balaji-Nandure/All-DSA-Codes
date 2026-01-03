/*
Problem:
Check if Strings Are Rotations of Each Other

Given two strings s1 and s2,
check whether s2 is a rotation of s1.

Definition:
- A string s2 is a rotation of s1 if it can be obtained
  by rotating s1 any number of times.
- Both strings must have the same length.

Examples:
Input  : s1 = "ABCD", s2 = "CDAB"
Output : true

Input  : s1 = "ABCD", s2 = "ACBD"
Output : false

Input  : s1 = "aaaa", s2 = "aaaa"
Output : true


-----------------------------------
Approach (Expected / Optimal – Concatenation + Substring Check):
-----------------------------------
1. If lengths of s1 and s2 are different, return false.
2. Concatenate s1 with itself → temp = s1 + s1.
3. Check if s2 is a substring of temp.
4. If yes, s2 is a rotation of s1.

Why this works:
- Any rotation of s1 will always appear as a substring
  in s1 + s1.
- Length check avoids false positives.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-strings-are-rotations-of-each-other/

LeetCode:
https://leetcode.com/problems/rotate-string/
*/

bool areRotations(string s1, string s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    string temp = s1 + s1;

    return temp.find(s2) != string::npos;
}
