/*
Problem:
926. Flip String to Monotone Increasing

Approach:
Single pass greedy / DP.

Let:
ones = number of '1's seen so far
flips = minimum flips needed so far

If we see:
'1' → increase ones
'0' → either:
   - flip this '0' to '1'  → flips + 1
   - flip all previous '1's to '0' → ones
Take minimum.

LeetCode:
https://leetcode.com/problems/flip-string-to-monotone-increasing/

Time Complexity:
O(n)

Space Complexity:
O(1)
*/

int minFlipsMonoIncr(string s) {

    int ones = 0;
    int flips = 0;

    for (char c : s) {

        // '1' → increase ones
        // '0' → either:
        // - flip this '0' to '1'  → flips + 1
        // - flip all previous '1's to '0' → ones   

        if (c == '1') {
            ones++;
        } else {
            // c == '0'
            flips = min(flips + 1, ones);
        }
    }

    return flips;
}
