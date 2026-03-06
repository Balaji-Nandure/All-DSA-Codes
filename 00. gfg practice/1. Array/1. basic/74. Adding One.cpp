/*
 * Problem: Adding One
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/adding-one/1
 * 
 * Given a non-negative integer (without leading zeroes) represented as an array arr. 
 * Add 1 to the number (increment by 1). The digits are stored such that the most 
 * significant digit is at the starting index of the array.
 * 
 * Examples:
 * Input: arr[] = [5, 6, 7, 8]
 * Output: [5, 6, 7, 9]
 * Explanation: 5678 + 1 = 5679
 * 
 * Input: arr[] = [9, 9, 9]
 * Output: [1, 0, 0, 0]
 * Explanation: 999 + 1 = 1000
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 0 ≤ arr[i] ≤ 9
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Start from the rightmost digit (least significant)
 * - Add 1 to the last digit and handle carry propagation
 * - If digit becomes 10, set it to 0 and carry 1 to next position
 * - Continue until no carry or reach the beginning
 * - If carry still exists after processing all digits, insert 1 at beginning
 * - This handles the edge case where all digits are 9 (e.g., 999 → 1000)
 * 
 * Time: O(n) - single pass from right to left
 * Space: O(1) - in-place modification, only extra space for potential leading 1
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> addOne(vector<int>& arr) {
        
        int n = arr.size();
        int carry = 1;  // We want to add 1
        
        // Process digits from right to left
        for(int i = n - 1; i >= 0; i--) {  // Fixed: added i--
            
            int sum = arr[i] + carry;
            arr[i] = sum % 10;    // Current digit
            carry = sum / 10;     // Carry for next iteration
            
            if(!carry) break;     // Early termination optimization
        }
        
        // If carry still exists, we need to add a leading 1
        if(carry) {
            arr.insert(arr.begin(), carry);
        }
        
        return arr;
    }
};