/*
Problem: Rock Paper Scissors!

GFG: https://www.geeksforgeeks.org/problems/rock-paper-scissors-game/1

Description:
Given a string S of length 2:
- S[0] is move of player A
- S[1] is move of player B

Moves are from {R, P, S}. Return:
- "A" if A wins
- "B" if B wins
- "DRAW" if both moves are same

Examples:

Input: S = "RR"
Output: "DRAW"

Input: S = "RS"
Output: "A"

Constraints:
|S| = 2
S[i] in {R, P, S}

Approach:
Handle draw first, then check the three winning cases for A.

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(1)
    // SC: O(1)

    string gameResult(string S) {

        char a = S[0];
        char b = S[1];

        if(a == b) {
            return "DRAW";
        }

        if((a == 'R' && b == 'S') ||
           (a == 'S' && b == 'P') ||
           (a == 'P' && b == 'R')) {
            return "A";
        }

        return "B";
    }
};
