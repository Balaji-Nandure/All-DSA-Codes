/*
 * Problem: Number of Subarrays of 0s
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/number-of-subarrays-of-0s/1
 * 
 * Given an array of 0s and 1s, count the total number of subarrays consisting 
 * ONLY of 0s.
 * 
 * Examples:
 * Input: arr = [0, 0, 1, 0]
 * Output: 4
 * Explanation: 
 * First block of zeros (length 2): subarrays = [0], [0], [0,0] = 3
 * Second block of zeros (length 1): subarrays = [0] = 1
 * Total = 3 + 1 = 4
 * 
 * Input: arr = [1, 0, 0, 0, 1]
 * Output: 6
 * Explanation: Block of 3 consecutive zeros gives 3*(3+1)/2 = 6 subarrays
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * arr[i] ∈ {0, 1}
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Key insight: For k consecutive zeros, number of subarrays = k*(k+1)/2
 * - This is because we can choose any starting position (k choices) and 
 *   any ending position after it, giving us the combination formula
 * - Traverse array and count consecutive zeros in blocks
 * - When encountering 1, calculate subarrays for current block and reset
 * - Handle the last block of zeros after loop ends
 * - Use long long to prevent integer overflow
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long int no_of_subarrays(int n, vector<int> &arr) {
        
        long long result = 0;
        long long count = 0;
        
        for(int i = 0; i < n; i++) {
            
            if(arr[i] == 0) {
                count++;
            }
            else {
                // Found a 1, calculate subarrays for current block of zeros
                result += (count * (count + 1)) / 2;
                count = 0;  // Reset count for next block
            }
        }
        
        // Handle last block of zeros (if array ends with zeros)
        result += (count * (count + 1)) / 2;
        
        return result;
    }
};