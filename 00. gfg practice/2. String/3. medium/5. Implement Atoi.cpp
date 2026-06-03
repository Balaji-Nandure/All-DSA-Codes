/*
GeeksforGeeks: Implement Atoi
Difficulty: Medium

Problem:
Given a string s, convert it into a 32-bit signed integer (similar to the atoi() function) without using any built-in conversion functions.
The conversion follows these rules:
1. Ignore Leading Whitespaces: Skip all leading whitespace characters.
2. Check Sign: If the next character is either '+' or '-', take it as the sign of the number. If no sign is present, assume the number is positive.
3. Read Digits: Read the digits and ignore any leading zeros. Stop reading when a non-digit character is encountered or the end of the string is reached. If no digits are found, return 0.
4. Handle Overflow: If the number exceeds the range of a 32-bit signed integer:
   - Return 2^31 − 1 (i.e., 2147483647) if it is greater than the maximum value.
   - Return −2^31 (i.e., -2147483648) if it is smaller than the minimum value.

Examples:
Input: s = "-123"
Output: -123

Input: s = " -"
Output: 0
Explanation: No digits are present, therefore the returned answer is 0.

Input: s = " 1231231231311133"
Output: 2147483647
Explanation: Exceeds INT_MAX.

Input: s = "  -0012gfg4"
Output: -12
Explanation: Stops reading after '2' because 'g' is a non-digit.

Core Idea:
This is a classic string parsing problem that strictly follows sequential logic:
1. Traverse and ignore any leading spaces.
2. Parse a potential '+' or '-' character to determine the mathematical sign.
3. Traverse any numeric characters (`isdigit`) and build the number using `ans = ans * 10 + digit`.
4. The most critical edge case is **Integer Overflow**. 
Since the max string length in constraints is 15, the maximum absolute value is 999,999,999,999,999. This comfortably fits within a standard 64-bit integer (`long long`). 
Therefore, we can safely use a `long long` to continuously accumulate the digits, and aggressively check if it has crossed the 32-bit `INT_MAX` or `INT_MIN` thresholds at every step.

Approach:
1. Initialize `i = 0` and `sign = 1`.
2. Skip whitespaces: `while (s[i] == ' ') i++;`
3. Parse Sign: If `s[i] == '+'` or `s[i] == '-'`, update `sign` accordingly and `i++`.
4. Parse Digits: Using a `long long ans = 0`, while `isdigit(s[i])`:
   - Multiply `ans` by 10 and add the integer value of the current digit `(s[i] - '0')`.
   - On-the-fly Overflow Check: 
     - If `sign == 1` and `ans >= INT_MAX`, return `INT_MAX`.
     - If `sign == -1` and `-ans <= INT_MIN`, return `INT_MIN`.
   - Increment `i`.
5. Return the final signed integer `ans * sign`.

Time Complexity: O(N) where N is the length of the string. We scan through the string in a single fast pass.
Space Complexity: O(1) auxiliary space.

GFG Link: https://www.geeksforgeeks.org/problems/implement-atoi/1
*/

#include <iostream>
#include <string>
#include <cctype>
#include <climits>

using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.length();
        
        // 1. Skip leading whitespaces
        while (i < n && s[i] == ' ') {
            i++;
        }
        
        // 2. Check for optional sign
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') {
                sign = -1;
            }
            i++;
        }
        
        // 3. Read digits and build the number
        long long ans = 0;
        while (i < n && isdigit(s[i])) {
            ans = ans * 10 + (s[i] - '0');
            
            // 4. Handle overflow on the fly
            // (Using >= / <= because if it exactly hits INT_MAX, we can safely return INT_MAX directly)
            if (sign == 1 && ans >= INT_MAX) {
                return INT_MAX;
            }
            if (sign == -1 && -ans <= INT_MIN) {
                return INT_MIN;
            }
            
            i++;
        }
        
        // 5. Apply sign and return
        return sign * ans;
    }
};

/*
Dry Run — Example 5:
Input: s = "  -0012gfg4"

1. Skip spaces:
   i=0 (' ') -> skip
   i=1 (' ') -> skip
   i ends up at 2.

2. Check sign:
   s[2] is '-', so sign = -1, i = 3.

3. Read digits:
   i=3 ('0'): isdigit is true. ans = 0 * 10 + 0 = 0.
   i=4 ('0'): isdigit is true. ans = 0 * 10 + 0 = 0.
   i=5 ('1'): isdigit is true. ans = 0 * 10 + 1 = 1.
   i=6 ('2'): isdigit is true. ans = 1 * 10 + 2 = 12.
   
   i=7 ('g'): isdigit is FALSE. Loop breaks!

4. Return ans * sign:
   12 * -1 = -12.

Output: -12
*/
