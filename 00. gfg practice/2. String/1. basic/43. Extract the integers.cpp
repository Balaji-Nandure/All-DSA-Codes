/*
Problem: Extract the integers

GFG: https://www.geeksforgeeks.org/problems/extract-the-integers/1

Description:
Given a string s, extract all integers present in it. Consecutive digits belong
to the same integer.

Examples:

Input:
s = "1: Prakhar Agrawal, 2: Manish Kumar Rai, 3: Rishabh Gupta56"
Output: ["1", "2", "3", "56"]

Input: s = "geeksforgeeks"
Output: []

Constraints:
1 <= |s| <= 10^5

Approach:
Scan the string once. Start building a token when a digit is found, and keep
adding digits while they are consecutive. Push completed tokens to the answer.

Time Complexity: O(|s|)
Space Complexity: O(|s|)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    vector<string> extractIntegerWords(string s) {

        vector<string> ans;
        int n = s.size();
        int i = 0;

        while(i < n) {

            if(s[i] >= '0' && s[i] <= '9') {

                string token = "";

                while(i < n && s[i] >= '0' && s[i] <= '9') {
                    token.push_back(s[i]);
                    i++;
                }

                ans.push_back(token);
            } else {
                i++;
            }
        }

        return ans;
    }
};
