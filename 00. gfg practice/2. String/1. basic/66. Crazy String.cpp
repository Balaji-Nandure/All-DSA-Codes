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
    // TC: O(n)
    // SC: O(1)
    string getCrazy(string S) {
        if (S.empty()) return S;
        
        bool firstIsLower = islower(S[0]);

        for(int i = 1; i < S.size(); i++) {
            if (firstIsLower == (i % 2 == 0)) {
                S[i] = tolower(S[i]);
            } else {
                S[i] = toupper(S[i]);
            }
        }

        return S;
    }
};
