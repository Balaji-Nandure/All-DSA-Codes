/*
GeeksforGeeks: Count the Reversals
Difficulty: Medium

Problem:
Given a string s consisting of only opening and closing curly brackets '{' and '}', 
find out the minimum number of reversals required to convert the string into a balanced expression. 
A reversal means changing '{' to '}' or vice-versa.
If the string cannot be balanced, return -1.

Examples:
Input: s = "}{{}}{{{"
Output: 3
Explanation: One way to balance is "{{{}}{}}". There is no balanced sequence that can be formed in lesser reversals.

Input: s = "{{}{{{}{{}}{{"
Output: -1
Explanation: The length is odd, so it's impossible to balance.

Constraints:
1 <= s.length() <= 10^5

Core Idea:
- First, if the length of the string is odd, it is impossible to balance it (as every open brace needs a matching close brace). Return -1.
- Next, we can filter out the already balanced pairs. For example, any substring "{}" is already balanced and does not contribute to reversals.
- Instead of using an actual stack, we can keep track of unmatched braces using two counters:
  - `open_count`: number of unmatched '{'
  - `close_count`: number of unmatched '}'
- We iterate through the string:
  - If we see '{', we increment `open_count`.
  - If we see '}':
    - If `open_count > 0`, it matches a previously unmatched '{'. So we decrement `open_count`.
    - Else (if `open_count == 0`), this '}' is unmatched. We increment `close_count`.
- After one pass, the remaining unmatched braces will look like:
  - `close_count` closing braces '}' followed by `open_count` opening braces '{'.
  - (e.g. "}}} {{" where close_count = 3, open_count = 2).
- To balance them:
  - Pairwise '}' can be balanced by reversing one: 2 closing braces need 1 reversal.
  - Pairwise '{' can be balanced by reversing one: 2 opening braces need 1 reversal.
  - If there is an odd number of '}' and '{' remaining, we'll be left with one of each: "}{". 
    To balance "}{", we need to reverse both braces to form "{}". This requires 2 reversals.
  - Mathematically, this maps to:
    Reversals = ceil(close_count / 2.0) + ceil(open_count / 2.0)
              = (close_count + 1) / 2 + (open_count + 1) / 2.

Approach:
1. If `s.length() % 2 != 0`, return -1.
2. Initialize `open_count = 0`, `close_count = 0`.
3. Loop through each character `c` in `s`:
   - If `c == '{'`, `open_count++`.
   - If `c == '}'`:
     - If `open_count > 0`, `open_count--`.
     - Else, `close_count++`.
4. Return `(close_count + 1) / 2 + (open_count + 1) / 2`.

Time Complexity: O(N) where N is the length of string s. We iterate through the string exactly once.
Space Complexity: O(1) auxiliary space as we only use two integer variables.

GFG Link: https://www.geeksforgeeks.org/problems/count-the-reversals0401/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int countMinReversals(string s) {
        // Step 1: If length is odd, it is impossible to balance
        if (s.length() % 2 != 0) {
            return -1;
        }
        
        int open_count = 0;  // Tracks unmatched '{'
        int close_count = 0; // Tracks unmatched '}'
        
        // Step 2: Eliminate already balanced "{}" pairs
        for (char c : s) {
            if (c == '{') {
                open_count++;
            } else { // c == '}'
                if (open_count > 0) {
                    open_count--; // Matches with the closest '{'
                } else {
                    close_count++; // Unmatched '}'
                }
            }
        }
        
        // Step 3: Calculate reversals needed for unmatched braces
        return (close_count + 1) / 2 + (open_count + 1) / 2;
    }
};

/*
Dry Run — Example:
s = "}{{}}{{{"
Length = 8 (even, valid to check)

Initial: open_count = 0, close_count = 0

1. c = '}' -> open_count == 0 -> close_count = 1
2. c = '{' -> open_count = 1
3. c = '}' -> open_count > 0 -> open_count = 0
4. c = '}' -> open_count == 0 -> close_count = 2
5. c = '{' -> open_count = 1
6. c = '{' -> open_count = 2
7. c = '{' -> open_count = 3
8. c = '{' -> open_count = 4

At end of loop: close_count = 2, open_count = 4 (corresponds to unmatched sequence: "}} {{{{")

Reversals = (close_count + 1) / 2 + (open_count + 1) / 2
          = (2 + 1) / 2 + (4 + 1) / 2
          = 1 + 2
          = 3

Output: 3
*/
