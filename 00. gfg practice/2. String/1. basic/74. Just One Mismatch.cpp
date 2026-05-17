/*
Problem: Just One Mismatch
Difficulty: Basic

Given a string S and array of strings, find whether the array contains a string with one character different from the given string.

Example 1:
Input :
N = 4
arr[] = {"bana","apple","banaba","bonanzo"}
S = "banana"
Output : True
Explanation: banana and banaba has only one character different.

Example 2:
Input:
N = 4
arr[] = {"bana","apple","banaba","bonanzo"}
S = "apple"
Output : False
Explanation: No string in arr differ by one character from S 

Your Task: 
You don't need to read input or print anything. Your task is to complete the function isStringExist() which takes the string array arr[], its size N and a string S as input parameters and returns "True" if a string exists in arr which has only one character different from S else return "False".

Expected Time Complexity: O(N * Length of the string S)
Expected Space Complexity: O(1)

Constraints :
1 <= N <= 100
1 <= |arr[i]| <= 1000
1 <= |S| <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(N * |S|)
    // SC: O(1)
    string isStringExist(vector<string> arr, int N, string S) {
        for (int i = 0; i < N; i++) {
            // Strings must be of the exact same length to differ by just one character
            if (arr[i].length() == S.length()) {
                int mismatchCount = 0;
                
                for (int j = 0; j < S.length(); j++) {
                    if (arr[i][j] != S[j]) {
                        mismatchCount++;
                    }
                    // Optimization: stop checking if there's more than 1 mismatch
                    if (mismatchCount > 1) {
                        break;
                    }
                }
                
                // If exactly 1 character is different, return True
                if (mismatchCount == 1) {
                    return "True";
                }
            }
        }
        
        return "False";
    }
};
