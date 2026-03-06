/*
 * Problem: Search in a row-wise sorted matrix
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/search-in-a-row-wise-sorted-matrix1313/1
 * 
 * Given a row-wise sorted 2D matrix mat[][] of size n x m and an integer x, 
 * find whether element x is present in the matrix. Note: In a row-wise sorted 
 * matrix, each row is sorted in itself, i.e. for any i, j within bounds, 
 * mat[i][j] <= mat[i][j+1].
 * 
 * Examples:
 * Input: mat[][] = [[3, 4, 9],[2, 5, 6],[9, 25, 27]], x = 9
 * Output: true
 * Explanation: 9 is present in the matrix, so the output is true.
 * 
 * Input: mat[][] = [[19, 22, 27, 38, 55, 67]], x = 56
 * Output: false
 * Explanation: 56 is not present in the matrix, so the output is false.
 * 
 * Input: mat[][] = [[1, 2, 9],[65, 69, 75]], x = 91
 * Output: false
 * Explanation: 91 is not present in the matrix.
 * 
 * Constraints:
 * 1 ≤ n, m ≤ 1000
 * 1 ≤ mat[i][j] ≤ 10^5
 * 1 ≤ x ≤ 10^5
 * 
 * Expected Time Complexity: O(n log m)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Since each row is sorted individually, use binary search on each row
 * - For each row i, perform binary search to check if x exists
 * - If found in any row, return true
 * - If not found after checking all rows, return false
 * - This leverages the row-wise sorting property for efficient search
 * 
 * Time: O(n log m) - binary search on each of n rows
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        
        int n = mat.size();
        int m = mat[0].size();
        
        for (int i = 0; i < n; i++) {
            
            int left = 0;
            int right = m - 1;
            
            // Binary search in each row
            while (left <= right) {
                
                int mid = left + (right - left) / 2;
                
                if (mat[i][mid] == x)
                    return true;
                
                if (mat[i][mid] < x)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        
        return false;
    }
};
