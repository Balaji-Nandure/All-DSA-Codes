/*
Problem: Shortest direction

GFG: https://www.geeksforgeeks.org/problems/shortest-direction/1

Description:
Given a path string with only E, W, N, S moves, return the shortest path that
reaches the same final point. Output must be lexicographically sorted.

Examples:

Input: S = "SSSNEEEW"
Output: "EESS"

Input: S = "NESNWES"
Output: "E"

Constraints:
1 <= |S| <= 10^5

Approach:
Count net horizontal and vertical movement:
- horizontal = count(E) - count(W)
- vertical   = count(N) - count(S)
Then build answer in lexicographic order among {E, N, S, W}:
- add E or W based on horizontal
- add N or S based on vertical

Time Complexity: O(|S|)
Space Complexity: O(|S|) for output
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(n) output

    string shortestPath(string S) {

        int horizontal = 0;
        int vertical = 0;

        for(char ch : S) {
            if(ch == 'E') {
                horizontal++;
            } else if(ch == 'W') {
                horizontal--;
            } else if(ch == 'N') {
                vertical++;
            } else if(ch == 'S') {
                vertical--;
            }
        }

        string ans = "";

        // Lexicographic order: E < N < S < W
        if(horizontal > 0) {
            ans.append(horizontal, 'E');
        }
        if(vertical > 0) {
            ans.append(vertical, 'N');
        }
        if(vertical < 0) {
            ans.append(-vertical, 'S');
        }
        if(horizontal < 0) {
            ans.append(-horizontal, 'W');
        }

        return ans;
    }
};
