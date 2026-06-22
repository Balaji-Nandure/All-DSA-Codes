/*
GeeksforGeeks: Smallest number
Difficulty: Medium

Problem:
Given two integers s and d. The task is to find the smallest number such that the sum of its digits is s 
and the number of digits in the number are d. Return a string that is the smallest possible number. 
If it is not possible then return -1.

Examples:
Input: s = 9, d = 2
Output: 18 
Explanation: 18 is the smallest number possible with the sum of digits = 9 and total digits = 2.

Input: s = 20, d = 3 
Output: 299 
Explanation: 299 is the smallest number possible with the sum of digits = 20 and total digits = 3.

Constraints:
1 <= s <= 100
1 <= d <= 6

Core Idea:
- To make the number as small as possible:
  1. We must make the leftmost digits (higher place values) as small as possible.
  2. Consequently, we must make the rightmost digits (lower place values) as large as possible (up to 9).
- First, check if it's possible:
  - The maximum sum we can form with d digits is 9 * d. If s > 9 * d, it is impossible, so return "-1".
  - If s = 0 and d > 1, we can't form a number because the first digit cannot be 0. (Though constraints say s >= 1).
- We construct a string of size d.
- We iterate from right to left (index d-1 down to 1):
  - At each position, we place the largest possible digit (up to 9) but save at least 1 for the first digit (so that the number doesn't start with 0).
  - So: `digit = min(9, s - 1)`.
  - Subtract this `digit` from `s`, and assign it to the current position.
- Finally, for the first digit at index 0, we assign the remaining value of `s`.

Time Complexity: O(d) — We perform a single loop of size d. Given d <= 6, this is O(1) time.
Space Complexity: O(1) auxiliary space (excluding the output string).

GFG Link: https://www.geeksforgeeks.org/problems/smallest-number5831/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(int s, int d) {
        // Step 1: Check if it's possible to form the sum s with d digits
        if (s > 9 * d) {
            return "-1";
        }
        
        string result(d, '0');
        
        // Step 2: Fill digits greedily from right to left (index d-1 down to 1)
        for (int i = d - 1; i > 0; i--) {
            // Reserve at least 1 for the first digit (result[0])
            int digit = min(9, s - 1);
            result[i] = '0' + digit;
            s -= digit;
        }
        
        // Step 3: Put the remaining sum in the first digit
        result[0] = '0' + s;
        
        return result;
    }
};

/*
Dry Run — Example:
s = 20, d = 3
Max possible sum = 9 * 3 = 27. Since 20 <= 27, a valid number is possible.

Initial: result = "000"

1. i = 2 (units place):
   - digit = min(9, 20 - 1) = min(9, 19) = 9.
   - result[2] = '0' + 9 = '9'.
   - s = 20 - 9 = 11.
   - result state: "009"

2. i = 1 (tens place):
   - digit = min(9, 11 - 1) = min(9, 10) = 9.
   - result[1] = '0' + 9 = '9'.
   - s = 11 - 9 = 2.
   - result state: "099"

3. Loop terminates (i = 0 reached).

4. First digit (hundreds place):
   - result[0] = '0' + s = '0' + 2 = '2'.
   - result state: "299"

Output: "299"
*/
