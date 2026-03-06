/*
 * Problem: Minimum Number
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/minimum-number/1
 * 
 * You are given an array arr of n elements. In one operation you can pick two 
 * indices i and j, such that arr[i] >= arr[j] and replace the value of arr[i] 
 * with (arr[i] - arr[j]). You have to minimize the values of the array after 
 * performing any number of such operations.
 * 
 * Examples:
 * Input: n = 3, arr = {3,2,4}
 * Output: 1
 * Explanation: 
 * 1st Operation: Pick 4 & 3, subtract 4-3 => {3,2,1}
 * 2nd Operation: Pick 3 & 2, subtract 3-2 => {1,2,1}
 * 3rd Operation: Pick 2 & 1, subtract 2-1 => {1,1,1}
 * 4th Operation: Pick 1 & 1, subtract 1-1 => {1,0,1}
 * 5th Operation: Pick 1 & 1, subtract 1-1 => {0,0,1}
 * Maximum number left is 1.
 * 
 * Input: n = 2, arr = {2,4}
 * Output: 2
 * Explanation:
 * 1st Operation: Pick 4 & 2, subtract 4-2 => {2,2}
 * 2nd Operation: Pick 2 & 2, subtract 2-2 => {0,2}
 * Maximum number left is 2.
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n)
 * Expected Space Complexity: O(1)
 * 
 * Approach:
 * - Key insight: The operation arr[i] - arr[j] is similar to Euclidean algorithm
 * - The minimum possible value we can achieve is the GCD of all elements
 * - This is because the subtraction operation preserves the GCD property
 * - Any common divisor of the original numbers will remain a divisor
 * - The GCD is the largest number that can divide all elements
 * - After optimal operations, all elements become multiples of GCD
 * - The minimum non-zero value achievable is exactly the GCD
 * 
 * Time: O(n * log(max(arr))) - GCD calculation
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    
    // Helper function to calculate GCD using Euclidean algorithm
    int gcd(int a, int b) {
        while(b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    int minimumNumber(int n, vector<int> &arr) {
        
        // Find GCD of all elements
        int result = arr[0];
        
        for(int i = 1; i < n; i++) {
            result = gcd(result, arr[i]);
            
            // inbuild gcd function
            // if the GCD is 1, then we can break out of the loop
            
            // Early termination: if GCD becomes 1, it won't change
            if(result == 1) {
                break;
            }
        }
        
        return result;
    }
};