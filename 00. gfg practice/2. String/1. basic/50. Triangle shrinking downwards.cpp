/*
Problem: Triangle shrinking downwards

GFG: https://www.geeksforgeeks.org/problems/triangle-shrinking-downwards/1

Description:
Given a string S, form rows by removing one character from the beginning in each
next row. Replace left spaces with dots. Return all rows joined by '.'.

For input "GEEKS", return "GEEKS.EEKS..EKS...KS....S".

Examples:

Input: S = "Geeks"
Output: "Geeks.eeks..eks...ks....s"

Input: S = "@io30"
Output: "@io30..io30...o30....30.....0"

Constraints:
1 <= |S| <= 100

Approach:
For each starting index i:
- add i dots
- append substring S[i..n-1]
Join each row with '.' between rows.

Time Complexity: O(|S|^2)
Space Complexity: O(|S|^2) for output construction
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string triDownwards(string S) {

        int n = S.size();
        string ans = "";

        for(int i = 0; i < n; i++) {
            for(int d = 0; d < i; d++) {
                ans.push_back('.');
            }

            for(int j = i; j < n; j++) {
                ans.push_back(S[j]);
            }
        }

        return ans;
    }
};
