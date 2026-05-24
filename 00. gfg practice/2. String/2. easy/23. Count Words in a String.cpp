/*
Problem: Count Words in a String

GFG: https://www.geeksforgeeks.org/problems/count-words-in-a-string/1

Description:
Given a string s containing:
- lowercase letters
- spaces
- '\n'
- '\t'

Count total number of words.

A word:
- continuous sequence of lowercase letters

Separators:
- space
- newline '\n'
- tab '\t'

Examples:

Input: s = "abc def"
Output: 2

Explanation:
"abc" and "def"

--------------------------------------------------

Input: s = "a\nyo\t"
Output: 2

Explanation:
Words are:
"a" and "yo"

Constraints:
2 ≤ s.size() ≤ 10^6

Approach:
- Traverse string
- Detect starting character of every word

A character starts a new word if:
- current char is alphabet
AND
- previous char is separator
  OR current char is first character

Dry Run:
s = "abc def"

i=0 -> 'a'
start of word → cnt=1

i=4 -> 'd'
previous char was space
new word → cnt=2

Answer = 2 ✅

--------------------------------------------------

Dry Run:
s = "a\nyo\t"

'a' -> new word → cnt=1

'y' -> previous char '\n'
new word → cnt=2

Answer = 2 ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    int countWords(string s) {

        int cnt = 0;
        int n = s.size();

        for(int i = 0; i < n; i++) {

            // Current char is alphabet
            if(s[i] >= 'a' && s[i] <= 'z') {

                // Start of new word
                if(i == 0 || s[i - 1] == ' ' || 
                   s[i - 1] == '\n' || s[i - 1] == '\t') {

                    cnt++;
                }
            }
        }

        return cnt;
    }
};