/*
Problem:
Given a string consisting of lowercase english alphabets.
Find the first repeating character in the string.

Return:
- First repeating character
- If no repeating character exists, return '#'

Example:
Input:  "geeksforgeeks"
Output: 'g'

Input:  "abcde"
Output: '#'

Approach:
1. Count frequency of every character.
2. Traverse string again from left to right.
3. First character whose frequency > 1 is the answer.

Why this works?
- Frequency array tells how many times each character appears.
- First character with count > 1 is the first repeating character.

Pattern:
Frequency Counting / Hashing

Time Complexity: O(N)
Space Complexity: O(1)   // only 26 lowercase letters

GFG Link:
https://www.geeksforgeeks.org/problems/repeated-character2058/1
*/

class Solution {
public:

    char firstRep(string s) {

        // Frequency array for lowercase letters
        int freq[26] = {0};

        // Count frequency of every character
        for(char ch : s) {
            freq[ch - 'a']++;
        }

        // Find first repeating character
        for(char ch : s) {

            if(freq[ch - 'a'] > 1) {
                return ch;
            }
        }

        // No repeating character found
        return '#';
    }
};

/*
Summary:
- First count frequencies
- Then scan again to find first character with freq > 1
- Very common hashing pattern
*/