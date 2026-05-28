/*
Problem: Minimum changes to make all substrings distinct

Given a string s consisting only lower case alphabets, find the minimum number of changes required to it so that all substrings of the string become distinct.
Note: length of the string is at most 26.

Constraints:
1 <= |S| <= 26

--------------------------------------------------

Pattern:
String Processing + Hashing / Frequency Array

--------------------------------------------------

Key Observation:
- For all substrings to be distinct, a necessary and sufficient condition is that all individual characters (substrings of length 1) must be distinct.
- If all characters in the string are unique, any two substrings starting at different indices will be different starting from their very first character.
- Therefore, the problem reduces to finding the minimum number of character changes to make all characters in the string unique.
- Since the length is at most 26, it's always possible to replace duplicate characters with unused letters from the alphabet.
- The number of changes required is exactly the total length of the string minus the number of unique characters already present.

--------------------------------------------------

Approach:
1. Initialize a boolean array `present` of size 26 to `false` and a counter `uniqueCnt` to 0.
2. Iterate through each character `c` in the string `S`.
3. Check if `present[c - 'a']` is `false`. If so, mark it `true` and increment `uniqueCnt`.
4. The minimum number of changes needed is simply `S.length() - uniqueCnt`.
5. Return this value.

--------------------------------------------------

Time Complexity: O(|S|) as we iterate through the string of length at most 26 exactly once.
Space Complexity: O(1) or O(26) as we use a fixed size boolean array of length 26.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/minimum-changes-to-make-all-substrings-distinct/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minChange(string S) {
        vector<bool> present(26, false);
        int uniqueCnt = 0;
        
        for (char c : S) {
            int idx = c - 'a';
            if (!present[idx]) {
                present[idx] = true;
                uniqueCnt++;
            }
        }
        
        return S.length() - uniqueCnt;
    }
};
