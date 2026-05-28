/*
Problem: Count Alphabets

Given a string, The task is to count the number of alphabets present in the string.

Constraints:
1 <= |S| <= 10^5
S contains only upper and lower case alphabets, digits and '#', '!', '$', '&' only.

--------------------------------------------------

Pattern:
String Processing

--------------------------------------------------

Key Observation:
- We need to count the characters that are either lowercase or uppercase English letters.
- The standard library provides `isalpha()` in `<cctype>` which checks if a given character is an alphabet.

--------------------------------------------------

Approach:
1. Initialize a counter `cnt` to 0.
2. Iterate through each character `c` in the string `S`.
3. If `isalpha(c)` returns true, increment the counter `cnt`.
4. Return `cnt`.

--------------------------------------------------

Time Complexity: O(|S|) as we iterate through the string once.
Space Complexity: O(1) as we only use a single counter variable.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/count-alphabets3649/1
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    int Count(string S) {
        int cnt = 0;
        for (char c : S) {
            if (isalpha(c)) {
                cnt++;
            }
        }
        return cnt;
    }
};
