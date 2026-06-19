/*
GeeksforGeeks: Sum of two large numbers
Difficulty: Medium

Problem:
Given two strings denoting non-negative numbers s1 and s2. Calculate the sum of s1 and s2.

Examples:
Input: s1 = "25", s2 = "23"
Output: "48"
Explanation: The sum of 25 and 23 is 48.

Input: s1 = "2500", s2 = "23"
Output: "2523"
Explanation: The sum of 2500 and 23 is 2523.

Input: s1 = "2", s2 = "3"
Output: "5"
Explanation: The sum of 2 and 3 is 5.

Constraints:
1 <= |s1|, |s2| <= 10^5
The strings can have leading zeros. The output should not contain any leading zeros except when the sum is 0.

Core Idea:
Because the numbers can have up to 10^5 digits, they cannot fit into standard integer types (like `long long` in C++).
We simulate the basic school addition algorithm:
- Start from the least significant digit (rightmost end) of both strings.
- Add corresponding digits along with a `carry` (initially 0).
- The new digit to append is `(digit1 + digit2 + carry) % 10`.
- The new carry is `(digit1 + digit2 + carry) / 10`.
- After processing all digits, reverse the resulting string.
- Strip any leading zeros from the final result. If the result consists entirely of zeros, return "0".

Approach:
1. Initialize pointers `i = s1.length() - 1` and `j = s2.length() - 1` and `carry = 0`.
2. Loop while `i >= 0`, `j >= 0`, or `carry > 0`:
   - Extract digit from `s1` if `i >= 0`.
   - Extract digit from `s2` if `j >= 0`.
   - Sum them up along with `carry`.
   - Append `sum % 10` to `result`.
   - Update `carry = sum / 10`.
3. Reverse `result`.
4. Skip leading zeros in `result`, but preserve at least one character if it is "0".
5. Return the substring starting from the first non-zero character.

Time Complexity: O(|s1| + |s2|) as we iterate through both strings once.
Space Complexity: O(|s1| + |s2|) to store the result string.

GFG Link: https://www.geeksforgeeks.org/problems/sum-of-two-large-numbers3701/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string findSum(string s1, string s2) {
        string result = "";
        int i = s1.length() - 1;
        int j = s2.length() - 1;
        int carry = 0;
        
        // Loop from right to left
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += s1[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += s2[j] - '0';
                j--;
            }
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }
        
        // Reverse result as we appended from least significant to most significant digit
        reverse(result.begin(), result.end());
        
        // Strip leading zeros
        int k = 0;
        while (k < result.length() - 1 && result[k] == '0') {
            k++;
        }
        
        return result.substr(k);
    }
};

/*
Dry Run — Example:
s1 = "2500", s2 = "23"

- i = 3 (s1[3]='0'), j = 1 (s2[1]='3'), carry = 0 -> sum = 0 + 3 + 0 = 3 -> result = "3", carry = 0, i = 2, j = 0
- i = 2 (s1[2]='0'), j = 0 (s2[0]='2'), carry = 0 -> sum = 0 + 2 + 0 = 2 -> result = "32", carry = 0, i = 1, j = -1
- i = 1 (s1[1]='5'), j < 0, carry = 0             -> sum = 5 + 0 = 5     -> result = "325", carry = 0, i = 0
- i = 0 (s1[0]='2'), j < 0, carry = 0             -> sum = 2 + 0 = 2     -> result = "3252", carry = 0, i = -1

Loop terminates.
Reverse result -> "2523".
No leading zeros to strip (result[0] != '0').
Output: "2523"
*/
