/*
Problem: Message decoding
Difficulty: Basic

Given a string S, check whether it can be converted into the string "hello" by deleting some characters from it.
Note : S can have both uppercase and lowercase letters.

Example 1:
Input:
S = "bbbbbxxhhelllllooudd"
Output: 1
Explanation: The string hello is marked in bold: bbbbbxxhhelllllooudd

Example 2:
Input: 
S = "hlelo"
Output: 0
Explanation: It's impossible to convert the given string into "hello".

Your Task:
You don't need to read input or print anything. Your task is to complete the function decode() which takes the string S as input and returns the true if the string can be converted to "hello", else return false.

Expected Time Complexity: O(|S|).
Expected Auxiliary Space: O(1).

Constraints:
1 <= |S| <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(|S|)
    // SC: O(1)
    bool decode(string s) {
        string target = "hello";
        int targetIdx = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // If the character matches the current required character in "hello"
            if (s[i] == target[targetIdx]) {
                targetIdx++;
                
                // If we have successfully found all characters of "hello" in order
                if (targetIdx == target.length()) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
