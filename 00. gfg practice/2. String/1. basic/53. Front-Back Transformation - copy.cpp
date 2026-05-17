/*
Problem: Front-Back Transformation - copy

GFG: https://www.geeksforgeeks.org/problems/front-back-transformation/1

Description:
Given a string S of English alphabets, replace each letter by its reverse
alphabet counterpart:
- 'a' <-> 'z', 'b' <-> 'y', ... , 'm' <-> 'n'
- same mapping for uppercase letters

Examples:

Input: S = "Hello"
Output: "Svool"

Input: S = "GfG"
Output: "TuT"

Constraints:
1 <= |S| <= 10^5

Approach:
For lowercase: transformed = 'a' + ('z' - ch)
For uppercase: transformed = 'A' + ('Z' - ch)

Time Complexity: O(|S|)
Space Complexity: O(1) extra (in-place update)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1) extra

    string convert(string s) {

        for(char &ch : s) {

            if(ch >= 'a' && ch <= 'z') {
                ch = char('a' + ('z' - ch));
            } else if(ch >= 'A' && ch <= 'Z') {
                ch = char('A' + ('Z' - ch));
            }
        }

        return s;
    }
};
