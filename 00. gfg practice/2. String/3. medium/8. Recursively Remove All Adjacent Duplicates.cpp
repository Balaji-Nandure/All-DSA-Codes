/*
GeeksforGeeks: Recursively Remove All Adjacent Duplicates
Difficulty: Medium

Problem:
Given a string s, remove all its adjacent duplicate characters recursively, until there are no adjacent duplicate characters left.
Note: If the resultant string becomes empty, return an empty string.

Examples:
Input: s = "geeksforgeek"
Output: "gksforgk"
Explanation: g(ee)ksforg(ee)k -> gksforgk

Input: s = "abccbccba"
Output: ""
Explanation: ab(cc)b(cc)ba -> abbba -> a(bbb)a -> aa -> (aa) -> "" (empty string)

Input: s = "abcd"
Output: "abcd"
Explanation: There are no adjacent duplicate characters

Core Idea:
In each iteration/pass, we traverse the string from left to right. Whenever we find a group of two or more adjacent identical characters, we skip the entire group. Characters that do not have adjacent identical matches are preserved.
If any duplicates were removed during a pass, the string has changed, and we must perform the process again recursively because the removal of duplicates could have brought new identical characters together (e.g., "abbba" -> "aa").
If a full pass is completed without finding any adjacent duplicates, the string is fully reduced, and we return it.

Approach:
1. Initialize a string `temp = ""` to build the reduced version of `s` and a boolean `hasDuplicates = false`.
2. Iterate `i` from `0` to `n - 1`:
   - If `s[i] == s[i + 1]`, we have found a duplicate sequence. Set `hasDuplicates = true`.
   - Store the duplicate character `dupChar = s[i]`, and advance `i` as long as `s[i] == dupChar` to skip all contiguous duplicate occurrences.
   - Otherwise, append `s[i]` to `temp` and increment `i`.
3. If `hasDuplicates` is true, return `rremove(temp)`.
4. Otherwise, return `temp` (or `s`).

Time Complexity: O(N) average case, O(N^2) in the worst case (e.g., "abcdefgfedcba"). With GFG limits, this recursive reduction passes within limits.
Space Complexity: O(N) due to recursion stack depth and temporary string copies.

GFG Link: https://www.geeksforgeeks.org/problems/recursively-remove-all-adjacent-duplicates0744/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string rremove(string s) {
        string temp = "";
        int n = s.length();
        int i = 0;
        bool hasDuplicates = false;
        
        while (i < n) {
            // Check if the current character is part of a duplicate group
            if (i < n - 1 && s[i] == s[i + 1]) {
                hasDuplicates = true;
                char dupChar = s[i];
                // Skip all adjacent occurrences of this duplicate character
                while (i < n && s[i] == dupChar) {
                    i++;
                }
            } else {
                temp += s[i];
                i++;
            }
        }
        
        // If we found and removed any duplicates, recurse on the remaining string
        if (hasDuplicates) {
            return rremove(temp);
        }
        
        return temp;
    }
};

/*
Dry Run — Example:
s = "abccbccba"

Pass 1:
- i = 0: s[0]='a' != s[1]='b' -> temp = "a", i = 1
- i = 1: s[1]='b' != s[2]='c' -> temp = "ab", i = 2
- i = 2: s[2]='c' == s[3]='c' -> hasDuplicates = true, skip all 'c's starting at 2 -> i becomes 4
- i = 4: s[4]='b' != s[5]='c' -> temp = "abb", i = 5
- i = 5: s[5]='c' == s[6]='c' -> hasDuplicates = true, skip all 'c's starting at 5 -> i becomes 7
- i = 7: s[7]='b' != s[8]='a' -> temp = "abbb", i = 8
- i = 8: s[8]='a' (end of string) -> temp = "abbba", i = 9
Since hasDuplicates was true, recurse with s = "abbba"

Pass 2:
s = "abbba"
- i = 0: s[0]='a' != s[1]='b' -> temp = "a", i = 1
- i = 1: s[1]='b' == s[2]='b' -> hasDuplicates = true, skip all 'b's starting at 1 -> i becomes 4
- i = 4: s[4]='a' (end of string) -> temp = "aa", i = 5
Since hasDuplicates was true, recurse with s = "aa"

Pass 3:
s = "aa"
- i = 0: s[0]='a' == s[1]='a' -> hasDuplicates = true, skip all 'a's starting at 0 -> i becomes 2
Since hasDuplicates was true, recurse with s = ""

Pass 4:
s = ""
Loop doesn't run. hasDuplicates is false. Returns "".
Final Output: ""
*/
