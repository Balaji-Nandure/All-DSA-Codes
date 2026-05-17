/*
Problem: Sums of i-th row and i-th column

Description:
Given a matrix mat[][] of size n x m, check whether for every valid index i,
sum of i-th row is equal to sum of i-th column.

If n != m, compare only for i in [0, min(n, m) - 1].

Examples:
[[1, 2], [2, 1]] -> true
[[5], [0], [0]] -> true
[[1, 4, 2], [6, 1, 3]] -> false

Constraints:
1 <= n, m <= 10^3
0 <= mat[i][j] <= 10^3

Approach:
1) Compute all row sums.
2) Compute all column sums.
3) For i from 0 to min(n, m)-1, compare rowSum[i] and colSum[i].
   If any mismatch, return false; otherwise true.

Time Complexity: O(n * m)
Space Complexity: O(n + m)

Pattern: Matrix Traversal / Prefix-style aggregation
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool sumOfRowCol(vector<vector<int>>& mat) {
        int n = (int)mat.size();
        int m = (int)mat[0].size();

        vector<long long> rowSum(n, 0), colSum(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
            }
        }

        int limit = min(n, m);
        for (int i = 0; i < limit; i++) {
            if (rowSum[i] != colSum[i]) {
                return false;
            }
        }

        return true;
    }
};

