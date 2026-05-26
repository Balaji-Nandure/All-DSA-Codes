/*
GeeksforGeeks: License Key Formatting
Difficulty: Easy

Given a string S that consists of only alphanumeric characters and dashes. The string is separated into N + 1 groups by N dashes. Also given an integer K. 

We want to reformat the string S, such that each group contains exactly K characters, except for the first group, which could be shorter than K but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted string.

Example 1:

Input: 
S = "5F3Z-2e-9-w", K = 4
Output: "5F3Z-2E9W"
Explanation: The string S has been split into two
parts, each part has 4 characters. Note that two
extra dashes are not needed and can be removed.

Example 2:

Input:
S = "2-5g-3-J", K = 2
Output: "2-5G-3J"
Explanation: The string s has been split 
into three parts, each part has 2 characters 
except the first part as it could
be shorter as mentioned above.

Constraints:
1 <= S.length() <= 10^5
1 <= K <= 10^4
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Problem: License Key Formatting
     * 
     * Reformat S into groups of K characters (except the first group), 
     * separated by dashes, and convert all letters to uppercase.
     * 
     * Time Complexity: O(N) - single pass from right to left, plus string reversal
     * Space Complexity: O(N) - auxiliary space to store the reformatted string
     */
    string ReFormatString(string S, int K) {
        string res = "";
        int count = 0;
        
        // Traverse S from right to left
        for (int i = S.length() - 1; i >= 0; i--) {
            if (S[i] != '-') {
                // If we already filled a group of K characters, append a dash before starting the next group
                if (count == K) {
                    res += '-';
                    count = 0;
                }
                res += toupper(S[i]);
                count++;
            }
        }
        
        // Reverse the result since we constructed it backwards
        reverse(res.begin(), res.end());
        return res;
    }
};

/*
Approach: Right-to-Left Traversal
- Since the first group is allowed to be shorter than K characters, all other groups (starting from the right) must have exactly K characters.
- It is much easier to format the string by processing it from right to left.
- We iterate through the input string `S` backwards:
  1. Skip any dashes (`'-'`).
  2. For alphanumeric characters, if we have already accumulated `K` characters in the current group, we append a dash (`'-'`) to our result and reset our group counter.
  3. We then convert the character to uppercase using `toupper()` and append it to our result string, incrementing the group counter.
- Since we processed the string backwards, the result string `res` is built in reverse order. We reverse `res` at the end to get the correct output.

Complexity:
- Time Complexity: O(N) where N is the length of string `S`, as we iterate through the string once and reverse it.
- Space Complexity: O(N) auxiliary space to store the output string.
*/
