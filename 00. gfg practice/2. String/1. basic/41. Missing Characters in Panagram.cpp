/*
Problem: Missing Characters in Panagram

GFG: https://www.geeksforgeeks.org/problems/missing-characters-in-panagram/1

Description:
Given a string s, return the missing characters required to make it a pangram.
Return missing characters in lowercase and sorted order. If no character is
missing, return "-1".

Examples:

Input: s = "Abcdefghijklmnopqrstuvwxy"
Output: "z"

Input: s = "Abc"
Output: "defghijklmnopqrstuvwxyz"

Constraints:
1 <= |s| <= 10^4

Approach:
Track which alphabets appear in the string using a fixed-size array of 26.
Process letters case-insensitively, then collect missing letters in increasing
order.

Time Complexity: O(|s| + 26)
Space Complexity: O(26)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string missingPanagram(string s) {

        vector<int> present(26, 0);

        for(char ch : s) {

            if(ch >= 'A' && ch <= 'Z') {
                ch = char(ch - 'A' + 'a');
            }

            if(ch >= 'a' && ch <= 'z') {
                present[ch - 'a'] = 1;
            }
        }

        string ans = "";

        for(int i = 0; i < 26; i++) {
            if(present[i] == 0) {
                ans.push_back(char('a' + i));
            }
        }

        if(ans.empty()) {
            return "-1";
        }

        return ans;
    }
};
