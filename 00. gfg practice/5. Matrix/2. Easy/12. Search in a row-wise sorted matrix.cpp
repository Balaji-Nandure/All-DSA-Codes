/*
GeeksforGeeks: Search in a row-wise sorted matrix
Difficulty: Easy

Problem:
Given a row-wise sorted 2D matrix mat[][] of size n x m and an integer x, 
find whether element x is present in the matrix.
Note: In a row-wise sorted matrix, each row is sorted in itself, i.e. for 
any i, j within bounds, mat[i][j] <= mat[i][j+1]. But there is NO ordering 
guarantee between different rows.

Example 1:
Input: 
mat[][] = [[3, 4, 9],
           [2, 5, 6],
           [9, 25, 27]]
x = 9
Output: true
Explanation: 9 is present in the matrix, so the output is true.

Example 2:
Input: 
mat[][] = [[19, 22, 27, 38, 55, 67]]
x = 56
Output: false
Explanation: 56 is not present in the matrix, so the output is false.

Core Idea:
Because the matrix is row-wise sorted, we know that every single row is strictly 
sorted from left to right. However, since there is no relationship or ordering 
between different rows (e.g., Row 2 can have smaller numbers than Row 1), we 
must check every row.

Instead of doing a slow linear scan (checking every single element one by one), 
we can significantly speed up the search by performing a **Binary Search** on 
each individual row!

Approach:
1. Loop through each row `i` from `0` to `n - 1`.
2. Use C++'s built-in `std::binary_search` on `mat[i]`.
   - `binary_search` takes a start iterator, end iterator, and target value, 
     and returns `true` if it finds the element in the sorted range.
3. If `binary_search` returns `true` for any row, immediately return `true`.
4. If the loop completes and we haven't found the element, return `false`.

Time Complexity : O(N * log M) — We iterate through N rows, and do a Binary Search (log M) on each.
Space Complexity: O(1) — No extra space is required.

GFG Link:
https://www.geeksforgeeks.org/problems/search-in-a-row-wise-sorted-matrix/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Function to search a given number in row-wise sorted matrix.
    bool searchRowMatrix(vector<vector<int>> &mat, int x) {
        int n = mat.size();
        
        // Check each row individually
        for (int i = 0; i < n; i++) {
            
            // Since the row is sorted, we can use Binary Search!
            if (binary_search(mat[i].begin(), mat[i].end(), x)) {
                return true;
            }
        }
        
        // If we exhausted all rows and didn't find x, it's not in the matrix
        return false;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[3, 4, 9],
           [2, 5, 6],
           [9, 25, 27]]
x = 9

i = 0 (Row 1): [3, 4, 9]
  - binary_search([3, 4, 9], 9)
  - Mid is 4 (index 1). 9 > 4, search right half: [9]
  - Mid is 9. Match found! Returns true.

Result: true ✓
*/
