/*
Problem: Run Length Encoding

GFG: https://www.geeksforgeeks.org/problems/run-length-encoding/1

Description:
Given a string s, perform Run-Length Encoding (RLE).
Replace consecutive occurrences of a character with:
character + count of consecutive occurrences.

Examples:

Input: s = "aaaabbbccc"
Output: "a4b3c3"

Input: s = "abbbcdddd"
Output: "a1b3c1d4"

Input: s = "g"
Output: "g1"

Constraints:
1 ≤ s.size() ≤ 10^6

Approach (Single Pass Counting):
- Traverse the string
- Count consecutive same characters
- When character changes:
    append previous character + count
- Finally append last character group

Dry Run: s = "aaaabbbccc"

  Start:
    char='a', count=1

  i=1 -> 'a' == previous
    count=2

  i=2 -> 'a' == previous
    count=3

  i=3 -> 'a' == previous
    count=4

  i=4 -> 'b' != 'a'
    result += "a4"

  Now:
    char='b', count=1

  Continue similarly:
    result = "a4b3c3"

Time Complexity: O(n)
Space Complexity: O(n)   // output string
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    string encode(string s) {

        int n = s.size();

        string result = "";

        int count = 1;

        for(int i = 1; i < n; i++) {

            // Same character → increase count
            if(s[i] == s[i - 1]) {
                count++;
            }
            else {

                // Append previous character + frequency
                result += s[i - 1];
                result += to_string(count);

                // Reset count for new character
                count = 1;
            }
        }

        // Append last character group
        result += s[n - 1];
        result += to_string(count);

        return result;
    }
};