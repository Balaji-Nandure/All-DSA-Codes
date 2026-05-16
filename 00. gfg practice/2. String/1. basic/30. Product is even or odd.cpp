/*
Problem: Product is even or odd?

GFG: https://www.geeksforgeeks.org/problems/product-is-even-or-odd/1

Description:
You are given two large numbers N1 and N2 as strings. Determine whether their
product is even or odd.

Return:
- 1 if product is even
- 0 if product is odd

Examples:

Input: N1 = "12", N2 = "15"
Output: 1
Explanation: 12 * 15 = 180, which is even.

Input: N1 = "123", N2 = "457"
Output: 0
Explanation: 123 * 457 = 56211, which is odd.

Constraints:
1 <= N1, N2 <= 10^99

Approach (Parity Check):
We do not need full multiplication. Product parity depends only on whether at
least one number is even.

Key insight:
- A number is even if its last digit is even
- Product is odd only when both numbers are odd
- So check the last digit of each string

Algorithm:
1. Read last character of N1 and N2
2. Convert to digit and check parity
3. If either digit is even, return 1
4. Otherwise return 0

Time Complexity: O(1)
Space Complexity: O(1)

Pattern: Math / Parity / Last Digit Check
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
PARITY CHECK APPROACH
=====================================================

TC: O(1)
SC: O(1)

PARITY OBSERVATION
- Even * anything = even
- Odd * odd = odd
- Therefore only one case gives odd product:
  both numbers are odd

KEY INSIGHT:
Parity of a number is fully determined by its last digit.
So for very large numbers in string form, we only inspect the final character.

ALGORITHM:
1. d1 = last digit of N1
2. d2 = last digit of N2
3. If d1 is even OR d2 is even, return 1
4. Else return 0

DRY RUN:
N1 = "12", N2 = "15"
last digits: 2 and 5
2 is even -> product is even -> return 1
*/

class Solution {
public:

    // TC: O(1)
    // SC: O(1)

    int EvenOdd(string N1, string N2) {

        int d1 = N1.back() - '0';
        int d2 = N2.back() - '0';

        if((d1 % 2 == 0) || (d2 % 2 == 0)) {
            return 1;
        }

        return 0;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    VERY LARGE INTEGERS AS STRINGS
    + EVEN/ODD DECISION
    + PRODUCT PARITY

Think immediately:
    LAST DIGIT PARITY CHECK

-----------------------------------------------------

KEY OBSERVATIONS:

1. Full multiplication is unnecessary.
2. Only the last digit matters for odd/even.
3. Product is odd only if both factors are odd.
4. Works for huge values represented as strings.

-----------------------------------------------------

COMMON MISTAKES:

1. Trying to convert entire string to integer.
2. Multiplying large numbers directly.
3. Forgetting that one even factor makes product even.
4. Returning reversed output mapping (1/0).

-----------------------------------------------------

SIMILAR PROBLEMS

- Check if sum is even or odd
- Last digit of power/product
- Divisibility checks on big integers in strings

-----------------------------------------------------

REUSABLE PATTERN:

Whenever:
- Number is too large for standard integer types
- Question depends on parity or divisibility
- Property depends on suffix digits

Think:
String-based last-digit math

Algorithm:
1. Identify minimal digits needed
2. Read those digits from string end
3. Apply property rule (parity/divisibility)
4. Return result without full arithmetic

-----------------------------------------------------
*/
