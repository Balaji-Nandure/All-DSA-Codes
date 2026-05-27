/*
Problem: Largest odd number in string

Given a string S, representing a large integer. Return the largest-valued odd integer (as a string) that is substring of the given string S.
Note: A substring is a contiguous sequence of characters within a string. A null string ("") is also a substring.

Example 1:
Input: s = "504"
Output: "5"
Explanation: The only subtring "5" is odd number.

Example 2:
Input: s = "2042"
Output: ""
Explanation: All the possible non-empty substring have even value.

Constraints:
1 <= |S| <= 2 * 10^5
S only consists of digits and does not contain any leading zeros.

--------------------------------------------------

Pattern:
String Processing + Greedy

--------------------------------------------------

Key Observation:
- An integer is odd if and only if its last digit is odd (1, 3, 5, 7, 9).
- To maximize the value of the integer, we want to maximize the total number of digits.
- Since the original string `S` does not contain leading zeros, any prefix of `S` will also be a valid number without leading zeros.
- Therefore, the largest odd integer substring will simply be the longest prefix of `S` that ends with an odd digit.
- We can find this efficiently by scanning the string from right to left and stopping at the very first odd digit we encounter.

--------------------------------------------------

Approach:
1. Find the length of the string `n`.
2. Iterate backwards from the last index `i = n - 1` down to `0`.
3. Extract the integer value of the character `s[i]`.
4. If it is odd (`s[i] % 2 != 0`), immediately return the substring starting from index `0` up to index `i` (`s.substr(0, i + 1)`).
5. If the loop completes without finding any odd digits, it means the string has no odd characters at all. Return `""`.

--------------------------------------------------

Time Complexity: O(N) where N is the length of string S. We traverse the string at most once.
Space Complexity: O(1) Auxiliary Space (excluding the memory required to return the output string).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/largest-odd-number-in-string/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string maxOdd(string s) {
        int n = s.length();
        
        // Traverse from right to left to find the rightmost odd digit
        for (int i = n - 1; i >= 0; i--) {
            int digit = s[i] - '0';
            
            // If the digit is odd, the prefix ending here is the largest possible odd number
            if (digit % 2 != 0) {
                return s.substr(0, i + 1);
            }
        }
        
        // If no odd digit exists in the entire string
        return "";
    }
};
