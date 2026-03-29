/*
Problem: Spirally Traversing a Matrix

GFG: https://www.geeksforgeeks.org/spiral-traversal-of-matrix/

Description: Given a rectangular matrix mat[][] of size n x m, and your task is to return an array while traversing the matrix in spiral form.

Examples:

Input: mat[][] = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
Output: [1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10]
Explanation: 

Input: mat[][] = [[1, 2, 3, 4, 5, 6], [7, 8, 9, 10, 11, 12], [13, 14, 15, 16, 17, 18]]
Output: [1, 2, 3, 4, 5, 6, 12, 18, 17, 16, 15, 14, 13, 7, 8, 9, 10, 11]
Explanation: Applying same technique as shown above.
Input: mat[][] = [[32, 44, 27, 23], [54, 28, 50, 62]]
Output: [32, 44, 27, 23, 62, 50, 28, 54]
Explanation: Applying same technique as shown above, output will be [32, 44, 27, 23, 62, 50, 28, 54].

Constraints:
1 ≤ n, m ≤ 1000
0 ≤ mat[i][j] ≤ 100

Striver Intuition:

Spiral traversal means we move in layers:

Step-by-step movement:
1. Left → Right (Top row)
2. Top → Bottom (Right column)
3. Right → Left (Bottom row)
4. Bottom → Top (Left column)

Then we move inside the matrix and repeat.

We maintain 4 boundaries:
top = 0
bottom = n - 1
left = 0
right = m - 1

After traversing each direction, we update boundaries.

IMPORTANT:
Before traversing bottom row and left column,
we must check boundaries to avoid double printing.

Pattern:
Matrix Boundary Traversal

Time Complexity: O(n * m)
Space Complexity: O(1) (excluding result array)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spirallyTraverse(vector<vector<int>> &mat) {
        int n = mat.size();
        int m = mat[0].size();

        int top = 0, bottom = n - 1;
        int left = 0, right = m - 1;

        vector<int> ans;

        while(top <= bottom && left <= right) {

            // 1. Left → Right
            for(int i = left; i <= right; i++) {
                ans.push_back(mat[top][i]);
            }
            top++;

            // 2. Top → Bottom
            for(int i = top; i <= bottom; i++) {
                ans.push_back(mat[i][right]);
            }
            right--;

            // 3. Right → Left
            if(top <= bottom) {
                for(int i = right; i >= left; i--) {
                    ans.push_back(mat[bottom][i]);
                }
                bottom--;
            }

            // 4. Bottom → Top
            if(left <= right) {
                for(int i = bottom; i >= top; i--) {
                    ans.push_back(mat[i][left]);
                }
                left++;
            }
        }

        return ans;
    }
};

/*
Final Summary (Interview Revision):

We use 4 boundaries:
top, bottom, left, right

Movement order:
1. Left → Right
2. Top → Bottom
3. Right → Left
4. Bottom → Top

After each move, update boundary.

Important condition:
Check boundaries before printing bottom row and left column
to avoid duplicates.

Memory Trick:
"Top → Right → Bottom → Left" (TRBL Spiral)
*/
