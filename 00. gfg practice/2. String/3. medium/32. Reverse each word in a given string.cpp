/*
GeeksforGeeks: Reverse each word in a given string
Difficulty: Medium

Problem:
You are given a string s. You need to reverse each word in it where the words are separated by spaces 
and return the modified string.
Note: The string may contain leading or trailing spaces, or multiple spaces between two words. 
The returned string should only have a single space separating the words, and no extra spaces should be included.

Examples:
Input: s = " i like this program very much "
Output: "i ekil siht margorp yrev hcum"
Explanation: The words are reversed as follows:
             "i" -> "i", "like" -> "ekil", "this" -> "siht", "program" -> "margorp", "very" -> "yrev", "much" -> "hcum".

Input: s = " pqr mno "
Output: "rqp onm"

Input: s = "pqr"
Output: "rqp"

Constraints:
1 <= s.length() <= 10^5
s contains only lowercase English alphabets and spaces.

Core Idea:
- We traverse the string character by character.
- We accumulate non-space characters into a temporary string `word`.
- When a space ' ' is encountered:
  - If `word` is not empty (which means we have just completed a word):
    - Reverse `word` using `reverse()`.
    - If our `result` string already has words in it, append a single space " " to separate them.
    - Append the reversed `word` to `result`.
    - Clear `word` to prepare for the next word.
- After the loop completes, there might be one final word in `word` (if the input did not end with a trailing space). 
  We check if `word` is not empty, and if so, reverse and append it.
- This approach handles:
  1. Leading spaces (since `word` will remain empty until we hit the first character).
  2. Trailing spaces (since any trailing spaces will just trigger a check where `word` is empty).
  3. Multiple consecutive spaces (since the first space processes the word, and subsequent spaces see an empty `word` and are ignored).
  This naturally produces a single-spaced, cleanly formatted output string.

Approach:
1. Initialize `result = ""` and `word = ""`.
2. Loop through `char c : s`:
   - If `c != ' '`, `word.push_back(c)`.
   - Else (if `c == ' '`):
     - If `!word.empty()`:
       - `reverse(word.begin(), word.end())`
       - If `!result.empty()`, `result += " "`.
       - `result += word`
       - `word.clear()`
3. After loop, if `!word.empty()`:
   - `reverse(word.begin(), word.end())`
   - If `!result.empty()`, `result += " "`.
   - `result += word`
4. Return `result`.

Time Complexity: O(N) where N is the length of string s. We iterate through the string once and reverse each word in-place.
Space Complexity: O(N) to store and return the result string.

GFG Link: https://www.geeksforgeeks.org/problems/reverse-each-word-in-a-given-string1001/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string result = "";
        string word = "";
        
        for (char c : s) {
            if (c != ' ') {
                word.push_back(c);
            } else {
                if (!word.empty()) {
                    reverse(word.begin(), word.end());
                    if (!result.empty()) {
                        result += " ";
                    }
                    result += word;
                    word.clear();
                }
            }
        }
        
        // Handle the final word if it exists
        if (!word.empty()) {
            reverse(word.begin(), word.end());
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }
        
        return result;
    }
};

/*
Dry Run — Example:
s = " pqr mno "

1. Initialize result = "", word = ""
2. Iterate c through s:
   - c = ' ' : word is empty -> do nothing.
   - c = 'p' : word = "p"
   - c = 'q' : word = "pq"
   - c = 'r' : word = "pqr"
   - c = ' ' : word is "pqr" (not empty)
     - reverse("pqr") -> "rqp"
     - result is empty -> result = "rqp"
     - word cleared -> ""
   - c = 'm' : word = "m"
   - c = 'n' : word = "mn"
   - c = 'o' : word = "mno"
   - c = ' ' : word is "mno" (not empty)
     - reverse("mno") -> "onm"
     - result is not empty -> result = "rqp" + " " + "onm" = "rqp onm"
     - word cleared -> ""

3. Loop ends. word is empty.
4. Return result: "rqp onm"
*/
