/*
Problem: The Muskteers
Difficulty: Basic

Given binary string str consisting of only 0's and 1's, Check if all the 0's are together or not.

Example 1:
Input:
str = "000"
Output: YES
Explanation: All the 0's are together.

Example 2:
Input:
str = "111"
Output: NO
Explanation: All the 0's are not together.

Your Task:  
You don't need to read input or print anything. Your task is to complete the function checkTogether() which takes the binary string str as an input parameter and returns 1 if all the 0's are together else returns 0.

Expected Time Complexity: O(N), Where N is the size of the string.
Expected Auxiliary Space: O(1)

Constraints:
1 <= |str| <= 10000
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(N)
    // SC: O(1)
    int checkTogether(string str) {
        int zeroBlocks = 0;
        bool inZeroBlock = false;
        
        for (char c : str) {
            if (c == '0') {
                if (!inZeroBlock) {
                    zeroBlocks++;
                    inZeroBlock = true;
                }
            } else {
                inZeroBlock = false;
            }
        }
        
        // If there is exactly one continuous block of 0's, they are together.
        // If zeroBlocks == 0 (no 0's like "111"), it correctly returns 0 (NO).
        return zeroBlocks == 1 ? 1 : 0;
    }
};
