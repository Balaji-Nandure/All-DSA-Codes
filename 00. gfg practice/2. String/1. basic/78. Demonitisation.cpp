/*
Problem: Demonitisation

GFG: https://www.geeksforgeeks.org/problems/demonitisation/1

Description:
Given strings S, m and n, remove occurrences of m and n from S completely.
If resulting string is empty, return "-1".

Examples:

Input: S = "abc", m = "ab", n = "bc"
Output: "-1"

Input: S = "abbbccab", m = "ab", n = "bcc"
Output: "b"

Input: S = "geeksforgks", m = "for", n = "gks"
Output: "geeks"

Constraints:
1 <= |S| <= 1000

Approach:
Repeatedly erase all occurrences of m and n until no more deletions happen.
If final string is empty, return "-1".

Time Complexity: O(|S|^2) (fits constraints)
Space Complexity: O(|S|)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    void eraseAll(string &s, const string &pat, bool &changed) {
        if(pat.empty()) {
            return;
        }

        size_t pos = s.find(pat);
        while(pos != string::npos) {
            s.erase(pos, pat.size());
            changed = true;
            pos = s.find(pat);
        }
    }

    string demonitize(string S, string m, string n) {

        while(true) {
            bool changed = false;

            eraseAll(S, m, changed);
            eraseAll(S, n, changed);

            if(!changed) {
                break;
            }
        }

        if(S.empty()) {
            return "-1";
        }

        return S;
    }
};
