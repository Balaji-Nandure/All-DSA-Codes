/*
 * Problem: Count Zeros in a Sorted Matrix
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/count-zeros-in-a-sorted-matrix/1
 * 
 * Given a N X N binary square matrix where each row and column is sorted in 
 * ascending order. Find the total number of zeros present in the matrix.
 * 
 * Examples:
 * Input: N = 3, A = {{0, 0, 0}, {0, 0, 1}, {0, 1, 1}}
 * Output: 6
 * Explanation: First row has 3 zeros, second row has 2 zeros, third row has 1 zero.
 * Total = 3 + 2 + 1 = 6 zeros.
 * 
 * Input: N = 2, A = {{1, 1}, {1, 1}}
 * Output: 0
 * Explanation: No zeros present in the matrix.
 * 
 * Constraints:
 * 0 < N ≤ 10^3
 * 0 ≤ A[i][j] ≤ 1
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Start from top-right corner using staircase search
 * - Key insight: Each step eliminates either one row or one column
 * - If A[row][col] == 1: move left (all elements below may still be 1)
 * - If A[row][col] == 0: count (col+1) zeros in current row, move down
 * - This leverages matrix sorting properties to achieve optimal complexity
 * - Each element to the left of current 0 is also 0 (row sorted property)
 * 
 * Time: O(N) - at most N+N steps (N left moves + N down moves)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int countZeros(vector<vector<int>>& A) {
        
        int n = A.size();
        
        int row = 0;
        int col = n - 1;  // Start from top-right corner
        
        int zeros = 0;
        
        while(row < n && col >= 0) {
            
            if(A[row][col] == 1) {
                col--;  // Move left - eliminate current column
            }
            else {
                zeros += (col + 1);  // All elements left are zeros
                row++;               // Move to next row
            }
        }
        
        return zeros;
    }
};