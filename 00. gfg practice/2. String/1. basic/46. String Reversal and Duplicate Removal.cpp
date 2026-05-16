/*
Problem: String Reversal and Duplicate Removal

GFG: https://www.geeksforgeeks.org/problems/string-reversal-and-duplicate-removal/1

Description:
Given a string S, reverse it while removing spaces and repeated characters.

Examples:

Input: S = "GEEKS FOR GEEKS"
Output: "SKEGROF"

Input: S = "I AM AWESOME"
Output: "EMOSWAI"

Approach:
Traverse from right to left. Ignore spaces. For other characters, append to the
answer only if it has not already been taken.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string reverseString(string S) {

        vector<int> seen(256, 0);
        string ans = "";

        for(int i = (int)S.size() - 1; i >= 0; i--) {
            unsigned char ch = (unsigned char)S[i];

            if(ch == ' ') {
                continue;
            }

            if(seen[ch] == 0) {
                seen[ch] = 1;
                ans.push_back((char)ch);
            }
        }

        return ans;
    }
};
