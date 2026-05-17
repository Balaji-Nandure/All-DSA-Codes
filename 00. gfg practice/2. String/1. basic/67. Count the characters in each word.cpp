/*
Problem: Count the characters in each word in a given sentence
Difficulty: Basic

Given a string containing multiple words, count the characters in each word and display them.

Example 1:
Input:
S = "the quick brown fox"
Output: 3 5 5 3

Example 2:
Input: 
S = "geeks for geeks"
Output: 5 3 5

Your Task:
complete the function countChars() which takes the string S as inputs are returns an array containing the number of characters in each word of the string in the order as they appear in the input string S.

Expected Time Complexity: O(|S|).
Expected Auxiliary Space: O(|S|) (for output).

Constraints:
1 <= |S| <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(|S|)
    // SC: O(|S|)
    vector<int> countChars(string s) {
        vector<int> res;
        stringstream ss(s);
        string word;
        
        while (ss >> word) {
            res.push_back(word.length());
        }
        
        return res;
    }
};
