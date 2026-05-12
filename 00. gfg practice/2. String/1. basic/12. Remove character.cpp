/*
Problem:
Remove vowels from string

Example:
Input: s = "welcome to geeksforgeeks"
Output: "wlcm t gksfrgks"

Input: s = "what is your name ?"
Output: "wht s yr nm ?"

Approach:
1. Create a set/hash of vowels.
2. Traverse the string.
3. Keep only characters that are not vowels.

Why this works?
- Hash lookup for vowels is O(1).
- We preserve original order of consonants.
- Handles spaces and special characters.

Pattern:
Hashing / Filtering

Time Complexity: O(N)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/remove-vowels-from-string4430/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string removeChars(string str1, string str2) {

        // Mark characters present in str2
        int freq[26] = {0};

        for(char ch : str2) {
            freq[ch - 'a'] = 1;
        }

        string ans = "";

        // Keep only characters not in str2
        for(char ch : str1) {

            if(freq[ch - 'a'] == 0) {
                ans += ch;
            }
        }

        return ans;
    }
};

/*
Summary:
- Store removable characters
- Traverse str1
- Keep only safe characters
*/
