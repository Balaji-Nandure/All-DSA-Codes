/*
Problem: Remove repeated digits in a given number

GFG: https://www.geeksforgeeks.org/problems/remove-repeated-digits-in-a-given-number/1

Description:
Given an integer N, remove consecutive repeated digits from it.

Examples:

Input: N = 1224
Output: 124

Input: N = 1242
Output: 1242

Constraints:
1 <= N <= 10^18

Approach (Right-to-Left Digit Scan):
Process digits from least significant to most significant digit. Keep a digit if
it is different from the previous digit seen while scanning from the right.

Key insight:
- Consecutive duplicates are adjacent in the original number
- Scanning from right to left lets us remove repeated runs in one pass
- Rebuild the answer using powers of 10

Algorithm:
1. Take the last digit as the initial previous digit
2. Scan remaining digits from right to left
3. If the current digit differs from previous digit, append it to the result
4. Update the previous digit and power of 10
5. Return the reconstructed number

Time Complexity: O(log N)
Space Complexity: O(1)

Pattern: Digit Processing / Run Compression
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
DIGIT RUN COMPRESSION
=====================================================

TC: O(log N)
SC: O(1)

RUN COMPRESSION
- Work from right to left
- Keep only the first digit of each consecutive run
- Rebuild the number in the correct order

DRY RUN:
n = 1224

Digits from right:
4 -> keep
2 -> keep
2 -> skip
1 -> keep

Result = 124
*/

class Solution {
public:

    // TC: O(log N)
    // SC: O(1)

    long long modify(long long n) {

        long long previousDigit = n % 10;
        long long power = 10;
        long long result = previousDigit;

        while(n > 0) {

            long long currentDigit = n % 10;

            if(currentDigit != previousDigit) {
                result += currentDigit * power;
                previousDigit = currentDigit;
                power *= 10;
            }

            n /= 10;
        }

        return result;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    REMOVING CONSECUTIVE DUPLICATE DIGITS
    + NUMBER INPUT
    + O(LOG N) TARGET

Think immediately:
    RIGHT-TO-LEFT DIGIT SCAN

-----------------------------------------------------

KEY OBSERVATIONS:

1. Only adjacent equal digits need to be removed.
2. Scanning from the right preserves run boundaries cleanly.
3. No extra stack or string is required.

-----------------------------------------------------

COMMON MISTAKES:

1. Removing all duplicate digits globally instead of consecutive ones.
2. Forgetting to update the power of 10.
3. Not handling the last digit as the initial previous digit.

-----------------------------------------------------
*/
