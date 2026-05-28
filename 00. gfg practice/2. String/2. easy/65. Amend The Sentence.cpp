/*
Problem: Amend The Sentence

Given a string which is basically a sentence without spaces between words. However the first letter of every word is in uppercase. You need to print this sentence after following amendments:
(i) Put a single space between these words
(ii) Convert the uppercase letters to lowercase.
Note: The first character of the string can be both uppercase/lowercase.

Constraints:
1 <= Size of String <= 10^6

--------------------------------------------------

Pattern:
String Processing

--------------------------------------------------

Key Observation:
- A new word starts whenever we encounter an uppercase letter.
- The only exception is the first letter of the string, which may or may not be uppercase but shouldn't have a space before it regardless.
- We need to build a new string where uppercase letters are replaced by a space followed by their lowercase equivalent, and lowercase letters are simply appended.

--------------------------------------------------

Approach:
1. Initialize an empty string `ans`.
2. Iterate through each character in the string `s`.
3. Check if the character is uppercase using `isupper(s[i])`.
4. If it is uppercase:
    a. If it's not the first character (`i != 0`), append a space to `ans`.
    b. Convert it to lowercase using `tolower(s[i])` and append to `ans`.
5. If it is lowercase, simply append it to `ans`.
6. Return the constructed string `ans`.

--------------------------------------------------

Time Complexity: O(N) as we iterate through the string of size N exactly once.
Space Complexity: O(N) to store the amended output string.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/amend-the-sentence3235/1
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    string amendSentence(string s) {
        string ans = "";
        for (int i = 0; i < s.length(); ++i) {
            if (isupper(s[i])) {
                if (i != 0) {
                    ans += " ";
                }
                ans += tolower(s[i]);
            } else {
                ans += s[i];
            }
        }
        return ans;
    }
};
