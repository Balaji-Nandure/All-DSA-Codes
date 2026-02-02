

#include <bits/stdc++.h>
using namespace std;

/*
Problem:
2466. Count Ways To Build Good Strings

Description:
Given the integers zero, one, low, and high, we can construct a string by starting with an empty 
string, and then at each step perform either of the following:
- Append the character '0' zero times.
- Append the character '1' one times.

This can be performed any number of times.

A good string is a string constructed by the above process having a length between low and high (inclusive).

Return the number of different good strings that can be constructed satisfying these properties. 
Since the answer can be large, return it modulo 10^9 + 7.

Example 1:
Input: low = 3, high = 3, zero = 1, one = 1
Output: 8
Explanation: 
One possible valid good string is "011". 
It can be constructed as follows: "" -> "0" -> "01" -> "011". 
All binary strings from "000" to "111" are good strings in this example.

Example 2:
Input: low = 2, high = 3, zero = 1, one = 2
Output: 5
Explanation: The good strings are "00", "11", "000", "110", "011".

Approach:
Dynamic Programming (Bottom-Up)

State:
dp[i] = number of ways to construct a string of length i

Transition:
At each length i, we can reach it by:
1. Adding 'zero' zeros from length (i - zero)
2. Adding 'one' ones from length (i - one)

dp[i] = dp[i - zero] + dp[i - one]

Base case:
dp[0] = 1 (empty string)

Result:
Sum of dp[low] + dp[low+1] + ... + dp[high]

LeetCode:
https://leetcode.com/problems/count-ways-to-build-good-strings/

Time Complexity:
O(high) - we compute dp values up to high

Space Complexity:
O(high) - for the dp array
*/

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int MOD = 1e9 + 7;
        vector<int> dp(high + 1, 0);
        
        // Base case: empty string
        dp[0] = 1;
        
        // Fill dp array for all lengths up to high
        for (int i = 1; i <= high; i++) {
            // Add zeros (if we can reach from i - zero)
            if (i >= zero) {
                dp[i] = (dp[i] + dp[i - zero]) % MOD;
            }
            
            // Add ones (if we can reach from i - one)
            if (i >= one) {
                dp[i] = (dp[i] + dp[i - one]) % MOD;
            }
        }
        
        // Sum all good strings with length between low and high
        int result = 0;
        for (int i = low; i <= high; i++) {
            result = (result + dp[i]) % MOD;
        }
        
        return result;
    }
};

class Solution {
public:
    int MOD = 1e9 + 7;
    int result = 0;
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, 0);
        dp[0] = 1;

        for(int i = 1; i <= high; i++){
            if(i >= zero){
                dp[i] = (dp[i] + dp[i - zero]) % MOD;
            }

            if(i >= one){
                dp[i] = (dp[i] + dp[i - one]) % MOD;
            }

            if(i >= low){
                result = (result + dp[i]) % MOD;
            }
        }

        // int result = 0;
        // for(int i = low; i <= high; i++){
        //     result = (result + dp[i]) % MOD; 
        // }

        return result;
    }
};

// Time Complexity: O(high)
// Space Complexity: O(high)

// Alternative: Top-Down DP (Memoization)
class Solution2 {
private:
    int MOD = 1e9 + 7;
    
    int solve(int length, int low, int high, int zero, int one, vector<int>& dp) {
        // Base case: if length exceeds high, no valid strings
        if (length > high) {
            return 0;
        }
        
        // Check memoized result
        if (dp[length] != -1) {
            return dp[length];
        }
        
        // Count current string if it's within [low, high]
        int count = (length >= low && length <= high) ? 1 : 0;
        
        // Add zero zeros
        count = (count + solve(length + zero, low, high, zero, one, dp)) % MOD;
        
        // Add one ones
        count = (count + solve(length + one, low, high, zero, one, dp)) % MOD;
        
        return dp[length] = count;
    }
    
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, -1);
        return solve(0, low, high, zero, one, dp);
    }
};

// Time Complexity: O(high)
// Space Complexity: O(high)




