/*
Problem: Most Frequent Character

GFG: https://www.geeksforgeeks.org/problems/most-frequent-character-in-a-string0352/1

Description:
Given a string s of lowercase alphabets, find the maximum occurring character.
If tie, return the lexicographically smaller character.

Examples:

Input: s = "testsample"  Output: 'e'
Input: s = "output"      Output: 't'  (t and u both freq 2, t < u)

Constraints:
1 ≤ |s| ≤ 100

Approach (Frequency Array):
- Count freq of each char using array[26]
- Iterate a-z (lexicographic order), track max freq
- Since we go a→z, first max found is automatically lexicographically smallest

Dry Run: s = "output"
  Freq: o=1 u=2 t=2 p=1
  Iterate a→z: ... o(1) p(1) ... t(2)→maxChar='t' ... u(2) not > 2 → skip
  Result: 't' ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1)
    char getMaxOccurringChar(string& s) {

        int freq[26] = {0};

        for(char ch : s) freq[ch - 'a']++;

        int maxFreq = 0;
        char result = 'a';

        for(int i = 0; i < 26; i++) {
            if(freq[i] > maxFreq) {
                maxFreq = freq[i];
                result = 'a' + i;
            }
        }

        return result;
    }
};
