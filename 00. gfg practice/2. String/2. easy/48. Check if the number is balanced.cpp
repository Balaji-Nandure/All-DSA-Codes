/*
Problem: Check if the number is balanced

Given an integer N which has odd number of digits, find whether the given number is a balanced or not.
An odd digit number is called a balanced number if the sum of all digits to the left of the middle digit and the sum of all digits to the right of the middle digit is equal.

Example 1:
Input:
N = 1234006
Output: 1 
Explanation: Total number of digits in N = 7. Middle digit is 4. LHS = 1+2+3 = 6 and RHS = 0+0+6 = 6. LHS is equal to RHS. 

Example 2:
Input:
N = 12345
Output: 0
Explanation: LHS = 1+2 = 3 and RHS = 4+5 = 9. LHS and RHS are not equal.

Constraints:
1 <= N <= 10^100
N will always have odd number of digits.
Since N can be very large, it is given as a string. 

--------------------------------------------------

Pattern:
String Processing + Simple Iteration

--------------------------------------------------

Key Observation:
- We are given a string `N` with an odd length `n`.
- The middle character is located exactly at index `n / 2`.
- We need to compute the numerical sum of digits from index `0` to `(n/2) - 1` and compare it with the sum from index `(n/2) + 1` to `n - 1`.
- To get the numerical value of a character, simply subtract the character '0', i.e., `N[i] - '0'`.

--------------------------------------------------

Approach:
1. Find the total length `n` of string `N` and identify the `mid` index as `n / 2`.
2. Initialize two variables `lSum` and `rSum` to 0.
3. Iterate `i` from 0 to `mid - 1` and add `N[i] - '0'` to `lSum`.
4. Iterate `i` from `mid + 1` to `n - 1` and add `N[i] - '0'` to `rSum`.
5. Return `true` if `lSum == rSum`, else `false`.

--------------------------------------------------

Time Complexity: O(L) where L is the number of digits in N.
Space Complexity: O(1) Auxiliary Space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/check-if-the-number-is-balanced5914/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool balancedNumber(string N) {
        int n = N.length();
        int mid = n / 2;
        int lSum = 0;
        int rSum = 0;
        
        // Sum of left part
        for (int i = 0; i < mid; i++) {
            lSum += (N[i] - '0');
        }
        
        // Sum of right part
        for (int i = mid + 1; i < n; i++) {
            rSum += (N[i] - '0');
        }
        
        // Check if balanced
        return lSum == rSum;
    }
};
