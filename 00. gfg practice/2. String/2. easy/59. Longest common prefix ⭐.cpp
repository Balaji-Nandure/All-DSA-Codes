/*
Problem: Longest common prefix

Given two strings str1 and str2 of the same length. Find the longest prefix of str1 which is common in str2. Return the length of the longest common prefix.

Constraints:
1 <= |str1| = |str2| <= 100
str1 and str2 contain only lowercase alphabets.

--------------------------------------------------

Pattern:
String Processing + Substring Search

--------------------------------------------------

Key Observation:
- We need to find the longest prefix of `str1` that appears ANYWHERE as a substring in `str2`.
- Since we want the longest prefix, we can start checking prefixes of `str1` from the maximum possible length (which is the length of `str1`) down to 1.
- The first prefix that is found as a substring in `str2` will be the longest one because we are checking in descending order of length.

--------------------------------------------------

Approach:
1. Get the length of `str1` (which is the same as `str2`), let's call it `len`.
2. Loop a variable `i` from `len` down to 1:
    a. Extract the prefix of `str1` of length `i` using `str1.substr(0, i)`.
    b. Check if this prefix exists in `str2` using `str2.find()`.
    c. If it does exist, immediately return `i` as it's the longest valid prefix.
3. If the loop finishes without finding any common prefix, return 0.

--------------------------------------------------

Time Complexity: O(|str1| * |str2|) since `find` can take O(|str2|) in the worst case and we do it up to |str1| times.
Space Complexity: O(|str1|) to store the prefix substring during the checks.

--------------------------------------------------
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int longestCommonPrefix(string str1, string str2) {
        int len = str1.length();
        for (int i = len; i >= 1; --i) {
            string pref = str1.substr(0, i);
            if (str2.find(pref) != string::npos) {
                return i;
            }
        }
        return 0;
    }
};
