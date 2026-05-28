/*
Problem: Common Subsequence

Given two strings S1 and S2, check whether they have a common subsequence or not.
Note: A common subsequence exists if and only if the two strings share at least one common character.

Constraints:
1 <= |S1|, |S2| <= 10^5

--------------------------------------------------

Pattern:
String Processing + Hashing (Frequency Array)

--------------------------------------------------

Key Observation:
- A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.
- For two strings to have ANY common subsequence, they must share at least ONE common character. If they share a character, that single character itself constitutes a valid common subsequence of length 1!
- Thus, the entire problem reduces to simply checking if there is any intersection between the sets of characters in `S1` and `S2`.

--------------------------------------------------

Approach:
1. Initialize a boolean array `present` of size 256 (to cover all ASCII characters) to `false`.
2. Iterate through the first string `S1`. For each character `c`, mark `present[c] = true`.
3. Iterate through the second string `S2`. For each character `c`, check if `present[c]` is `true`.
4. If it is `true`, we immediately return `true` because we found a shared character.
5. If the loop finishes without finding any common characters, return `false`.

--------------------------------------------------

Time Complexity: O(|S1| + |S2|) since we traverse each string exactly once.
Space Complexity: O(1) Auxiliary Space (fixed size array of 256 booleans).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/common-subsequence-1587115620/1
*/

#include <iostream>
#include <string>
#include <array>

using namespace std;

class Solution {
public:
    bool commonSubseq(string s1, string s2) {
        if (s1.empty() || s2.empty()) return false;
        
        // Use an array of 256 booleans to represent character presence
        array<bool, 256> present{};
        
        // Mark all characters present in s1
        for (unsigned char c : s1) {
            present[c] = true;
        }
        
        // Check if any character in s2 is also in s1
        for (unsigned char c : s2) {
            if (present[c]) {
                return true;
            }
        }
        
        return false;
    }
};
