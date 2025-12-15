
/*
 * Problem: Triangle (Minimum Path Sum in Triangular Array)
 *
 * LeetCode 120: Triangle
 * GeeksforGeeks: https://www.geeksforgeeks.org/minimum-sum-path-triangle/
 *
 * Given a triangular array/list 'TRIANGLE', return the minimum path sum to reach from 
the top to the bottom row.

The triangle array will have N rows and the i-th row (where 0 <= i < N) will have i + 1 elements.
You can move only to the adjacent number of row below each step. For example, if you are 
at index j in row i, then you can move to index j or j + 1 in row i + 1 in each step.

Constraints:
- Can only move to adjacent indices in the next row
- Find the path with minimum sum from top to bottom

Example:
TRIANGLE = [[1],
            [2, 3],
            [3, 6, 7],
            [8, 9, 6, 1]]
Minimum path: 1 -> 2 -> 3 -> 6 = 12
Or: 1 -> 3 -> 6 -> 1 = 11
Minimum = 11

Recurrence (Top-Down):
dp[i][j] = minimum sum to reach cell (i, j) from top
dp[i][j] = triangle[i][j] + min(dp[i-1][j-1], dp[i-1][j])
Base cases:
- dp[0][0] = triangle[0][0]
- For first element in each row: dp[i][0] = triangle[i][0] + dp[i-1][0]
- For last element in each row: dp[i][i] = triangle[i][i] + dp[i-1][i-1]
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

// recursive approach
int triangleMinPathRec(int i, int j, vector<vector<int>> &triangle, int n) {
    // if (i == n - 1) return triangle[i][j]; // base case: last row
    if (i == n) return 0;
    
    int down = triangleMinPathRec(i + 1, j, triangle, n); // move down
    int diag = triangleMinPathRec(i + 1, j + 1, triangle, n); // move diagonal
    
    return triangle[i][j] + min(down, diag);
}

// memoization approach
int triangleMinPathMemo(int i, int j, vector<vector<int>> &triangle, int n, vector<vector<int>> &dp) {
    if (i == n - 1) return triangle[i][j];
    if (dp[i][j] != -1) return dp[i][j]; // already computed
    
    int down = triangleMinPathMemo(i + 1, j, triangle, n, dp);
    int diag = triangleMinPathMemo(i + 1, j + 1, triangle, n, dp);
    
    return dp[i][j] = triangle[i][j] + min(down, diag);
}

// tabulation approach
int triangleMinPathTab(int n, vector<vector<int>> &triangle) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // base case: last row
    for (int j = 0; j < n; j++) {
        dp[n - 1][j] = triangle[n - 1][j];
    }
    
    // fill from bottom to top
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int down = dp[i + 1][j];
            int diag = dp[i + 1][j + 1];
            dp[i][j] = triangle[i][j] + min(down, diag);
        }
    }
    
    return dp[0][0];
}

// tabulation approach 2
// in this we are going from top to bottom.
// Just for understanding purpose.
int triangleMinPathTab2(int n, vector<vector<int>> &triangle) {
    vector<vector<int>> dp(n, vector<int>(n, 1e18));

    // Base case: top
    dp[0][0] = triangle[0][0];

    // Fill DP from row 1 to n-1
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {

            int upLeft = 1e18, up = 1e18;

            if (j > 0)            // from (i-1, j-1)
                upLeft = dp[i - 1][j - 1];

            if (j < i)            // from (i-1, j)
                up = dp[i - 1][j];

            dp[i][j] = triangle[i][j] + min(upLeft, up);
        }
    }

    // answer is min value in the last row
    int ans = 1e18;
    for (int j = 0; j < n; j++) ans = min(ans, dp[n - 1][j]);

    return ans;
}


// space optimization approach
int triangleMinPathSpaceOpt(int n, vector<vector<int>> &triangle) {
    vector<int> prev(n, 0);
    
    // base case: last row
    for (int j = 0; j < n; j++) {
        prev[j] = triangle[n - 1][j];
    }
    
    // process from bottom to top, only keep previous row
    for (int i = n - 2; i >= 0; i--) {
        vector<int> curr(n, 0);
        for (int j = 0; j <= i; j++) {
            int down = prev[j];
            int diag = prev[j + 1];
            curr[j] = triangle[i][j] + min(down, diag);
        }
        prev = curr;
    }
    
    return prev[0];
}

signed main() {

    vector<vector<int>> triangle = {
        {1},
        {2, 3},
        {3, 6, 7},
        {8, 9, 6, 1}
    };

    int n = triangle.size();

    // Recursive
    int ansRec = triangleMinPathRec(0, 0, triangle, n);

    // Memoization
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int ansMemo = triangleMinPathMemo(0, 0, triangle, n, dp);

    // Tabulation
    int ansTab = triangleMinPathTab(n, triangle);

    // Space Optimized
    int ansSpace = triangleMinPathSpaceOpt(n, triangle);

    cout << "Recursive:        " << ansRec << endl;
    cout << "Memoization:      " << ansMemo << endl;
    cout << "Tabulation:       " << ansTab << endl;
    cout << "Space Optimized:  " << ansSpace << endl;

    return 0;
}
