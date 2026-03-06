/*
 * Problem: Equal Point in a String of Brackets
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/equal-point-in-a-string-of-brackets/1
 * 
 * Given a string str of opening and closing brackets '(' and ')' only. Find an 
 * equal point - an index such that the number of closing brackets on the right 
 * from that point equals the number of opening brackets before that point.
 * 
 * Examples:
 * Input: str = "(())))("
 * Output: 4
 * Explanation: After index 4, string splits into "(())" and "))(". 
 * Opening brackets in first part = 2, closing brackets in second part = 2.
 * 
 * Input: str = "))"
 * Output: 2
 * Explanation: After index 2, splits into "))" and "". 
 * Opening brackets in first part = 0, closing brackets in second part = 0.
 * 
 * Constraints:
 * 1 ≤ str.size() ≤ 10^6
 * str consists of only '(' and ')' brackets
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Count total opening brackets in the string
 * - Traverse from left, maintaining count of opening brackets seen so far
 * - At each position i, check if opening brackets before i equals 
 *   closing brackets after i (total_closing - closing_seen_so_far)
 * - Since total_closing = n - total_opening, we can optimize to O(1) space
 * - For position i: open_before = open_count, close_after = total_close - close_count
 * 
 * Time: O(n) - single pass through string
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findIndex(string str) {
        
        int n = str.length();
        
        // Count total opening brackets
        int totalOpen = 0;
        for(char c : str) {
            if(c == '(') {
                totalOpen++;
            }
        }
        
        int totalClose = n - totalOpen;
        
        // Traverse and find equal point
        int openCount = 0;   // Opening brackets seen so far
        int closeCount = 0;  // Closing brackets seen so far
        
        for(int i = 0; i <= n; i++) {
            
            // At position i:
            // - Opening brackets before i = openCount
            // - Closing brackets after i = totalClose - closeCount
            
            if(openCount == totalClose - closeCount) {
                return i;
            }
            
            // Update counts for next iteration (if not at end)
            if(i < n) {
                if(str[i] == '(') {
                    openCount++;
                } else {
                    closeCount++;
                }
            }
        }
        
        return -1;  // No equal point found (shouldn't happen for valid input)
    }
};