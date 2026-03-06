/*
 * Problem: Maximum Identical Bowls
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/maximum-identical-bowls/1
 * 
 * There are N bowls containing cookies. In one operation, you can take one cookie 
 * from any of the non-empty bowls and put it into another bowl. If the bowl becomes 
 * empty you discard it. You can perform the above operation any number of times. 
 * You want to know the maximum number of bowls you can have with an identical 
 * number of cookies.
 * 
 * Examples:
 * Input: N = 3, arr[] = {3, 1, 5}
 * Output: 3
 * Explanation: We can put 2 cookies from the 3rd bowl into the 2nd bowl.
 * Now the array becomes {3, 3, 3}. Each bowl contains 3 cookies.
 * 
 * Input: N = 4, arr[] = {1, 2, 6, 5}
 * Output: 2
 * Explanation: We can redistribute cookies to get {7, 7} by moving cookies
 * from bowls with 6 and 5 cookies to bowls with 1 and 2 cookies.
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Key insight: We want to maximize the number of bowls with identical cookies
 * - If we have k bowls with x cookies each, total cookies = k * x
 * - For a given k, x = total_cookies / k
 * - We need to check if it's possible to redistribute cookies to achieve this
 * - Try all possible values of k from N down to 1
 * - For each k, check if total_cookies is divisible by k
 * - If yes, return k (first valid k gives maximum bowls)
 * 
 * Time: O(N) - calculating sum + checking divisors
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int getMaximum(vector<int> &arr) {
        
        int n = arr.size();
        
        // Calculate total cookies
        long long totalCookies = 0;
        for(int i = 0; i < n; i++) {
            totalCookies += arr[i];
        }
        
        // Try from maximum possible bowls (n) down to 1
        for(int k = n; k >= 1; k--) {
            
            // Check if we can have k bowls with equal cookies
            if(totalCookies % k == 0) {
                
                long long cookiesPerBowl = totalCookies / k;
                
                // Check if redistribution is possible
                // We need at least cookiesPerBowl cookies in each of k bowls
                // This is always possible if total is divisible by k
                // because we can move cookies from bowls with excess to bowls with deficit
                
                return k;
            }
        }
        
        return 1; // At minimum, we can always have 1 bowl with all cookies
    }
};