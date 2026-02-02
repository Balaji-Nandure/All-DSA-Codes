/*
Problem:
1416. Restore The Array

Description:
A program was supposed to print an array of integers. The program forgot to print whitespaces 
and the array is printed as a string of digits s and all we know is that all integers in the array 
were in the range [1, k] and there are no leading zeros in the array.
Given the string s and the integer k, return the number of the possible arrays that can be printed 
as string s using the mentioned program. Since the answer may be very large, return it modulo 10^9 + 7.

Approach:
Recursion + Memoization

State:
solve(i) = number of ways to partition s[i..n-1] into valid numbers

Transition:
From position i, try all possible numbers starting at i:
- Extract substring s[i..j] and check if it forms a valid number (no leading zeros, <= k)
- Add solve(j+1) to the answer

Base case:
If i == n, we've successfully partitioned the entire string, return 1

LeetCode:
https://leetcode.com/problems/restore-the-array/

Time Complexity:
O(n * log(k)) where n is length of string, log(k) is max digits in k

Space Complexity:
O(n) for dp array and recursion stack
*/

class Solution {
private:
    const int MOD = 1e9 + 7;
    
    int solve(int i, string& s, int k, vector<int>& dp) {
        // Base case: reached end of string
        if (i == s.length()) {
            return 1;
        }
        
        // Leading zero - invalid
        if (s[i] == '0') {
            return 0;
        }
        
        // Check memoized result
        if (dp[i] != -1) {
            return dp[i];
        }
        
        long long ans = 0;
        long long num = 0;
        
        // Try all possible numbers starting at position i
        for (int j = i; j < s.length(); j++) {
            num = num * 10 + (s[j] - '0');
            
            // If number exceeds k, no point continuing
            if(num > k || num == 0) break;
            
            // Add the number of ways from position j+1
            ans = (ans + solve(j + 1, s, k, dp)) % MOD;
        }
        
        return dp[i] = ans;
    }
    
public:
    int numberOfArrays(string s, int k) {
        int n = s.length();
        vector<int> dp(n, -1);
        
        return solve(0, s, k, dp);
    }
};
