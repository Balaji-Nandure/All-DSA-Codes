/*
Problem: Find Substring from last of the Given String

GFG: https://www.geeksforgeeks.org/problems/find-substring-from-last-of-the-given-string/1

Description:
Given strings X and Y, return the last index in X where Y appears.
If Y does not appear, return -1.

Examples:

Input: X = "geeksforgeeks", Y = "geeks"
Output: 9

Input: X = "geesforgees", Y = "geeks"
Output: -1

Constraints:
1 <= |X|, |Y| <= 10^5

Approach (KMP):
Use KMP string matching to find all occurrences of Y in X in linear time.
Keep updating answer with each match start index; final value is last occurrence.

Time Complexity: O(|X| + |Y|)
Space Complexity: O(|Y|)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<int> buildLPS(const string &pattern) {
        int m = pattern.size();
        vector<int> lps(m, 0);

        int len = 0;
        int i = 1;

        while(i < m) {
            if(pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else if(len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }

        return lps;
    }

    int search(string X, string Y) {

        int n = X.size();
        int m = Y.size();

        if(m > n) {
            return -1;
        }

        vector<int> lps = buildLPS(Y);
        int i = 0;
        int j = 0;
        int answer = -1;

        while(i < n) {

            if(X[i] == Y[j]) {
                i++;
                j++;
            }

            if(j == m) {
                answer = i - j;
                j = lps[j - 1];
            } else if(i < n && X[i] != Y[j]) {
                if(j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }

        return answer;
    }
};
