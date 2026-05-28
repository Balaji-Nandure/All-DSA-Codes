/*
Problem: Panagram Checking

Given a string s, check if it is a "Panagram" or not. Return true if the string is a Panagram, else return false.
A "Panagram" is a sentence containing every letter in the English Alphabet either in lowercase or Uppercase.

Constraints:
1 <= |s| <= 10^4
s consists only lowercase and uppercase letters

--------------------------------------------------

Pattern:
String Processing + Hashing / Frequency Array

--------------------------------------------------

Key Observation:
- We need to check if all 26 letters of the English alphabet are present in the string.
- Case does not matter (A is the same as a).
- We can keep track of the letters we've seen using a boolean array of size 26.
- A counter can be used to track the number of unique letters seen. If the counter reaches 26, it's a panagram.

--------------------------------------------------

Approach:
1. Initialize a boolean array `present` of size 26 to false, and a counter `cnt` to 0.
2. Iterate through each character `c` in the string `s`.
3. If `c` is an alphabet character, convert it to lowercase and find its index (0 to 25).
4. If `present[index]` is false, mark it as true and increment `cnt`.
5. Return whether `cnt` is equal to 26.

--------------------------------------------------

Time Complexity: O(|s|) as we iterate through the string.
Space Complexity: O(1) as the boolean array size is fixed at 26.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/pangram-checking-1587115620/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Solution {
public:
    // Function to check if a string is Pangram or not.
    bool checkPangram(string s) {
        vector<bool> present(26, false);
        int cnt = 0;
        
        for (char c : s) {
            if (isalpha(c)) {
                int idx = tolower(c) - 'a';
                if (!present[idx]) {
                    present[idx] = true;
                    cnt++;
                }
            }
        }
        
        return cnt == 26;
    }
};
