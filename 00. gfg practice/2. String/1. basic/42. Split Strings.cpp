/*
Problem: Split Strings

GFG: https://www.geeksforgeeks.org/problems/split-strings5211/1

Description:
Given a string S containing alphabets, digits, and special characters, split it
into three strings:
- S1: all alphabets
- S2: all digits
- S3: all special characters
Maintain original relative order in each resulting string.

Examples:

Input: S = "geeks01for02geeks03!!!"
Output:
"geeksforgeeks"
"010203"
"!!!"

Input: S = "**Docoding123456789everyday##"
Output:
"Docodingeveryday"
"123456789"
"**##"

Constraints:
1 <= |S| <= 10^5

Approach:
Traverse the string once and classify each character into alphabet, digit, or
special character.

Time Complexity: O(|S|)
Space Complexity: O(|S|)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    vector<string> splitString(string S) {

        string alphabets = "";
        string digits = "";
        string special = "";

        for(char ch : S) {

            if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                alphabets.push_back(ch);
            } else if(ch >= '0' && ch <= '9') {
                digits.push_back(ch);
            } else {
                special.push_back(ch);
            }
        }

        return {alphabets, digits, special};
    }
};
