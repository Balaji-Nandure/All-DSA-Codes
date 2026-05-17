/*
Problem: Confused pappu

GFG: https://www.geeksforgeeks.org/problems/confused-pappu/1

Description:
Pappu confuses digit 6 with 9. Given the correct amount, return the maximum
extra amount he can give by reading some/all 6 as 9.

Examples:

Input: amount = 56
Output: 3
Explanation: 59 - 56 = 3

Input: amount = 66
Output: 33
Explanation: 99 - 66 = 33

Constraints:
1 <= amount <= 10000001

Approach:
Build the maximum possible mistaken amount by replacing each '6' with '9' in
the decimal representation, then subtract original amount.

Time Complexity: O(number of digits)
Space Complexity: O(number of digits)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(log10(amount))
    // SC: O(log10(amount))

    int findDiff(int amount) {

        string s = to_string(amount);

        for(char &ch : s) {
            if(ch == '6') {
                ch = '9';
            }
        }

        int maximumPossible = stoi(s);
        return maximumPossible - amount;
    }
};
