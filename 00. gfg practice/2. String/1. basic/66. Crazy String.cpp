/*
Problem: Crazy String

GFG: https://www.geeksforgeeks.org/problems/crazy-string/1

Description:
Convert a string into alternating lowercase/uppercase sequence without changing
the character at index 0.

Examples:

Input:  "geeksforgeeks"
Output: "gEeKsFoRgEeKs"

Input:  "Geeksforgeeks"
Output: "GeEkSfOrGeEkS"

Constraints:
1 <= |S| <= 10^5

Approach:
Keep S[0] unchanged. For each next index i:
- If i parity is same as index 0, use same case as S[0]
- Otherwise use opposite case

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    char toLowerCase(char ch) {
        if(ch >= 'A' && ch <= 'Z') {
            return char(ch - 'A' + 'a');
        }
        return ch;
    }

    char toUpperCase(char ch) {
        if(ch >= 'a' && ch <= 'z') {
            return char(ch - 'a' + 'A');
        }
        return ch;
    }

    // TC: O(n)
    // SC: O(1)
    string getCrazy(string S) {

        bool firstIsLower = (S[0] >= 'a' && S[0] <= 'z');

        for(int i = 1; i < (int)S.size(); i++) {

            bool sameParityAsZero = (i % 2 == 0);

            if(firstIsLower) {
                if(sameParityAsZero) {
                    S[i] = toLowerCase(S[i]);
                } else {
                    S[i] = toUpperCase(S[i]);
                }
            } else {
                if(sameParityAsZero) {
                    S[i] = toUpperCase(S[i]);
                } else {
                    S[i] = toLowerCase(S[i]);
                }
            }
        }

        return S;
    }
};
