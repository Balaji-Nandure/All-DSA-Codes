/*
Problem: Extraction of secret message

GFG: https://www.geeksforgeeks.org/problems/extraction-of-secret-message/1

Description:
Given encoded string S, extract the secret message by treating every occurrence
of substring "LIE" as a separator.

Examples:

Input: S = "LIEILIEAMLIELIECOOL"
Output: "I AM COOL"

Input: S = "LIELIEALIEBCLIE"
Output: "A BC"

Constraints:
1 <= N <= 10^6

Approach:
Scan string left to right.
If the next three characters are "LIE", add one space (as separator).
Otherwise append current character to answer.

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(N)
    // SC: O(N)

    string ExtractMessage(string S) {

        string ans = "";
        int n = S.size();

        for(int i = 0; i < n; ) {

            if(i + 2 < n && S[i] == 'L' && S[i + 1] == 'I' && S[i + 2] == 'E') {
                if(!ans.empty() && ans.back() != ' ') {
                    ans.push_back(' ');
                }
                i += 3;
            } else {
                ans.push_back(S[i]);
                i++;
            }
        }

        while(!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }

        return ans;
    }
};
