/*
GeeksforGeeks: Add Binary Strings
Difficulty: Medium

Problem:
Given two binary strings s1 and s2 consisting of only 0s and 1s. Find the resultant string after adding the two Binary Strings.
Note: The input strings may contain leading zeros but the output string should not have any leading zeros.

Examples:
Input: s1 = "1101", s2 = "111"
Output: 10100
Explanation:
 1101
+  111
 -----
 10100

Input: s1 = "00100", s2 = "010"
Output: 110
Explanation: 
  100
+  10
 -----
  110

Constraints:
1 <= s1.size(), s2.size() <= 10^6

Core Idea:
This is similar to adding decimal numbers, but with base 2:
- Iterate from right to left (least significant bit to most significant bit) of both strings.
- Add digits along with `carry` (initially 0).
- In binary, the new bit to append is `(bit1 + bit2 + carry) % 2`.
- The new carry is `(bit1 + bit2 + carry) / 2`.
- Reverse the resulting string.
- Strip any leading zeros from the final result. If the result consists entirely of zeros, preserve a single "0".

Approach:
1. Initialize pointers `i = s1.length() - 1` and `j = s2.length() - 1` and `carry = 0`.
2. Loop while `i >= 0`, `j >= 0`, or `carry > 0`:
   - Extract bit from `s1` if `i >= 0`.
   - Extract bit from `s2` if `j >= 0`.
   - Sum them up along with `carry`.
   - Append `sum % 2` to `result`.
   - Update `carry = sum / 2`.
3. Reverse `result`.
4. Skip leading zeros in `result`, but preserve at least one character if it is "0" (using a simple pointer `k` to find the first non-zero bit).
5. Return the substring starting from `k`.

Time Complexity: O(|s1| + |s2|) — single pass to add the binary strings.
Space Complexity: O(|s1| + |s2|) — to store the result string.

GFG Link: https://www.geeksforgeeks.org/problems/add-binary-strings5722/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string addBinary(string s1, string s2) {
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
            carry = sum / 2;
            result.push_back((sum % 2) + '0');
        }
        
        // Reverse result as we appended from least significant to most significant bit
        reverse(result.begin(), result.end());
        
        // Strip leading zeros (keep at least one character in case result is all "0")
        int k = 0;
        while (k < result.length() - 1 && result[k] == '0') {
            k++;
        }
        
        return result.substr(k);
    }
};

/*
Dry Run — Example:
s1 = "00100", s2 = "010"

- i = 4 (s1[4]='0'), j = 2 (s2[2]='0'), carry = 0 -> sum = 0 + 0 + 0 = 0 -> result = "0", carry = 0, i = 3, j = 1
- i = 3 (s1[3]='0'), j = 1 (s2[1]='1'), carry = 0 -> sum = 0 + 0 + 1 = 1 -> result = "01", carry = 0, i = 2, j = 0
- i = 2 (s1[2]='1'), j = 0 (s2[0]='0'), carry = 0 -> sum = 0 + 1 + 0 = 1 -> result = "011", carry = 0, i = 1, j = -1
- i = 1 (s1[1]='0'), j < 0, carry = 0             -> sum = 0 + 0 = 0     -> result = "0110", carry = 0, i = 0
- i = 0 (s1[0]='0'), j < 0, carry = 0             -> sum = 0 + 0 = 0     -> result = "01100", carry = 0, i = -1

Loop terminates.
Reverse result -> "00110".
Strip leading zeros:
- k = 0, result[0] == '0' -> k = 1
- k = 1, result[1] == '0' -> k = 2
- k = 2, result[2] == '1' -> loop stops.
Return result.substr(2) -> "110".

Output: "110"
*/
