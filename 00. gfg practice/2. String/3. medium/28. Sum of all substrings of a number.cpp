/*
GeeksforGeeks: Sum of all substrings of a number
Difficulty: Medium

Problem:
Given an integer s represented as a string, the task is to get the sum of all possible sub-strings of this string.
Note: The number may have leading zeros.
It is guaranteed that the total sum will fit within a 62-bit integer (long long), and should be returned modulo 10^9 + 7.

Examples:
Input: s = "6759"
Output: 8421
Explanation:
Sum = 6 + 7 + 5 + 9 + 67 + 75 + 59 + 675 + 759 + 6759 = 8421

Input: s = "421"
Output: 491
Explanation: 
Sum = 4 + 2 + 1 + 42 + 21 + 421 = 491

Constraints:
1 <= |s| <= 10^5

DP State Design:
- dp[i] stores the sum of all substrings ending at index i.
- Recurrence: 
  Each substring ending at i-1 has the current digit appended to it, which multiplies its value by 10 and adds the current digit.
  There are exactly (i + 1) substrings ending at index i (including the single digit substring of s[i]).
  Therefore: dp[i] = (dp[i-1] * 10 + (i + 1) * s[i]) % MOD.

Time Complexity: O(N) where N is the length of string s.
Space Complexity: O(N) for top-down/tabulation, optimized to O(1) space.

GFG Link: https://www.geeksforgeeks.org/problems/sum-of-all-substrings-of-a-number-1587115621/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Recursive Approach (Exponential Time)
// TC: O(2^N) in worst case, SC: O(N) recursion stack space
class SubstringsRecursive {
private:
    const int MOD = 1e9 + 7;
    
    long long solve(int i, string &s) {
        // Base Case: Only one substring ending at index 0, which is the digit itself.
        if (i == 0) {
            return s[0] - '0';
        }
        
        int digit = s[i] - '0';
        return (10LL * solve(i - 1, s) + 1LL * digit * (i + 1)) % MOD;
    }
public:
    long long sumSubstrings(string s) {
        int n = s.size();
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + solve(i, s)) % MOD;
        }
        return ans;
    }
};

// 2. Memoization (Top-Down DP)
// TC: O(N), SC: O(N) dp state table + O(N) recursion stack space
class SubstringsMemoization {
private:
    const int MOD = 1e9 + 7;
    
    long long solve(int i, string &s, vector<long long> &dp) {
        // Base Case
        if (i == 0) {
            return s[0] - '0';
        }
        
        // Return cached result
        if (dp[i] != -1) {
            return dp[i];
        }
        
        int digit = s[i] - '0';
        return dp[i] = (10LL * solve(i - 1, s, dp) + 1LL * digit * (i + 1)) % MOD;
    }
public:
    long long sumSubstrings(string s) {
        int n = s.size();
        vector<long long> dp(n, -1);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + solve(i, s, dp)) % MOD;
        }
        return ans;
    }
};

// 3. Tabulation (Bottom-Up DP)
// TC: O(N), SC: O(N) dp table
// Let's learn Tabulation step-by-step! 
// Remember the 3 Golden Steps to convert any recursive DP into Tabulation:
// Step 1: Create the DP Table/Array.
// Step 2: Analyze & Initialize the Base Case.
// Step 3: Run the loops (bottom-up) and write down the state transition.
class SubstringsTabulation {
public:
    long long sumSubstrings(string s) {
        int n = s.length();
        const int MOD = 1e9 + 7;
        
        /* 
         * Step 1: Create the DP Table.
         * dp[i] will store: "What is the sum of all numeric substrings ending at index i?"
         * Size is n because indices run from 0 to n-1.
         * Initialize all cells as 0.
         */
        vector<long long> dp(n, 0);
        
        /* 
         * Step 2: Analyze & Initialize the Base Case.
         * For the first character at index 0, the only substring ending here is s[0].
         * So dp[0] = s[0] - '0'.
         * We also initialize our totalSum running accumulator with this base case value.
         */
        dp[0] = s[0] - '0';
        long long totalSum = dp[0];
        
        /* 
         * Step 3: Run the loops bottom-up.
         * We iterate forward from index i = 1 to n-1.
         * For each position i, the substrings ending at i are formed by:
         * 1. Appending the digit s[i] to all existing substrings ending at i-1. 
         *    In math, this is equivalent to multiplying the sum of all substrings ending at i-1 by 10,
         *    and adding the digit s[i] to each of these substrings.
         *    Since there are 'i' substrings ending at i-1, we add s[i] * i.
         * 2. Adding the single-character substring consisting only of the current digit s[i] itself.
         *    This adds another s[i] * 1.
         * Combining these: 
         * dp[i] = (dp[i-1] * 10 + (i + 1) * s[i]) % MOD.
         */
        for (int i = 1; i < n; i++) {
            long long digit = s[i] - '0';
            dp[i] = (dp[i - 1] * 10 + (i + 1) * digit) % MOD;
            totalSum = (totalSum + dp[i]) % MOD;
        }
        
        // Return the accumulated sum of all possible substrings
        return totalSum;
    }
};

// 4. Space Optimized (Bottom-Up DP with O(1) space)
// TC: O(N), SC: O(1) space optimization
class Solution {
public:
    long long sumSubstrings(string s) {
        int n = s.length();
        const int MOD = 1e9 + 7;
        
        // We only need the sum of substrings ending at the previous position (prev) 
        // to compute the sum of substrings ending at the current position.
        long long prev = s[0] - '0';
        long long totalSum = prev;
        
        for (int i = 1; i < n; i++) {
            long long digit = s[i] - '0';
            long long curr = (prev * 10 + (i + 1) * digit) % MOD;
            totalSum = (totalSum + curr) % MOD;
            prev = curr;
        }
        
        return totalSum;
    }
};

/*
Dry Run — Example:
s = "421"
n = 3

Initially, prev = 4, totalSum = 4.

1. i = 1 (digit = 2):
   - curr = (prev * 10 + (1 + 1) * 2) % MOD = (4 * 10 + 2 * 2) = 44
   - totalSum = (4 + 44) = 48
   - prev = curr = 44

2. i = 2 (digit = 1):
   - curr = (prev * 10 + (2 + 1) * 1) % MOD = (44 * 10 + 3 * 1) = 443
   - totalSum = (48 + 443) = 491
   - prev = curr = 443

Returns totalSum which is 491.
Output: 491
*/
