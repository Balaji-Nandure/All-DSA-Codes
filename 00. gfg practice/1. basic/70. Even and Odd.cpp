/*
 * Problem: Even and Odd
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/even-and-odd/1
 * 
 * Given an array arr[] of size N containing equal number of odd and even numbers. 
 * Arrange the numbers such that all even numbers get even index and odd numbers 
 * get odd index. Note: 0-based indexing is considered.
 * 
 * Examples:
 * Input: N = 6, arr[] = {3, 6, 12, 1, 5, 8}
 * Output: 1 (for any valid arrangement like [6, 3, 12, 1, 8, 5])
 * Explanation: Even numbers (6,12,8) at even indices (0,2,4), 
 * odd numbers (3,1,5) at odd indices (1,3,5).
 * 
 * Input: N = 4, arr[] = {1, 2, 3, 4}
 * Output: 1 (for arrangement like [2, 1, 4, 3])
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use two-pointer technique with in-place swapping
 * - Maintain two pointers: evenPos (starts at 0), oddPos (starts at 1)
 * - Traverse array and fix misplaced elements:
 *   * If even number at odd position, swap with next available even position
 *   * If odd number at even position, swap with next available odd position
 * - Increment pointers by 2 to stay within even/odd indices
 * - This ensures O(1) space and O(N) time complexity
 * 
 * Time: O(N) - each element is processed at most once
 * Space: O(1) - only using two pointer variables
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void reArrange(int arr[], int N) {
        
        int evenPos = 0;  // Next available even index
        int oddPos = 1;   // Next available odd index
        
        while(evenPos < N && oddPos < N) {
            
            // If even position has even number, move to next even position
            if(arr[evenPos] % 2 == 0) {
                evenPos += 2;
            }
            // If odd position has odd number, move to next odd position
            else if(arr[oddPos] % 2 == 1) {
                oddPos += 2;
            }
            // Both positions have wrong parity numbers, swap them
            else {
                swap(arr[evenPos], arr[oddPos]);
                evenPos += 2;
                oddPos += 2;
            }
        }
    }
};
