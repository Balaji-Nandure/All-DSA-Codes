/*
Problem: Check if divisible by 4

GFG: https://www.geeksforgeeks.org/problems/check-if-divisible-by-4/1

Description:
Given a number N as a string, check whether it is divisible by 4.

Return:
- 1 if divisible by 4
- 0 otherwise

Examples:

Input: N = 1124
Output: 1

Input: N = 7
Output: 0

Constraints:
1 <= N <= 10^1000+5

Approach (Last Two Digits Rule):
A number is divisible by 4 if and only if its last two digits form a number
divisible by 4.

Key insight:
- We do not need to inspect the whole string
- Only the last one or two digits matter
- This works even for very large numbers

Algorithm:
1. If the string length is 1, directly check that digit
2. Otherwise, form the number from the last two digits
3. Check whether that number is divisible by 4
4. Return 1 or 0 accordingly

Time Complexity: O(1)
Space Complexity: O(1)

Pattern: Modular Arithmetic / Last Digits
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
LAST TWO DIGITS CHECK
=====================================================

TC: O(1)
SC: O(1)

DIVISIBILITY RULE:
A number is divisible by 4 if the integer formed by its last two digits is
divisible by 4.

Examples:
1124 -> last two digits = 24 -> divisible by 4
7 -> last digit = 7 -> not divisible by 4

ALGORITHM:
1. If length is 1, check s[0]
2. Otherwise, take last two digits as an integer
3. Return 1 if that integer % 4 == 0, else return 0
*/

class Solution {
public:

    // TC: O(1)
    // SC: O(1)

    int divisibleBy4(string N) {

        int n = N.size();

        if(n == 1) {
            return ((N[0] - '0') % 4 == 0) ? 1 : 0;
        }

        int lastTwo = (N[n - 2] - '0') * 10 + (N[n - 1] - '0');
        return (lastTwo % 4 == 0) ? 1 : 0;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    VERY LARGE NUMBER AS STRING
    + DIVISIBILITY BY 4
    + O(1) EXPECTED COMPLEXITY

Think immediately:
    LAST TWO DIGITS TEST

-----------------------------------------------------

KEY OBSERVATIONS:

1. A number's divisibility by 4 depends only on its last two digits.
2. Full conversion to integer is unnecessary.
3. The check works for arbitrarily large inputs.

-----------------------------------------------------

COMMON MISTAKES:

1. Checking only the last digit.
2. Trying to parse the full string into a number.
3. Forgetting the single-digit case.

-----------------------------------------------------
*/
