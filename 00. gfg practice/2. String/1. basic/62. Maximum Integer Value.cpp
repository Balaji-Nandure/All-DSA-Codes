/*
Problem: Maximum Integer Value

GFG: https://www.geeksforgeeks.org/problems/maximum-integer-value2449/1

Description:
Given a string S of digits, place either '+' or '*' between consecutive digits
while traversing left to right to maximize the final value.

Examples:

Input: S = "01230"
Output: 9

Input: S = "891"
Output: 73

Constraints:
1 <= |S| < 20
S contains digits only.

Approach (Greedy):
Let current result be ans and next digit be d.
Best local choice is:
- use '+' when ans <= 1 or d <= 1
- otherwise use '*'

Equivalent update:
ans = max(ans + d, ans * d)

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    long long MaximumIntegerValue(string S) {

        long long ans = S[0] - '0';

        for(int i = 1; i < (int)S.size(); i++) {
            long long digit = S[i] - '0';
            ans = max(ans + digit, ans * digit);
        }

        return ans;
    }
};
