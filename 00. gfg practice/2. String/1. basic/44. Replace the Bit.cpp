/*
Problem: Replace the Bit

GFG: https://www.geeksforgeeks.org/problems/replace-the-bit/1

Description:
Given N and K, change the Kth bit from the left (1-based) in binary form of N
to 0 if it is 1. If that bit does not exist or is already 0, return N.

Examples:

Input: N = 13, K = 2
Output: 9
Explanation: 13 -> 1101, 2nd bit from left is 1, make it 0 => 1001 (9)

Input: N = 13, K = 6
Output: 13
Explanation: 1101 has only 4 bits, so no change.

Constraints:
1 <= N <= 10^6

Approach:
Find number of bits in N. Convert Kth-from-left to index from right:
posFromRight = totalBits - K.
If K is out of range, return N. Otherwise clear that bit with mask.

Time Complexity: O(log N)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(log N)
    // SC: O(1)

    int replaceBit(int N, int K) {

        int totalBits = 0;
        int temp = N;

        while(temp > 0) {
            totalBits++;
            temp >>= 1;
        }

        if(K > totalBits) {
            return N;
        }

        int posFromRight = totalBits - K;
        int mask = 1 << posFromRight;

        if((N & mask) == 0) {
            return N;
        }

        return (N & (~mask));
    }
};
