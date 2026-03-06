/*
 * Problem: Play with an Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/play-with-an-array/1
 * 
 * You are given an array arr[] of positive integers. You have to rearrange the 
 * array elements such that the number at the odd index is strictly greater than 
 * the number at the previous even index. If the array can be rearranged according 
 * to condition, then return true otherwise return false.
 * 
 * Examples:
 * Input: arr[] = [5, 4, 3, 2, 1]
 * Output: true
 * Explanation: The given array after modification will be as such: [4, 5, 2, 3, 1].
 * Pattern: 4 < 5, 2 < 3 (odd indices greater than previous even indices)
 * 
 * Input: arr[] = [4, 3, 1, 1]
 * Output: true
 * Explanation: Can be rearranged as [1, 3, 1, 4] where 1 < 3 and 1 < 4.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Sort the array to get optimal pairing opportunity
 * - Use greedy strategy: pair smallest with largest available elements
 * - After sorting, try pairing first half (smaller elements) at even indices
 *   with second half (larger elements) at odd indices
 * - Check if arr[i] < arr[i + n/2] for all valid i
 * - If any pair fails the condition, return false
 * - This gives the best chance since we're pairing smallest with largest
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool canArrange(vector<int> &arr) {
        
        int n = arr.size();
        
        // Sort the array for optimal pairing
        sort(arr.begin(), arr.end());
        
        // Try to pair elements: smaller half with larger half
        // arr[0] with arr[n/2], arr[1] with arr[n/2+1], etc.
        for(int i = 0; i < n/2; i++) {
            
            // Check if current pair satisfies the condition
            if(arr[i] >= arr[i + n/2]) {
                return false;
            }
        }
        
        return true;
    }
};