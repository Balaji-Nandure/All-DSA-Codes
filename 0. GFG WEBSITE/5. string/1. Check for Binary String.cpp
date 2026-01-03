/*
Problem:
Check for Binary String

Given a string s, check whether it is a binary string or not.
A binary string contains only characters:
- '0'
- '1'

If the string contains any other character, return false.
Otherwise, return true.

Examples:
Input  : s = "101010"
Output : true

Input  : s = "10012"
Output : false

Input  : s = "0000"
Output : true


Approach (Optimal – Linear Scan):
1. Traverse each character of the string.
2. If any character is not '0' or '1', return false immediately.
3. If traversal completes successfully, return true.

Why this works:
- Binary string definition is strict: only two valid characters.
- Single pass guarantees earliest failure detection.
- No extra data structures required.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-string-binary/

LeetCode:
No direct equivalent problem.
(Related to string validation problems)
*/

bool isBinaryString(string s) {
    for (char ch : s) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    return true;
}
