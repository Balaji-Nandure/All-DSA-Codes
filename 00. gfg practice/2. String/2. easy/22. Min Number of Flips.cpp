/*
Problem: Min Number of Flips

GFG: https://www.geeksforgeeks.org/problems/min-number-of-flips3210/1

Description:
Given a binary string s,
find minimum flips needed
to make string alternating.

Possible alternating forms:
- "010101..."
- "101010..."

Examples:

Input: s = "001"
Output: 1

Input: s = "0001010111"
Output: 2

Constraints:
1 ≤ s.size() ≤ 10^5

Approach:
- Compare string with both possible patterns
- cnt1 -> flips needed if string starts with '0'
- cnt2 -> flips needed if string starts with '1'
- Return minimum of both

Dry Run:
s = "001"

Pattern1 = "010"
Mismatch = 1

Pattern2 = "101"
Mismatch = 2

Answer = 1 ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    int minFlips(string s) {

        int cnt1 = 0;
        int cnt2 = 0;

        for(int i = 0; i < s.size(); i++) {

            char p1 = (i % 2 == 0) ? '0' : '1';
            char p2 = (i % 2 == 0) ? '1' : '0';

            if(s[i] != p1) cnt1++;

            if(s[i] != p2) cnt2++;
        }

        return min(cnt1, cnt2);
    }
};