/*
Problem: Largest number with given sum

GFG: https://www.geeksforgeeks.org/problems/largest-number-possible5028/1

Description:
Given:
- n = total number of digits
- sum = sum of all digits

Return the largest possible number having:
- exactly n digits
- digit sum equal to sum

If impossible, return "-1".

Examples:

Input:
n = 5
sum = 12

Output:
"93000"

Explanation:
9 + 3 + 0 + 0 + 0 = 12
Largest possible number is 93000.

--------------------------------------------------

Input:
n = 3
sum = 29

Output:
"-1"

Explanation:
Maximum possible sum using 3 digits:
9 + 9 + 9 = 27

29 > 27
Impossible.

Constraints:
1 ≤ n ≤ 10^4
0 ≤ sum ≤ 9 * 10^4

Approach (Greedy):
To form the largest number:
- Fill leftmost digits with maximum possible value (9)
- Reduce sum accordingly
- Continue until all digits filled

Why Greedy Works?
- Larger digits at left positions create larger numbers
- So always place maximum possible digit first

Impossible Case:
- If sum > 9*n:
    impossible to distribute sum across n digits

Dry Run:
n = 5
sum = 12

Digit 1:
  put 9
  remaining sum = 3

Digit 2:
  put 3
  remaining sum = 0

Remaining digits:
  put 0 0 0

Answer = "93000" ✅

--------------------------------------------------

Dry Run:
n = 3
sum = 29

Maximum possible sum:
9 * 3 = 27

29 > 27 ❌

Return "-1"

Time Complexity: O(n)
Space Complexity: O(n)   // output string
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    string largestNumber(int n, int sum) {

        // Impossible case
        if(sum > 9 * n) {
            return "-1";
        }

        string result = "";

        for(int i = 0; i < n; i++) {

            // Put maximum possible digit
            int digit = min(9, sum);

            result += (digit + '0');

            sum -= digit;
        }

        return result;
    }
};