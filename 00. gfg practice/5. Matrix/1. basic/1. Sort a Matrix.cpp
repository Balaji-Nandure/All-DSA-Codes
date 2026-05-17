/*
Problem: Sort a Matrix

GFG: https://www.geeksforgeeks.org/problems/sort-a-matrix/1

Description:
Given an n x n matrix, return the matrix after sorting all elements in
non-decreasing order.

Examples:

Input:
[[10, 20, 30, 40],
 [15, 25, 35, 45],
 [27, 29, 37, 48],
 [32, 33, 39, 50]]

Output:
[[10, 15, 20, 25],
 [27, 29, 30, 32],
 [33, 35, 37, 39],
 [40, 45, 48, 50]]

Input:
[[1, 5, 3],
 [2, 8, 7],
 [4, 6, 9]]

Output:
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]

Constraints:
1 <= n <= 1000
1 <= mat[i][j] <= 10^5

Approach:
1) Flatten all n*n elements into a 1D vector.
2) Sort the vector.
3) Fill the matrix row-wise using sorted values.

Time Complexity: O(n^2 log(n^2)) = O(n^2 log n)
Space Complexity: O(n^2)

Pattern: Matrix + Sorting
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<vector<int>> sortedMatrix(int N, vector<vector<int>> Mat) {
        vector<int> values;
        values.reserve(N * N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                values.push_back(Mat[i][j]);
            }
        }

        sort(values.begin(), values.end());

        int idx = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Mat[i][j] = values[idx++];
            }
        }

        return Mat;
    }
};

