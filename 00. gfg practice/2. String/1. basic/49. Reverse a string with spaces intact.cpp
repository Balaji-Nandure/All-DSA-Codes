/*
Problem: Reverse a string with spaces intact

GFG: https://www.geeksforgeeks.org/problems/reverse-a-string-with-spaces-intact5234/1

Description:
Reverse the string while keeping spaces at their original indices.

Examples:

Input: S = "Help others"
Output: "sreh topleH"

Input: S = "geeksforgeeks"
Output: "skeegrofskeeg"

Constraints:
1 <= |S| <= 10^5

Approach:
Use two pointers from both ends. If either side points to a space, move that
pointer. Otherwise swap characters and move both pointers.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string reverseWithSpacesIntact(string s) {

        int left = 0;
        int right = (int)s.size() - 1;

        while(left < right) {

            if(s[left] == ' ') {
                left++;
                continue;
            }

            if(s[right] == ' ') {
                right--;
                continue;
            }

            swap(s[left], s[right]);
            left++;
            right--;
        }

        return s;
    }
};
