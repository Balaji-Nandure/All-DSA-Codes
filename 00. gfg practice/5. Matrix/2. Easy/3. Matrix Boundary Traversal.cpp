/*
GeeksforGeeks: Matrix Boundary Traversal
Difficulty: Easy

Problem:
Return all boundary elements of the matrix
in clockwise order.

Example:

1  2  3  4
5  6  7  8
9 10 11 12
13 14 15 16

Output:
1 2 3 4 8 12 16 15 14 13 9 5

Approach:
Boundary consists of:

1. Top row
2. Right column (excluding top)
3. Bottom row (excluding right corner)
4. Left column (excluding top and bottom)

Special Cases:
1. Single row
2. Single column

Time Complexity: O(R + C)
Space Complexity: O(1) extra
(ignoring output array)

GFG Link:
https://www.geeksforgeeks.org/problems/boundary-traversal-of-matrix/1
*/

class Solution {
public:

    vector<int> boundaryTraversal(vector<vector<int>>& mat) {

        int n = mat.size();
        int m = mat[0].size();

        vector<int> ans;

        // Single row
        if(n == 1) {

            for(int j = 0; j < m; j++)
                ans.push_back(mat[0][j]);

            return ans;
        }

        // Single column
        if(m == 1) {

            for(int i = 0; i < n; i++)
                ans.push_back(mat[i][0]);

            return ans;
        }

        // Top row
        for(int j = 0; j < m; j++)
            ans.push_back(mat[0][j]);

        // Right column
        for(int i = 1; i < n; i++)
            ans.push_back(mat[i][m - 1]);

        // Bottom row
        for(int j = m - 2; j >= 0; j--)
            ans.push_back(mat[n - 1][j]);

        // Left column
        for(int i = n - 2; i >= 1; i--)
            ans.push_back(mat[i][0]);

        return ans;
    }
};

/*
Dry Run:

1  2  3  4
5  6  7  8
9 10 11 12
13 14 15 16

Top    : 1 2 3 4
Right  : 8 12 16
Bottom : 15 14 13
Left   : 9 5

Answer:
1 2 3 4 8 12 16 15 14 13 9 5

Final Summary:
Top Row
→ Right Column
→ Bottom Row
→ Left Column
(clockwise boundary traversal)
*/