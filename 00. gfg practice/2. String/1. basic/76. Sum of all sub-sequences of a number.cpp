/*
Problem: Sum of all sub-sequences of a number

GFG: https://www.geeksforgeeks.org/problems/sum-of-all-sub-sequences-of-a-number/1

Description:
Given a number as string S, find sum of all elements present in all possible
non-empty subsequences.

Examples:

Input: S = "123"
Output: 24

Input: S = "5"
Output: 5

Approach:
Each digit appears in exactly 2^(n-1) subsequences (choose include/exclude for
remaining n-1 positions). So:

answer = (sum of digits) * 2^(n-1)

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    long long subsequenceSum(string S) {

        long long digitSum = 0;
        for(char ch : S) {
            digitSum += (ch - '0');
        }

        long long ways = 1LL << ((int)S.size() - 1);
        return digitSum * ways;
    }
};
