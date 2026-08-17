/*
    Problem Name: Median in a Row-Wise Sorted Matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a row-wise sorted matrix mat[][] of size n x m, where n and m are always odd integers.
    Return the median of the matrix.
    The median is the middle element when all n * m elements are sorted in ascending order.

    Examples:
    Input: mat[][] = [[1, 3, 5],
                      [2, 6, 9],
                      [3, 6, 9]]
    Output: 5
    Explanation: Sorted elements = [1, 2, 3, 3, 5, 6, 6, 9, 9]. Median = 5.

    Input: mat[][] = [[2, 4, 9],
                      [3, 6, 7],
                      [4, 7, 10]]
    Output: 6
    Explanation: Sorted elements = [2, 3, 4, 4, 6, 7, 7, 9, 10]. Median = 6.

    Input: mat[][] = [[3],
                      [4],
                      [8]]
    Output: 4

    Constraints:
    1 <= n, m <= 400
    1 <= mat[i][j] <= 2000
    n and m are always odd.

    Expected Complexities:
    Time Complexity: O(32 * n * log(m)), using Binary Search on Range + upper_bound.
    Space Complexity: O(1), no extra space.

    Love Babbar Style Approach:
    Binary Search on Value Range (Range Binary Search + upper_bound):

    1. INTUITION:
       - Since each row of the matrix is already sorted:
         * The minimum element in the matrix is the minimum of the first column: `low = min(mat[i][0])`.
         * The maximum element in the matrix is the maximum of the last column: `high = max(mat[i][m-1])`.
       - Total elements in matrix = `n * m` (which is odd).
       - The median is the element such that there are AT LEAST `reqCount = (n * m + 1) / 2` elements `<= median`.
       - We perform Binary Search on the value range `[low, high]`:
         * For candidate `mid = low + (high - low) / 2`:
           - Count how many elements in the entire matrix are `<= mid`.
           - Since each row is sorted, number of elements `<= mid` in row `i` is given by:
             `upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin()`.
           - Sum this count across all `n` rows.
         * If `count < reqCount`: `mid` is too small -> `low = mid + 1`.
         * If `count >= reqCount`: `mid` can be a median candidate -> record `ans = mid` and search smaller range `high = mid - 1`.

    2. ALGORITHM:
       - `median(mat)`:
         * `int n = mat.size(), m = mat[0].size();`
         * `int low = INT_MAX, high = INT_MIN;`
         * For `i` from `0` to `n - 1`:
           `low = min(low, mat[i][0]);`
           `high = max(high, mat[i][m - 1]);`
         * `int reqCount = (n * m + 1) / 2;`
         * While (`low <= high`):
           - `int mid = low + (high - low) / 2;`
           - `int count = 0;`
           - For `i` from `0` to `n - 1`:
             `count += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();`
           - If (`count < reqCount`) `low = mid + 1;`
           - Else `high = mid - 1;`
         * Return `low`.

    Dry Run:
    mat = [[1, 3, 5], [2, 6, 9], [3, 6, 9]], n=3, m=3, reqCount = 5
    - low = 1, high = 9
    - mid = 5 -> count = 3 + 1 + 1 = 5 >= 5 -> high = 4
    - mid = 2 -> count = 1 + 1 + 0 = 2 < 5  -> low = 3
    - mid = 3 -> count = 2 + 1 + 1 = 4 < 5  -> low = 4
    - mid = 4 -> count = 2 + 1 + 1 = 4 < 5  -> low = 5
    - Loop ends. Returns low = 5 ✓
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    // GFG Signature - Binary Search on Range
    int median(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        int low = INT_MAX;
        int high = INT_MIN;

        // Step 1: Find global minimum and maximum bounds from sorted rows
        for (int i = 0; i < n; i++) {
            low = min(low, mat[i][0]);
            high = max(high, mat[i][m - 1]);
        }

        // Target count of elements <= median
        int reqCount = (n * m + 1) / 2;

        // Step 2: Binary search on range [low, high]
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 0;

            // Count number of elements <= mid across all rows
            for (int i = 0; i < n; i++) {
                count += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }

            if (count < reqCount) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Expected Output: 5
    vector<vector<int>> mat1 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    cout << "Example 1 Median: " << ob.median(mat1) << "\n";

    // Example 2:
    // Expected Output: 6
    vector<vector<int>> mat2 = {
        {2, 4, 9},
        {3, 6, 7},
        {4, 7, 10}
    };
    cout << "Example 2 Median: " << ob.median(mat2) << "\n";

    // Example 3:
    // Expected Output: 4
    vector<vector<int>> mat3 = {
        {3},
        {4},
        {8}
    };
    cout << "Example 3 Median: " << ob.median(mat3) << "\n";

    return 0;
}
