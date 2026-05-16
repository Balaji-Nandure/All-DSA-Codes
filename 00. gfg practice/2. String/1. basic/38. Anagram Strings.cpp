/*
Problem: Anagram Strings

GFG: https://www.geeksforgeeks.org/problems/anagram-strings/1

Description:
Given two strings S1 and S2, return "1" if both are anagrams, else return "0".

Examples:

Input: S1 = "cdbkdub", S2 = "dsbkcsdn"
Output: "0"

Input: S1 = "geeks", S2 = "skgee"
Output: "1"

Constraints:
1 <= |S1| <= 1000
1 <= |S2| <= 1000

Approach (Frequency Count):
Two strings are anagrams if they have the same length and same character
frequencies.

Key insight:
- Different lengths can never be anagrams
- Same lengths are anagrams iff every character count matches

Algorithm:
1. If lengths differ, return "0"
2. Create frequency array for characters
3. Increment counts for S1 and decrement for S2
4. If any count is non-zero, return "0"
5. Otherwise return "1"

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Hashing / Frequency Counting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
FREQUENCY COUNT APPROACH
=====================================================

TC: O(n)
SC: O(1)

FREQUENCY CHECK
- Count characters of first string
- Remove characters of second string
- All final counts must be zero
*/

// User function Template for C++
class Solution {
  public:
    int areAnagram(string S1, string S2) {
        // code here
        if(S1.size() != S2.size()) return 0;
        
        vector<int> freq(26, 0);
        for(char c: S1){
            freq[c - 'a']++;
        }
        
        for(char c: S2){
            freq[c - 'a']--;
            if(freq[c - 'a'] < 0) return 0;
            
        }

        return 1;
    }
};
