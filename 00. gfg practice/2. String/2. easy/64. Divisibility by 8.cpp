/*
Problem: Divisibility by 8

Given a string s representing a non-negative decimal number, determine whether the number is divisible by 8. Return true if it is divisible by 8, otherwise return false.

Constraints:
1 <= |s| <= 10^6

--------------------------------------------------

Pattern:
Math / Divisibility Rules

--------------------------------------------------

Key Observation:
- A large number is divisible by 8 if and only if the number formed by its last three digits is divisible by 8.
- If the number has fewer than 3 digits, we simply check the number itself.
- Because the string can be up to 10^6 characters long, parsing the entire string into an integer or even a long long will cause an overflow. The divisibility rule allows us to bypass this by only looking at the last 3 digits.

--------------------------------------------------

Approach:
1. Find the length of the string `n`.
2. If `n <= 2`, form the integer from the entire string.
3. If `n >= 3`, form the integer from only the last 3 characters of the string.
4. Check if the resulting integer is divisible by 8 (i.e., `num % 8 == 0`).
5. Return the boolean result.

--------------------------------------------------

Time Complexity: O(1) as we only ever look at the last 3 characters of the string, regardless of the string's total length.
Space Complexity: O(1) as we only use a few integer variables for calculation.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/divisibility-by-8/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    // Function to check whether the given number is divisible by 8.
    bool DivisibleByEight(string s) {
        int n = s.length();
        int num = 0;
        
        if (n == 1) {
            num = s[0] - '0';
        } else if (n == 2) {
            num = (s[0] - '0') * 10 + (s[1] - '0');
        } else {
            num = (s[n-3] - '0') * 100 + (s[n-2] - '0') * 10 + (s[n-1] - '0');
        }
        
        return (num % 8 == 0);
    }
};
