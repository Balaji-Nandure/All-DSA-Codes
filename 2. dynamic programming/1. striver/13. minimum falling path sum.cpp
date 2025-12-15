#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Minimum Falling Path Sum
 *
 * LeetCode 931: Minimum Falling Path Sum
 * GeeksforGeeks: https://www.geeksforgeeks.org/minimum-cost-path-dp-6/
 *
 * Given an n x n matrix of integers, find the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row 
that is either directly below or diagonally left/right. Specifically, the next element from 
position (i, j) will be (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).

Constraints:
- Can start from any column in first row
- Can move down, down-left, or down-right
- Can end at any column in last row
- Find the minimum sum path

Example:
matrix = [[2, 1, 3],
          [6, 5, 4],
          [7, 8, 9]]
Minimum path: 1 -> 5 -> 7 = 13
Or: 1 -> 4 -> 7 = 12
Minimum = 12

Recurrence:
dp[i][j] = minimum sum to reach cell (i, j) from any starting point in first row
dp[i][j] = matrix[i][j] + min(dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1])
Base cases:
- dp[0][j] = matrix[0][j] for all j (can start from any column)
- Answer = min(dp[n-1][j]) for all j in last row
*/

// recursive approach
int minFallingPathSumRec(int i, int j, vector<vector<int>> &matrix, int n) {
    if (i == 0) return matrix[i][j]; // base case: first row
    if (j < 0 || j >= n) return INF; // out of bounds
    
    int up = minFallingPathSumRec(i - 1, j, matrix, n); // move up (from below)
    int upLeft = INF;
    if (j > 0) upLeft = minFallingPathSumRec(i - 1, j - 1, matrix, n); // move up-left
    int upRight = INF;
    if (j < n - 1) upRight = minFallingPathSumRec(i - 1, j + 1, matrix, n); // move up-right
    
    return matrix[i][j] + min({up, upLeft, upRight});
}

// memoization approach
int minFallingPathSumMemo(int i, int j, vector<vector<int>> &matrix, int n, vector<vector<int>> &dp) {
    if (i == 0) return matrix[i][j];
    if (j < 0 || j >= n) return INF;
    if (dp[i][j] != -1) return dp[i][j]; // already computed
    
    int up = minFallingPathSumMemo(i - 1, j, matrix, n, dp);
    int upLeft = INF;
    if (j > 0) upLeft = minFallingPathSumMemo(i - 1, j - 1, matrix, n, dp);
    int upRight = INF;
    if (j < n - 1) upRight = minFallingPathSumMemo(i - 1, j + 1, matrix, n, dp);
    
    return dp[i][j] = matrix[i][j] + min({up, upLeft, upRight});
}

// tabulation approach
int minFallingPathSumTab(int n, vector<vector<int>> &matrix) {
    // vector<vector<int>> dp(n, vector<int>(n, INF));
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // base case: first row (can start from any column)
    for (int j = 0; j < n; j++) {
        dp[0][j] = matrix[0][j];
    }
    
    // fill from row 1 to n-1
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int up = dp[i - 1][j];
            int upLeft = INF;
            if (j > 0) upLeft = dp[i - 1][j - 1];
            int upRight = INF;
            if (j < n - 1) upRight = dp[i - 1][j + 1];
            
            dp[i][j] = matrix[i][j] + min({up, upLeft, upRight});
        }
    }
    
    // answer is min value in the last row
    int ans = INF;
    for (int j = 0; j < n; j++) {
        ans = min(ans, dp[n - 1][j]);
    }

    return ans;
}

// space optimization approach
int minFallingPathSumSpaceOpt(int n, vector<vector<int>> &matrix) {
    vector<int> prev(n, 0);
    
    // base case: first row
    for (int j = 0; j < n; j++) {
        prev[j] = matrix[0][j];
    }
    
    // process from row 1 to n-1, only keep previous row
    for (int i = 1; i < n; i++) {
        vector<int> curr(n, 0);
        for (int j = 0; j < n; j++) {
            int up = prev[j];
            int upLeft = INF;
            if (j > 0) upLeft = prev[j - 1];
            int upRight = INF;
            if (j < n - 1) upRight = prev[j + 1];
            
            curr[j] = matrix[i][j] + min({up, upLeft, upRight});
        }
        prev = curr;
    }
    
    // answer is min value in the last row
    int ans = INF;
    for (int j = 0; j < n; j++) {
        ans = min(ans, prev[j]);
    }
    
    return ans;
}

signed main() {
    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };
    
    int n = matrix.size();
    
    // Recursive: try all starting positions in first row
    int ansRec = INF;
    for (int j = 0; j < n; j++) {
        ansRec = min(ansRec, minFallingPathSumRec(n - 1, j, matrix, n));
    }
    
    // Memoization: try all starting positions in first row
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int ansMemo = INF;
    for (int j = 0; j < n; j++) {
        ansMemo = min(ansMemo, minFallingPathSumMemo(n - 1, j, matrix, n, dp));
    }
    
    // Tabulation
    int ansTab = minFallingPathSumTab(n, matrix);
    
    // Space Optimized
    int ansSpace = minFallingPathSumSpaceOpt(n, matrix);
    
    cout << "Recursive:        " << ansRec << endl;
    cout << "Memoization:      " << ansMemo << endl;
    cout << "Tabulation:       " << ansTab << endl;
    cout << "Space Optimized:  " << ansSpace << endl;
    
    return 0;
}
