/*
Problem: Perfect Reversible String

GFG: https://www.geeksforgeeks.org/problems/perfect-reversible-string/1

Description:
Check if reverse of every possible substring of str is also present in str.
Return 1 if true, else 0.

Examples:

Input: n = 2, str = "ab"
Output: 0

Input: n = 3, str = "aba"
Output: 1

Constraints:
1 <= n <= 2 * 10^5

Key Observation:
The whole string itself is one of the substrings. So reverse(str) must also be
present in str. The only substring of length n is str itself, therefore:
reverse(str) == str.
So the condition is equivalent to checking whether str is a palindrome.

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int isReversible(string str, int n) {

        int left = 0;
        int right = n - 1;

        while(left < right) {
            if(str[left] != str[right]) {
                return 0;
            }
            left++;
            right--;
        }

        return 1;
    }
};
