/*
GeeksforGeeks: Summed Matrix
Difficulty: Easy

Problem:
A matrix is constructed of size n*n and given an integer ‘q’. The value at every 
cell of the matrix is given as, M(i,j) = i + j, where ‘M(i,j)' is the value of a 
cell, ‘i’ is the row number, and ‘j’ is the column number. 
Return the number of cells having value ‘q’.

Note: Assume, the array is in 1-based indexing.

Example 1:
Input: n = 4, q = 7
Output: 2
Explanation: Matrix becomes:
2 3 4 5 
3 4 5 6 
4 5 6 7
5 6 7 8
The count of 7 is 2 (at positions (3,4) and (4,3)).

Example 2:
Input: n = 5, q = 4
Output: 3
Explanation: Matrix becomes:
2 3 4 5 6 
3 4 5 6 7 
4 5 6 7 8 
5 6 7 8 9 
6 7 8 9 10 
The count of 4 is 3 (at positions (1,3), (2,2), and (3,1)).

Core Idea:
Since `n` and `q` can be up to 10^18, we cannot build or simulate the matrix! 
This problem requires an O(1) mathematical observation.

We are looking for pairs `(i, j)` such that `i + j = q`.
We know the constraints for `i` and `j` in the matrix are:
1 <= i <= n
1 <= j <= n

From `i + j = q`, we can say `j = q - i`.
Substituting `j` into the boundaries of `j`:
1 <= q - i <= n

This gives us two inequalities to solve for `i`:
1. q - i >= 1  ==>  i <= q - 1
2. q - i <= n  ==>  i >= q - n

Combining this with the natural boundaries of `i` (`1 <= i <= n`), we get a 
strict range of valid values for `i`:
- The smallest valid `i` is `max(1, q - n)`
- The largest valid `i` is `min(n, q - 1)`

The number of valid `i`'s in this range is exactly the number of pairs that sum 
to `q`! If the upper bound is less than the lower bound, it simply means `q` is 
either too small (q < 2) or too large (q > 2n) to exist in the matrix.

Approach:
1. Calculate `lowerBound = max(1LL, q - n)`.
2. Calculate `upperBound = min(n, q - 1)`.
3. The count of pairs is `upperBound - lowerBound + 1`.
4. If the count is negative, return 0. Otherwise, return the count.

Time Complexity : O(1) — A few simple O(1) mathematical operations.
Space Complexity: O(1) — No extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/summed-matrix5834/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long sumMatrix(long long n, long long q) {
        // Find the lower and upper bounds for the valid row indices 'i'
        long long lower_bound = max(1LL, q - n);
        long long upper_bound = min(n, q - 1);
        
        // Calculate the number of valid 'i' values in this range
        long long count = upper_bound - lower_bound + 1;
        
        // If the range is invalid (i.e. q is outside the possible min/max sums), return 0
        if (count < 0) {
            return 0;
        }
        
        return count;
    }
};

/*
Dry Run — Example 1:
n = 4, q = 7

lower_bound = max(1LL, 7 - 4) 
            = max(1LL, 3) 
            = 3

upper_bound = min(4LL, 7 - 1) 
            = min(4LL, 6) 
            = 4

count = upper_bound - lower_bound + 1
      = 4 - 3 + 1
      = 2

Result = 2. ✓
*/
