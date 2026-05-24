/*
Problem: Sum of numbers in string

GFG: https://www.geeksforgeeks.org/problems/sum-of-numbers-in-string-1587115621/1

Description:
Given a string s containing alphanumeric characters,
find the sum of all numbers present in the string.

Examples:

Input: s = "1abc23"
Output: 24
Explanation:
Numbers are 1 and 23
1 + 23 = 24

Input: s = "geeks4geeks"
Output: 4

Input: s = "abc123xyz45"
Output: 168
Explanation:
123 + 45 = 168

Constraints:
1 ≤ s.size() ≤ 10^5
Sum of numbers ≤ 10^5

Approach (Build Number While Traversing):
- Traverse the string character by character
- If digit:
    build current number
    num = num * 10 + digit
- If non-digit:
    add current number to answer
    reset number to 0
- After loop:
    add last pending number

Dry Run: s = "1abc23"

  i=0 -> '1' digit
    num = 1

  i=1 -> 'a' non-digit
    ans += 1
    ans = 1
    num = 0

  i=4 -> '2'
    num = 2

  i=5 -> '3'
    num = 23

  End:
    ans += 23

  Final Answer = 24 ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    int findSum(string str) {

        int ans = 0;
        int num = 0;

        for(char ch : str) {

            // If digit → build number
            if(isdigit(ch)) {

                num = num * 10 + (ch - '0');
            }
            else {

                // Add completed number
                ans += num;

                // Reset for next number
                num = 0;
            }
        }

        // Add last pending number
        ans += num;

        return ans;
    }
};