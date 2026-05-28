/*
Problem: Maximum number of characters between any two same character

Given a string containing lower and uppercase alphabets, the task is to find the maximum number of characters between any two same (case sensitivity) character in the string.

Constraints:
1 <= |S| <= 10^5

--------------------------------------------------

Pattern:
String Processing + Hashing (First Occurrence Array)

--------------------------------------------------

Key Observation:
- We want to maximize the number of characters strictly between two identical characters. This is equivalent to finding the maximum of `j - i - 1` such that `S[i] == S[j]` and `i < j`.
- To maximize `j - i - 1` for a specific character, we should pick `i` as the first occurrence of that character, and `j` as the current (or last) occurrence.
- Since characters are ASCII values, we can simply maintain an array of size 256 to record the very first time we see each character.

--------------------------------------------------

Approach:
1. Initialize an array `firstOcc` of size 256 to `-1`. This will store the first observed index of each character.
2. Initialize a variable `maxDist` to `-1` to store the maximum distance found so far.
3. Iterate through the string `S` with index `i` from 0 to `|S| - 1`:
    a. If `firstOcc[S[i]]` is `-1`, it means this is the first time we've encountered this character. We update `firstOcc[S[i]] = i`.
    b. If `firstOcc[S[i]]` is not `-1`, it means we've seen this character before. We calculate the distance as `i - firstOcc[S[i]] - 1` and update `maxDist` if this distance is greater than the current `maxDist`.
4. Return `maxDist`. (If no repeating characters were found, it naturally returns the initialized `-1`).

--------------------------------------------------

Time Complexity: O(|S|) as we iterate over the string exactly once.
Space Complexity: O(1) as we use a fixed size array of 256 integers.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/maximum-number-of-characters-between-any-two-same-character4336/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxChars(string s) {
        int maxDist = -1;
        vector<int> firstOcc(256, -1);
        
        for (int i = 0; i < s.length(); ++i) {
            unsigned char c = s[i];
            if (firstOcc[c] == -1) {
                firstOcc[c] = i;
            } else {
                maxDist = max(maxDist, i - firstOcc[c] - 1);
            }
        }
        
        return maxDist;
    }
};
