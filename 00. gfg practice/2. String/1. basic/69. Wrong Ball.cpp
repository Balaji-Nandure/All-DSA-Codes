/*
Problem: Wrong Ball
Difficulty: Basic

There is a table on which N balls are kept starting from index 1 to N in horizontal direction. Each ball is either of red (denoted by 'R') or of blue (denoted by 'B') color. Any red ball which is placed on even indices and blue balls placed on odd indices is considered as wrongly placed. You need return the number of balls placed wrong on the table.

Example 1:
Input: S = "RRBB"
Output: 2
Explanation: second R and first B is wrongly placed.

Example 2:
Input: S = "RBRB"
Output: 0
Explanation: No ball is wrongly placed.

Your Task:
You don't need to read input or print anything. Your task is to complete the function countWrongPlacedBalls() which accpets a string as input parameter and returns the number of wrongly placed balls.

Expected Time Complexity: O(N)
Expected Auxiliary Space: O(1)

Constraints:
1 <= N <= 10^5
S[i] = 'R' or S[i] = 'B'
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(N)
    // SC: O(1)
    int countWrongPlacedBalls(string s) {
        int wrongCount = 0;
        
        for(int i = 0; i < s.length(); i++) {
            // 0-based even index corresponds to 1-based odd index (should be 'R')
            if (i % 2 == 0 && s[i] == 'B') {
                wrongCount++;
            }
            // 0-based odd index corresponds to 1-based even index (should be 'B')
            else if (i % 2 != 0 && s[i] == 'R') {
                wrongCount++;
            }
        }
        
        return wrongCount;
    }
};
