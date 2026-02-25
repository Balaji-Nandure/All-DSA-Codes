/*
 * Problem: Plus One
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/plus-one/1
 * 
 * Given a non-negative number represented as a list of digits, add 1 to the number 
 * (increment the number represented by the digits). The digits are stored such that 
 * the most significant digit is first element of array.
 * 
 * Examples:
 * Input: N = 3, arr[] = {1, 2, 4}
 * Output: {1, 2, 5}
 * Explanation: 124+1 = 125, and so the Output
 * 
 * Input: N = 3, arr[] = {9, 9, 9}
 * Output: {1, 0, 0, 0}
 * Explanation: 999+1 = 1000, and so the output
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^5
 * 0 ≤ arr[i] ≤ 9
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Start from last digit and add 1 with carry propagation
 * - Traverse from right to left, adding carry to each digit
 * - If sum < 10: set digit to sum, carry = 0, stop early
 * - If sum >= 10: set digit to 0, carry = 1, continue
 * - If carry remains after traversal (all 9s case), insert 1 at beginning
 * - Handle digit array as big integer addition
 * 
 * Time: O(N) - single pass through array
 * Space: O(1) - in-place modification except possible array resize
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> increment(vector<int>& arr, int N) {
        
        int carry = 1;   // we need to add +1
        
        // Traverse from last digit to first
        for (int i = N - 1; i >= 0; i--) {
            
            int sum = arr[i] + carry;
            
            if (sum < 10) {
                arr[i] = sum;   // no further carry
                carry = 0;
                break;          // we can stop early
            }
            else {
                arr[i] = 0;     // 10 -> 0 and carry forward
                carry = 1;
            }
        }
        
        // If carry still remains after full traversal
        if (carry == 1) {
            arr.insert(arr.begin(), 1);
        }
        
        return arr;
    }
};
