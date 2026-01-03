/*
Problem:
Transpose of a Matrix

Given a matrix mat[][] of size n × m,
find its transpose.

Definition:
The transpose of a matrix is obtained by converting all rows into columns.
For a matrix mat:
transpose[j][i] = mat[i][j]

Examples:
Input:
mat = [
  [1, 2, 3],
  [4, 5, 6]
]

Output:
[
  [1, 4],
  [2, 5],
  [3, 6]
]

Input:
mat = [
  [1, 2],
  [3, 4]
]

Output:
[
  [1, 3],
  [2, 4]
]


-----------------------------------
Approach 1: Extra Matrix (General Case)
-----------------------------------
1. Create a new matrix of size m × n.
2. For each cell mat[i][j], assign:
      trans[j][i] = mat[i][j]
3. Return the transposed matrix.

Why this works:
- Directly follows the mathematical definition of transpose.
- Works for both square and rectangular matrices.

Time Complexity:
O(n × m)

Space Complexity:
O(n × m)


-----------------------------------
Approach 2: In-place Transpose (Only for Square Matrix)
-----------------------------------
1. Applicable only when n == m.
2. Traverse only upper triangle of matrix.
3. Swap mat[i][j] with mat[j][i] for all i < j.

Why this works:
- Avoids extra space.
- Each element is swapped exactly once.

Time Complexity:
O(n × n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/transpose-matrix-single-line-using-loop/

LeetCode:
https://leetcode.com/problems/transpose-matrix/
*/


// ------------------------------------------------------------
// Approach 1: Using Extra Matrix (Works for all matrices)
// ------------------------------------------------------------
vector<vector<int>> transpose_ExtraSpace(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    vector<vector<int>> trans(m, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            trans[j][i] = mat[i][j];
        }
    }

    return trans;
}


// ------------------------------------------------------------
// Approach 2: In-place Transpose (Only for Square Matrix)
// ------------------------------------------------------------
void transpose_InPlace(vector<vector<int>>& mat) {
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }
}
