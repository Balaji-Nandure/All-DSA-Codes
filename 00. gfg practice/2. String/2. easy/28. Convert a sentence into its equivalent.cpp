/*
Problem: Convert a sentence into its equivalent
mobile numeric keypad sequence

GFG:
https://www.geeksforgeeks.org/problems/convert-a-sentence-into-its-equivalent-mobile-numeric-keypad-sequence/1

Description:
Given an uppercase string,
convert every character into its
mobile keypad sequence.

Rules:
- Space -> 0

Keypad Mapping:

2 -> ABC
3 -> DEF
4 -> GHI
5 -> JKL
6 -> MNO
7 -> PQRS
8 -> TUV
9 -> WXYZ

Examples:

Input:
S = "GFG"

Output:
"43334"

Explanation:
G -> 4
F -> 333
G -> 4

--------------------------------------------------

Input:
S = "HEY U"

Output:
"4433999088"

Explanation:
H -> 44
E -> 33
Y -> 999
space -> 0
U -> 88

Constraints:
1 ≤ s.size() ≤ 10^5

Approach:
- Store keypad sequence for every alphabet
- Traverse string
- Append corresponding sequence

Dry Run:
S = "ABC"

A -> 2
B -> 22
C -> 222

Answer:
"222222"

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    string printSequence(string s) {

        vector<string> mp = {
            "2",    "22",   "222",
            "3",    "33",   "333",
            "4",    "44",   "444",
            "5",    "55",   "555",
            "6",    "66",   "666",
            "7",    "77",   "777",  "7777",
            "8",    "88",   "888",
            "9",    "99",   "999",  "9999"
        };

        string ans = "";

        for(char ch : s) {

            // Space
            if(ch == ' ') {
                ans += '0';
            }
            else {

                ans += mp[ch - 'A'];
            }
        }

        return ans;
    }
};