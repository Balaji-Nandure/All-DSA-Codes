/*
Problem: No of Carry Operations

GFG: https://www.geeksforgeeks.org/problems/no-of-carry-operations/1

Description:
Given two numbers A and B (same length), return the number of carry operations
required while adding them.

Examples:

Input: A = 1234, B = 5678
Output: 2

Input: A = 555, B = 555
Output: 3

Constraints:
1 <= A, B <= 10^18

Approach:
Simulate addition from right to left:
- at each step, sum current digits and previous carry
- if sum >= 10, carry occurs

Time Complexity: O(number of digits)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long countCarry(long long A, long long B) {
        // code here
        int carry = 0;
        long long count = 0;
        
        while(A > 0 || B > 0){
            int a = A % 10;
            int b = B % 10;
            
            int sum = a + b + carry;
            if(sum >= 10){
                count++;
                carry = 1;
            } else {
                carry = 0;
            }
            
            A /= 10;
            B /= 10;
            
        }
        
        return count;
    }
};
