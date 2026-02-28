/*
 * Problem: Min Sum Formed by Digits
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/min-sum-formed-by-digits/1
 * 
 * Given an array of digits (values are from 0 to 9), find the minimum possible sum 
 * of two numbers formed from digits of the array. All digits of the given array 
 * must be used to form the two numbers.
 * 
 * Any combination of digits may be used to form the two numbers to be summed. 
 * Leading zeroes are permitted.
 * 
 * If forming two numbers is impossible (i.e. when n==0) then the "sum" is the 
 * value of the only number that can be formed.
 * 
 * Examples:
 * Input: N = 6, arr[] = {6, 8, 4, 5, 2, 3}
 * Output: 604
 * Explanation: The minimum sum is formed by numbers 358 and 246.
 * 
 * Input: N = 5, arr[] = {5, 3, 0, 7, 4}
 * Output: 82
 * Explanation: The minimum sum is formed by numbers 35 and 047.
 * 
 * Constraints:
 * 1 ≤ N ≤ 35
 * 0 ≤ A[] ≤ 9
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(N)
 * 
 * Approach:
 * - Sort the array of digits in ascending order
 * - Distribute digits alternately to two numbers, starting with the smallest digit
 * - This ensures both numbers are balanced and smaller digits are placed in higher positions
 * - Compute the sum of the two formed numbers
 * - Since N ≤ 35, the numbers fit in long long
 * 
 * Time: O(N log N) - dominated by sorting
 * Space: O(1) - no extra space besides input
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long int minSum(int arr[], int n) {
        
        if(n == 0)
            return 0;
            
        sort(arr, arr + n);
        
        long long num1 = 0;
        long long num2 = 0;
        
        for(int i = 0; i < n; i++) {
            
            if(i % 2 == 0)
                num1 = num1 * 10 + arr[i];
            else
                num2 = num2 * 10 + arr[i];
        }
        
        return num1 + num2;
    }
};
