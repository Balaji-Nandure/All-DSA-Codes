/*
Problem: Fake Profile

GFG: https://www.geeksforgeeks.org/problems/fake-profile/1

Description:
Given lowercase username a, ignore vowels and count distinct consonants.
- If count is odd  -> "HE!"
- If count is even -> "SHE!"

Examples:

Input: a = "jpmztf"
Output: "SHE!"

Input: a = "plkaitw"
Output: "HE!"

Constraints:
1 <= |a| <= 1000

Approach:
Use a 26-length visited array for distinct letters. Skip vowels while marking.

Time Complexity: O(|a|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    string solve(string a) {

        map<char, int> freq;

        for(char ch : a) {
            if(isVowel(ch)) {
                continue;
            }

            freq[ch]++;
        }

        int distinctConsonants = (int)freq.size();

        if(distinctConsonants % 2 == 1) {
            return "HE!";
        }

        return "SHE!";
    }
};
