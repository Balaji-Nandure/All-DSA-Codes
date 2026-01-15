#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Maximum Sum of Non-Adjacent Elements (House Robber)
 *
 * LeetCode 198: House Robber
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/stickler-theif/0
 *
 * Find maximum sum by picking elements such that no two are adjacent.
 *
 * Choices at each index:
 * - Pick: arr[i] + maxSum(i-2) (skip previous)
 * - Not Pick: maxSum(i-1) (can pick previous)
 *
 * Example: arr = [2, 1, 4, 9]
 * Pick: 2, 9 -> Sum = 11 (maximum)
 *
 * Time: O(n) with DP
 * Space: O(n) with DP, O(1) space optimized
 */

// Recursive approach
int maxSumNonAdjacent(int idx, vector<int> &arr){
    // Base case: no elements left
    if(idx < 0) return 0;
    // Base case: only one element, must pick it
    // if(idx == 0) return arr[0]; // this will be taken care of in the base case
    
    // Two choices:
    // 1. Pick current: arr[idx] + maxSum(idx-2) (skip previous)
    int pick = arr[idx] + maxSumNonAdjacent(idx - 2, arr);
    // 2. Not pick: maxSum(idx-1) (can pick previous)
    int notPick = maxSumNonAdjacent(idx - 1, arr);
    
    return max(pick, notPick);
}

// recursive but loop method
int maxSumNonAdjacent_loop(int start, vector<int> &arr) {

    // no elements left
    if (start < 0) return 0;

    int best = 0;

    // try picking ANY element end from start down to 0
    // not pick case is handled by the loop itself
    for (int end = start; end >= 0; end--) { 
        int take = arr[end] + maxSumNonAdjacent_loop(end - 2, arr);
        best = max(best, take);
    }

    return best;
}

// reverse loop method
int maxSumNonAdjacent_loop_reverse(int start, vector<int> &arr) {
    int n = (int)arr.size();

    // Base case: nothing left to pick
    if (start >= n) return 0;

    int best = 0;  // best sum we can get starting from 'start'

    // Try picking any element from index 'start' to 'n-1'
    for (int end = start; end < n; end++) {

        // If we pick arr[end], next allowed index is end + 2 (skip adjacent)
        //---------call function like this-------------------(0, arr)
        int take = arr[end] + maxSumNonAdjacent_loop_reverse(end + 2, arr);

        // Keep track of the maximum
        best = max(best, take);
    }

    return best;
}


// Memoization approach (Top-down DP)
int maxSumNonAdjacentMemoization(int idx, vector<int> &arr, vector<int> &dp){
    // Base cases
    if(idx < 0) return 0;
    if(idx == 0) return arr[0];
    // Return cached result
    if(dp[idx] != -1) return dp[idx];
    
    // Compute and store result
    int pick = arr[idx] + maxSumNonAdjacentMemoization(idx - 2, arr, dp);
    int notPick = maxSumNonAdjacentMemoization(idx - 1, arr, dp);
    
    return dp[idx] = max(pick, notPick);
}

// Tabulation approach (Bottom-up DP)
int maxSumNonAdjacentTabulation(int n, vector<int> &arr){
    if(n == 0) return 0;
    if(n == 1) return arr[0];
    
    vector<int> dp(n, 0);
    dp[0] = arr[0]; // Base case
    dp[1] = max(arr[0], arr[1]); // Can pick either first or second
    
    // Fill dp array
    for(int i = 2; i < n; i++){
        int pick = arr[i] + dp[i - 2]; // Pick current, skip previous
        int notPick = dp[i - 1]; // Skip current, can pick previous
        dp[i] = max(pick, notPick);
    }
    
    return dp[n - 1];
}

// Space optimization (only need last 2 values)
int maxSumNonAdjacentSpaceOptimization(int n, vector<int> &arr){
    if(n == 0) return 0;
    if(n == 1) return arr[0];
    
    int prev2 = arr[0]; // dp[0]
    int prev1 = max(arr[0], arr[1]); // dp[1]
    
    for(int i = 2; i < n; i++){
        int pick = arr[i] + prev2; // Pick current
        int notPick = prev1; // Skip current
        int curr = max(pick, notPick);
        // Update for next iteration
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

signed main() {
    vector<int> arr = {2, 1, 4, 9};
    int n = arr.size();
    
    int recursive = maxSumNonAdjacent(n - 1, arr);
    int recursive_loop = maxSumNonAdjacent_loop(n - 1, arr);
    int recursive_loop_reverse = maxSumNonAdjacent_loop_reverse(0, arr);
    
    vector<int> dp1(n, -1);
    int memoization = maxSumNonAdjacentMemoization(n - 1, arr, dp1);
    
    int tabulation = maxSumNonAdjacentTabulation(n, arr);
    int spaceOptimization = maxSumNonAdjacentSpaceOptimization(n, arr);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Recursive Loop: " << recursive_loop << endl;
    cout << "Recursive Loop Reverse: " << recursive_loop_reverse << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

