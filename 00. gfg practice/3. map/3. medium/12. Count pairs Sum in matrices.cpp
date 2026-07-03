/*
    Problem Name: Count pairs Sum in matrices
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two matrices mat1[][] and mat2[][] of size n x n, where the elements in each matrix are arranged in strictly ascending order. Specifically, each row is sorted from left to right, and the last element of a row is smaller than the first element of the next row.
    You're given a target value x, your task is to find and count all pairs {a, b} such that a is from mat1 and b is from mat2 where the sum of a + b is equal to x.

    Expected Complexities:
    Time Complexity: O(N^2), where N is the size of the row/column of the matrix. We traverse both matrices simultaneously using a two-pointer approach, which takes at most 2 * (N^2) steps.
    Space Complexity: O(1), as we are only using a few integer variables to track our pointers and the total count.

    Love Babbar Style Approach:
    1. The given matrices are sorted in row-major order. We can visualize them as strictly sorted 1D arrays of size N*N.
    2. Since they are sorted, we can use the classic two-pointer technique to find pairs with sum = x.
    3. Initialize two pointers:
       - `ptr1 = 0` (pointing to the very start of the virtual 1D array of mat1, which represents the smallest element)
       - `ptr2 = N * N - 1` (pointing to the very end of the virtual 1D array of mat2, representing the largest element)
    4. While `ptr1 < N * N` and `ptr2 >= 0`:
       a. Calculate their exact 2D indices using division and modulo:
          - `r1 = ptr1 / N`, `c1 = ptr1 % N`
          - `r2 = ptr2 / N`, `c2 = ptr2 % N`
       b. Extract the elements: `val1 = mat1[r1][c1]` and `val2 = mat2[r2][c2]`.
       c. Check the sum `val1 + val2`:
          - If it perfectly matches `x`: We found a valid pair! Increment the `count`, move `ptr1` forward, and move `ptr2` backward. (Since all elements are strictly ascending and unique, the current elements can't be part of any other valid pair).
          - If the sum is `< x`: We need a larger sum, so we must increase `val1` by moving `ptr1` forward.
          - If the sum is `> x`: We need a smaller sum, so we must decrease `val2` by moving `ptr2` backward.
    5. Return the total `count`.

    Dry Run:
    Input: n = 2, x = 10
    mat1 = [[1, 2], [3, 4]]
    mat2 = [[4, 5], [6, 7]]
    
    ptr1 = 0 (val1 = 1), ptr2 = 3 (val2 = 7). sum = 8 < 10. ptr1++ -> 1.
    ptr1 = 1 (val1 = 2), ptr2 = 3 (val2 = 7). sum = 9 < 10. ptr1++ -> 2.
    ptr1 = 2 (val1 = 3), ptr2 = 3 (val2 = 7). sum = 10 == 10. Matches! count = 1. ptr1++ -> 3, ptr2-- -> 2.
    ptr1 = 3 (val1 = 4), ptr2 = 2 (val2 = 6). sum = 10 == 10. Matches! count = 2. ptr1++ -> 4, ptr2-- -> 1.
    ptr1 = 4, loop terminates as ptr1 < 4 is false.
    Result = 2. Matches expected output!
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countPairs(vector<vector<int>> &mat1, vector<vector<int>> &mat2, int n, int x) {
        // Pointers for virtual 1D arrays
        int ptr1 = 0;
        int ptr2 = n * n - 1;
        
        int count = 0;
        
        // Traverse using Two-Pointer approach
        while (ptr1 < n * n && ptr2 >= 0) {
            // Map 1D index to 2D coordinates for mat1
            int r1 = ptr1 / n;
            int c1 = ptr1 % n;
            int val1 = mat1[r1][c1];
            
            // Map 1D index to 2D coordinates for mat2
            int r2 = ptr2 / n;
            int c2 = ptr2 % n;
            int val2 = mat2[r2][c2];
            
            int sum = val1 + val2;
            
            if (sum == x) {
                count++;
                ptr1++;
                ptr2--;
            } else if (sum < x) {
                ptr1++;
            } else {
                ptr2--;
            }
        }
        
        return count;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, x;
            cin >> n >> x;
            
            vector<vector<int>> mat1(n, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> mat1[i][j];
                }
            }
            
            vector<vector<int>> mat2(n, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> mat2[i][j];
                }
            }
            
            Solution ob;
            cout << ob.countPairs(mat1, mat2, n, x) << "\n";
        }
    }
    return 0;
}
