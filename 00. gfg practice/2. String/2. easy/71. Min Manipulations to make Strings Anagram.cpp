/*
Problem: Min Manipulations to make Strings Anagram

Given two strings in lowercase, your task is to find minimum number of manipulations required to make two strings anagram without deleting any character. If two strings contains same data set in any order then strings are called Anagrams.

Constraints:
1 <= N <= 10^5
|S1| = |S2| = N

--------------------------------------------------

Pattern:
String Processing + Hashing / Frequency Array

--------------------------------------------------

Key Observation:
- Since both strings have the same length `N`, the minimum manipulations required is simply the number of characters in `S2` that cannot be matched with any character in `S1`.
- For every unmatched character in `S2`, we can simply replace it with one of the missing characters from `S1`.
- Thus, we just need to count how many characters in `S2` are "extra" compared to the character frequencies in `S1`.

--------------------------------------------------

Approach:
1. Initialize a frequency array `count` of size 26 to 0.
2. Iterate through the first string `S1` and increment the count for each character.
3. Initialize an `ans` counter to 0.
4. Iterate through the second string `S2`.
5. For each character `c` in `S2`, check if its frequency in `count` is greater than 0:
   a. If it is, decrement the count (indicating we matched this character).
   b. If it is 0, it means this character is "extra" in `S2` and must be changed. Increment `ans`.
6. Return `ans`.

--------------------------------------------------

Time Complexity: O(N) as we iterate through both strings of length N.
Space Complexity: O(1) as we only use a fixed size array of 26 integers to store character counts.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/min-manipulations-to-make-strings-anagram5326/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minManipulation(int N, string S1, string S2) {
        vector<int> count(26, 0);
        
        for (char c : S1) {
            count[c - 'a']++;
        }
        
        int ans = 0;
        for (char c : S2) {
            if (count[c - 'a'] > 0) {
                count[c - 'a']--;
            } else {
                ans++;
            }
        }
        
        return ans;
    }
};
