#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Ugly Number II
LeetCode 264: https://leetcode.com/problems/ugly-number-ii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/ugly-numbers2254/1

An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
Given an integer n, return the nth ugly number.

Constraints:
- 1 <= n <= 1690

Example:
n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.

Key Insight:
- Every ugly number (except 1) is formed by multiplying a previous ugly number by 2, 3, or 5
- Use three pointers to track which ugly number to multiply by each prime factor
- Always pick the minimum of the three candidates to maintain sorted order
- This ensures we generate ugly numbers in increasing order

DP State:
- dp[i] = the (i+1)th ugly number

Recurrence Relation:
- dp[i] = min(dp[p2] * 2, dp[p3] * 3, dp[p5] * 5)
- Where p2, p3, p5 are pointers to the last ugly number used for each prime factor
- After selecting minimum, increment the pointer(s) that produced it

Base Cases:
- dp[0] = 1 (first ugly number)

Time Complexity: O(n)
Space Complexity: O(n) for DP array
*/

// Approach 1: Pure Recursion (inefficient, but for understanding)
class Solution1_Recursion {
public:
    // TC: O(3^n) exponential, SC: O(n) recursion stack
    bool isUgly(int num) {
        if (num == 1) return true;
        if (num <= 0) return false;
        
        // Check if divisible by 2, 3, or 5
        if (num % 2 == 0) return isUgly(num / 2);
        if (num % 3 == 0) return isUgly(num / 3);
        if (num % 5 == 0) return isUgly(num / 5);
        
        return false;
    }
    
    int nthUglyNumber(int n) {
        int count = 0;
        int num = 1;
        
        // Keep checking numbers until we find nth ugly number
        while (count < n) {
            if (isUgly(num)) {
                count++;
            }
            if (count == n) return num;
            num++;
        }
        return num;
    }
};

// Approach 3: Tabulation (same as memoization for this problem)
class Solution3_Tabulation {
public:
    // TC: O(n), SC: O(n) for DP array
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0] = 1; // Base case
        
        // Pointers for each prime factor
        int p2 = 0, p3 = 0, p5 = 0;
        
        for (int i = 1; i < n; i++) {
            // Generate next candidates
            int candidate2 = dp[p2] * 2;
            int candidate3 = dp[p3] * 3;
            int candidate5 = dp[p5] * 5;
            
            // Select minimum
            dp[i] = min({candidate2, candidate3, candidate5});
            
            // Move pointers forward (handle duplicates by incrementing all that match)
            if (dp[i] == candidate2) p2++;
            if (dp[i] == candidate3) p3++;
            if (dp[i] == candidate5) p5++;
        }
        
        return dp[n - 1];
    }
};
