/*
 * Problem: Nearest multiple of 10
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/nearest-multiple-of-10/0
 * 
 * A string s is given to represent a positive number. The task is to round str 
 * to the nearest multiple of 10. If you have two multiples equally apart from s, 
 * choose the smallest element among them.
 * 
 * Examples:
 * Input: s = "29" 
 * Output: 30
 * Explanation: Close multiples are 20 and 30, and 30 is the nearest to 29.
 * 
 * Input: s = "15"
 * Output: 10
 * Explanation: 10 and 20 are equally distant multiples from 15. 
 *              The smallest of the two is 10.
 * 
 * Constraints:
 * 1 ≤ s.size() ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Check last digit to determine rounding direction
 * - If last digit <= 5: round down by setting last digit to '0'
 * - If last digit > 5: round up by adding 1 to the number and setting last digit to '0'
 * - Handle carry propagation during rounding up
 * - If carry remains after processing all digits, prepend '1'
 * - Always return result with last digit as '0'
 * 
 * Time: O(n) - worst case when carry propagates through all digits
 * Space: O(1) - in-place string modification
 */

#include <bits/stdc++.h>
using namespace std;


class Solution {
  public:
    string roundToNearest(string& s) {
        // Complete the function
        int n = s.size();
        int lastDigit = s[n - 1] - '0';
        
        // round down
        if(lastDigit <= 5){
            s[n - 1] = '0';
            return s;
        }
        
        // round up
        s[n - 1] = '0';
        int carry = 1;
        int i = n - 2;
        
        while(i >= 0 && carry){
            int digit = (s[i] - '0') + carry;
            carry = digit / 10;
            s[i] = (digit % 10) + '0';
            i--;
        }
        
        if(carry){
            s = '1' + s;
        }
        
        
        return s;
    }
};
