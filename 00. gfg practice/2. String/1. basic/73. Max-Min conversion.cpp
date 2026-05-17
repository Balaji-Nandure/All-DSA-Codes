/*
Problem: Max-Min conversion
Difficulty: Basic

Given a number N. You can perform an operation on it multiple times, in which you can change digit 5 to 6 and vice versa.
You have to return the sum of the maximum number and the minimum number which can be obtained by performing such operations.

Example 1:
Input: N = 35
Output: 71
Explanation: The maximum number which can be
formed is 36 and the minimum number which can
be formed is 35 itself. 

Example 2:
Input: N = 22
Output: 44
Explanation: The maximum number and minimum
number which can be formed is 22 itself.

Your Task:
You need not take any input or print anything. Your task is to complete the function performOperation() which takes a single Number as input and returns the sum of maximum and minimum number.

Expected Time Complexity: O(Log10N)
Expected Auxiliary Space: O(Log10N) (or O(1) if optimized)

Constraints:
1 <= N <= 10^18
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(Log10N)
    // SC: O(Log10N)
    long long performOperation(long long N) {
        string s = to_string(N);
        string min_str = s;
        string max_str = s;
        
        for (int i = 0; i < s.length(); i++) {
            if (min_str[i] == '6') min_str[i] = '5';
            if (max_str[i] == '5') max_str[i] = '6';
        }
        
        return stoll(max_str) + stoll(min_str);
    }
};
