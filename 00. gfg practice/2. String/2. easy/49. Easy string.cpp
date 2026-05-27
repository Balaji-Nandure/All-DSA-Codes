/*
Problem: Easy string

You are given the string S. Compress the string when lower and upper cases are the same. In compressed string characters should be in lowercase.

Example 1:
Input: S = "aaABBb"
Output: "3a3b"
Explanation: As 'a' appears 3 times consecutively and 'b' also 3 times, and 'b' and 'B' considered as same. 

Example 2:
Input: S = "aaacca"
Output: "3a2c1a"
Explanation: As 'a' appears 3 times consecutively and 'c' also 2 times, and then 'a' 1 time.

Constraints:
1 <= |S| <= 2 * 10^5
S contains only lowercase and uppercase characters.

--------------------------------------------------

Pattern:
String Processing + Run Length Encoding

--------------------------------------------------

Key Observation:
- We need to count consecutive identical characters, ignoring case.
- We can convert each character to lowercase using `tolower()` before comparing it to the next.
- The required format for the compressed string is the numeric count followed by the lowercase character (e.g., "3a"). *Note: this is slightly different from standard Run Length Encoding which is usually "a3".*
- We maintain a `count` variable. Whenever the current character (in lowercase) matches the next character (in lowercase), we increment `count`.
- When they don't match, we append the `count` and the lowercase version of the character to our answer string, and then reset `count` to 1.

--------------------------------------------------

Approach:
1. Initialize an empty string `ans` and set `count` to 1.
2. Iterate `i` from 0 to `N - 1`.
3. Check if we haven't reached the end (`i < N - 1`) and if `tolower(S[i]) == tolower(S[i+1])`.
4. If they match, simply increment `count`.
5. If they don't match (meaning we reached the end of a group of identical characters), append `to_string(count)` and `tolower(S[i])` to `ans`.
6. Reset `count = 1` for the next group.
7. Return `ans`.

--------------------------------------------------

Time Complexity: O(N) where N is the length of string S.
Space Complexity: O(1) Auxiliary Space (excluding the space needed for the output string).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/easy-string2212/1
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    string transform(string S) {
        string ans = "";
        int n = S.length();
        int count = 1;
        
        for (int i = 0; i < n; i++) {
            // Check if current char matches the next char (case-insensitive)
            if (i < n - 1 && tolower(S[i]) == tolower(S[i + 1])) {
                count++;
            } else {
                // Append the count
                ans += to_string(count);
                // Append the lowercase character
                ans += tolower(S[i]);
                
                // Reset count for the next sequence of characters
                count = 1;
            }
        }
        
        return ans;
    }
};
