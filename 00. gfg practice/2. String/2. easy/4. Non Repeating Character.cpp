/*
Problem: Non Repeating Character

GFG: https://www.geeksforgeeks.org/problems/non-repeating-character-1587115620/1

Description:
Given a string s of lowercase English letters, return the first non-repeating character.
If there is no non-repeating character, return '$'.

Examples:

Input: s = "geeksforgeeks"  Output: 'f'
Input: s = "racecar"        Output: 'e'
Input: s = "aabbccc"        Output: '$'

Constraints:
1 ≤ s.size() ≤ 10^5

Approach (Frequency Array):
- Count frequency of each char in one pass
- Second pass: return first char with freq == 1
- freq array of size 26 → O(1) space

Dry Run: s = "geeksforgeeks"
  Freq: g=2 e=4 k=2 s=2 f=1 o=1 r=1
  Second pass: g(2)→skip, e(4)→skip, e→skip, k(2)→skip, s(2)→skip, f(1)→return 'f' ✅

Time Complexity: O(n)
Space Complexity: O(1) — fixed 26-size array
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1)
    char nonRepeatingChar(string& s) {

        int freq[26] = {0};

        for(char ch : s) freq[ch - 'a']++;

        for(char ch : s) {
            if(freq[ch - 'a'] == 1) return ch;
        }

        return '$';
    }
};
