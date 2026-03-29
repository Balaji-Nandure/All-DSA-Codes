/*
Problem: Row with Maximum Number of 1s

GFG: https://www.geeksforgeeks.org/find-the-row-with-maximum-number-1s/

Description: You are given a 2D binary array arr[][] consisting of only 1s and 0s. Each row of the array is sorted in non-decreasing order. Your task is to find and return the index of the first row that contains the maximum number of 1s. If no such row exists, return -1.

Note:
The array follows 0-based indexing.
The number of rows and columns in the array are denoted by n and m respectively.

Examples:

Input: arr[][] = [[0,1,1,1], [0,0,1,1], [1,1,1,1], [0,0,0,0]]
Output: 2
Explanation: Row 2 contains the most number of 1s (4 1s). Hence, output is 2.
Input: arr[][] = [[0,0], [1,1]]
Output: 1
Explanation: Row 1 contains the most number of 1s (2 1s). Hence, output is 1.
Input: arr[][] = [[0,0], [0,0]]
Output: -1
Explanation: No row contains any 1s, so output is -1.

Constraints:
1 ≤ arr.size(), arr[i].size() ≤ 103
0 ≤ arr[i][j] ≤ 1

Striver Intuition:

Since each row is sorted (0s first, then 1s),
the number of 1s in a row = m - (index of first 1).

So the problem reduces to:
Find the row which has the leftmost '1'.

Brute Force:
- Count number of 1s in each row
- TC = O(n * m)

Better:
- For each row, use Binary Search to find first 1
- TC = O(n * log m)

Optimal (Striver approach):
Start from top-right corner and move:
- If element == 1 → move left
- If element == 0 → move down

Why this works?
Because rows are sorted:
Moving left → more 1s in that row
Moving down → try next row

This way we traverse at most (n + m).

Pattern:
Matrix + Sorted Rows/Columns → Start from Top Right Corner

Time Complexity: O(n + m)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rowWithMax1s(vector<vector<int>> &arr) {
        int n = arr.size();
        int m = arr[0].size();

        int row = 0;
        int col = m - 1;
        int ans = -1;

        while (row < n && col >= 0) {
            if (arr[row][col] == 1) {
                ans = row;   // possible answer
                col--;       // move left to find more 1s
            } else {
                row++;       // move down
            }
        }

        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. Rows are sorted → number of 1s depends on first occurrence of 1.
2. We need row with leftmost 1.
3. Start from top-right:
      If 1 → move left
      If 0 → move down
4. This ensures O(n + m) solution.
5. Very common pattern:
      "Sorted Matrix → Start from Top Right"

Memory Trick:
Top Right se chalo → Left = 1, Down = 0
*/
