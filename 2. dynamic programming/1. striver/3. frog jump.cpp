/*
Problem: Frog Jump (Minimum Energy)

Statement:
Given an array height[] of size n.
A frog starts at index 0 and wants to reach index n-1.
The frog can jump either 1 step or 2 steps.
Cost of a jump from i to j = abs(height[i] - height[j]).
Return the minimum total energy required.

DP State:
dp[i] = minimum energy required to reach index i

Recurrence:
dp[i] = min(
            dp[i-1] + abs(h[i] - h[i-1]),
            dp[i-2] + abs(h[i] - h[i-2])
         )

Links:
GFG : https://practice.geeksforgeeks.org/problems/geek-jump/1
LC  : https://leetcode.com/problems/frog-jump/
*/

#include <bits/stdc++.h>
using namespace std;

/* ---------------------------------------------------------- */
/* Approach 1: Pure Recursion
   TC: O(2^n)
   SC: O(n) (recursion stack)
*/
int frogJumpRec(int i, vector<int> &h) {
    // Base case: starting position
    if (i == 0) return 0;

    // Jump from i-1
    int oneJump = frogJumpRec(i - 1, h) + abs(h[i] - h[i - 1]);

    // Jump from i-2 (if possible)
    // this recrsion call always will not happen so we keep a check
    int twoJump = INT_MAX;
    if (i > 1)
        twoJump = frogJumpRec(i - 2, h) + abs(h[i] - h[i - 2]);

    // Take minimum energy
    return min(oneJump, twoJump);
}

/* ---------------------------------------------------------- */
/* Approach 2: Memoization (Top-Down DP)
   TC: O(n)
   SC: O(n) + recursion stack
*/
int frogJumpMemo(int i, vector<int> &h, vector<int> &dp) {
    // Base case
    if (i == 0) return 0;

    // Return stored result
    if (dp[i] != -1) return dp[i];

    // Jump from i-1
    int oneJump = frogJumpMemo(i - 1, h, dp) + abs(h[i] - h[i - 1]);

    // Jump from i-2
    int twoJump = INT_MAX;
    if (i > 1)
        twoJump = frogJumpMemo(i - 2, h, dp) + abs(h[i] - h[i - 2]);

    // Store and return
    return dp[i] = min(oneJump, twoJump);
}

/* ---------------------------------------------------------- */
/* Approach 3: Tabulation (Bottom-Up DP)
   TC: O(n)
   SC: O(n)
*/
int frogJumpTab(int n, vector<int> &h) {
    vector<int> dp(n);

    // Base cases
    dp[0] = 0;
    dp[1] = abs(h[1] - h[0]);

    // Build dp iteratively
    for (int i = 2; i < n; i++) {
        dp[i] = min(
            //  whenever there is dp[i-1] or dp[i-2] in the recurrence relation, 
            // we can space optimise it.
            dp[i - 1] + abs(h[i] - h[i - 1]),
            dp[i - 2] + abs(h[i] - h[i - 2])
        );
    }

    return dp[n - 1];
}

/* ---------------------------------------------------------- */
/* Approach 4: Space Optimized (Best)
   TC: O(n)
   SC: O(1)
*/
int frogJumpSpaceOpt(int n, vector<int> &h) {
    if(n == 1) return 0;
    int prev2 = 0;                       // dp[0]
    int prev1 = abs(h[1] - h[0]);        // dp[1]
    // Iterate using only two variables
    for (int i = 2; i < n; i++) {
        int curr = min(
            prev1 + abs(h[i] - h[i - 1]),
            prev2 + abs(h[i] - h[i - 2])
        );
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

/* ---------------------------------------------------------- */
/* Main function for testing */
int main() {
    vector<int> height = {10, 20, 30, 10};
    int n = height.size();

    cout << "Recursion        : " << frogJumpRec(n - 1, height) << endl;

    vector<int> dp(n, -1);
    cout << "Memoization      : " << frogJumpMemo(n - 1, height, dp) << endl;

    cout << "Tabulation       : " << frogJumpTab(n, height) << endl;
    cout << "Space Optimized  : " << frogJumpSpaceOpt(n, height) << endl;

    return 0;
}
