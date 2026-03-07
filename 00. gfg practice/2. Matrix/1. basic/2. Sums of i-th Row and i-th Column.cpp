/*
 * Problem: Sums of i-th Row and i-th Column
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/sums-of-i-th-row-and-i-th-column/1
 * 
 * Given a matrix A of dimensions N×M. Check whether the sum of the i-th row is 
 * equal to the sum of the i-th column. Check only up to valid row and column 
 * numbers i.e., min(N, M).
 * 
 * Examples:
 * Input: N=2, M=2, A=[[1,2],[2,1]]
 * Output: 1
 * Explanation: 
 * Row0 sum = 1+2 = 3, Col0 sum = 1+2 = 3 ✓
 * Row1 sum = 2+1 = 3, Col1 sum = 2+1 = 3 ✓
 * All valid pairs match, so return 1.
 * 
 * Input: N=1, M=3, A=[[5,0,0]]
 * Output: 1
 * Explanation: Only check Row0 vs Col0.
 * Row0 sum = 5+0+0 = 5, Col0 sum = 5 ✓
 * (No 2nd/3rd rows to check since N=1)
 * 
 * Constraints:
 * 1 ≤ N, M, A[i][j] ≤ 10^3
 * 
 * Expected Time Complexity: O(N*M)
 * Expected Auxiliary Space: O(min(N,M))
 * 
 * Approach:
 * - Check only up to k = min(N,M) since beyond that either row or column doesn't exist
 * - For each i from 0 to k-1:
 *   * Calculate sum of i-th row (scan M elements)
 *   * Calculate sum of i-th column (scan N elements)  
 *   * If sums don't match, return 0 immediately
 * - If all valid pairs match, return 1
 * - Early termination optimization when mismatch found
 * 
 * Time: O(N*M) - in worst case, scan all elements once
 * Space: O(1) - constant extra space (not O(min(N,M)) as expected)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int sumOfRowCol(int N, int M, vector<vector<int>> A) {
        
        int k = min(N, M);
        
        for(int i = 0; i < k; i++) {
            
            int rowSum = 0;
            int colSum = 0;
            
            // Calculate sum of i-th row
            for(int j = 0; j < M; j++) {
                rowSum += A[i][j];
            }
            
            // Calculate sum of i-th column
            for(int j = 0; j < N; j++) {
                colSum += A[j][i];
            }
            
            // Early termination if sums don't match
            if(rowSum != colSum) {
                return 0;
            }
        }
        
        return 1;  // All valid pairs matched
    }
};