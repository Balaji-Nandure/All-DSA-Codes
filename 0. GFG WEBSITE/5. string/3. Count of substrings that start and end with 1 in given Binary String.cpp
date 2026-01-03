/*
Problem:
Count of Substrings that Start and End with 1 in a Given Binary String

Given a binary string s consisting of characters '0' and '1',
find the count of all substrings that:
- start with '1'
- end with '1'

Examples:
Input  : s = "00100101"
Output : 3
Explanation:
Valid substrings are:
"1001", "100101", "101"

Input  : s = "1111"
Output : 10
Explanation:
All substrings that start and end with '1':
Total = C(4,2) + 4 = 6 + 4 = 10

Input  : s = "000"
Output : 0


Approach (Expected / Optimal – Combinatorics):
1. Count the number of '1's in the string → let count = c.
2. Any substring that starts and ends with '1' is formed by choosing:
   - a starting '1'
   - an ending '1' (can be the same position)
3. Number of such substrings =
      c (single-character "1")
    + C(c, 2) (pairs of different '1's)
   = c * (c + 1) / 2

Why this works:
- Every valid substring corresponds to choosing either:
  - one '1' (length = 1), or
  - two '1's as boundaries.
- Positions of '0' in between do not matter.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/count-of-substrings-that-start-and-end-with-1-in-binary-string/

LeetCode:
No direct equivalent problem.
(Related to substring counting and combinatorics)
*/

int countSubstringsStartEndWith1(string s) {
    int countOne = 0;
    int result = 0;

    // Count number of '1's
    for (char ch : s) {
        if (ch == '1') {
            result += countOne;
            countOne++;
        }
    }

    return result;
}
