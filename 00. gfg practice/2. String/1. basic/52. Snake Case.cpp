/*
Problem: Snake Case

GFG: https://www.geeksforgeeks.org/problems/snake-case/1

Description:
Given sentence S, convert it to snake_case:
- all letters in lowercase
- spaces replaced by underscore '_'

Examples:

Input: N = 14, S = "Geeks ForGeeks"
Output: "geeks_forgeeks"

Input: N = 21, S = "Here comes the garden"
Output: "here_comes_the_garden"

Constraints:
1 <= N <= 10^5

Approach:
Traverse string once:
- if character is uppercase, convert to lowercase
- if character is space, replace with '_'

Time Complexity: O(N)
Space Complexity: O(1) extra (in-place update)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(N)
    // SC: O(1) extra

    string snakeCase(int N, string S) {

        for(int i = 0; i < N; i++) {

            if(S[i] >= 'A' && S[i] <= 'Z') {
                S[i] = char(S[i] - 'A' + 'a');
            } else if(S[i] == ' ') {
                S[i] = '_';
            }
        }

        return S;
    }
};
