#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Subset Sum Equal to Target
Given an array of integers and a target sum, determine if there exists a subset 
of the array that sums to exactly the target.

Constraints:
- Each element can be used at most once
- We can either pick an element or skip it
- Return true if subset exists, false otherwise

Example:
arr = [1, 2, 3, 4], target = 7
Subset: [3, 4] -> Sum = 7
Answer = true

Recurrence:
dp[i][target] = can we achieve target sum using elements from index 0 to i
dp[i][target] = dp[i-1][target] OR dp[i-1][target - arr[i]]
Base cases:
- dp[i][0] = true (empty subset always sums to 0)
- dp[0][arr[0]] = true (if first element equals target)
*/

// Recursive approach
bool subsetSumRec(int idx, int target, vector<int> &arr) {
    // Base case: target achieved (empty subset sums to 0)
    if (target == 0) return true;
    // Base case: no elements left, target not achieved
    if (idx < 0) return false;
    
    // Two choices:
    // 1. PICK: Include arr[idx], check if we can achieve (target - arr[idx]) with remaining
    bool pick = false;
    if (target >= arr[idx]) {
        pick = subsetSumRec(idx - 1, target - arr[idx], arr);
    }
    // 2. NOT PICK: Skip arr[idx], check if we can achieve target with remaining
    bool notPick = subsetSumRec(idx - 1, target, arr);
    
    return pick || notPick; // Return true if either choice works
}

// memoization approach
bool subsetSumMemo(int idx, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if (target == 0) return true;
    if (idx < 0) return false;
    
    if (dp[idx][target] != -1) return dp[idx][target]; // already computed
    
    bool pick = false;
    if (target >= arr[idx]) {
        pick = subsetSumMemo(idx - 1, target - arr[idx], arr, dp);
    }
    bool notPick = subsetSumMemo(idx - 1, target, arr, dp);
    
    return dp[idx][target] = (pick || notPick);
}

// Tabulation approach (Bottom-up DP)
bool subsetSumTab(int n, int target, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
    
    // Base case: target = 0 is always achievable (empty subset)
    for (int i = 0; i < n; i++) {
        dp[i][0] = true;
    }
    
    // Base case: first element
    if (arr[0] <= target) {
        dp[0][arr[0]] = true; // Can achieve target = arr[0] using first element
    }
    
    // Fill dp table: dp[i][t] = can we achieve target t using elements 0 to i
    for (int i = 1; i < n; i++) {
        for (int t = 1; t <= target; t++) {
            bool pick = false;
            // Pick arr[i]: check if we can achieve (t - arr[i]) with previous elements
            if (t >= arr[i]) {
                pick = dp[i - 1][t - arr[i]];
            }
            // Not pick arr[i]: check if we can achieve t with previous elements
            bool notPick = dp[i - 1][t];
            dp[i][t] = pick || notPick;
        }
    }
    
    return dp[n - 1][target];
}

// Space optimization (only need previous row)
bool subsetSumSpaceOpt(int n, int target, vector<int> &arr) {
    // Only track previous row (size target+1)
    vector<bool> prev(target + 1, false);
    
    // Base case: target = 0 is always achievable
    prev[0] = true;
    
    // Base case: first element
    if (arr[0] <= target) {
        prev[arr[0]] = true;
    }
    
    // Process from index 1 to n-1
    for (int i = 1; i < n; i++) {
        vector<bool> curr(target + 1, false);
        curr[0] = true; // target = 0 is always achievable
        
        for (int t = 1; t <= target; t++) {
            bool pick = false;
            // Pick arr[i]: check previous row at (t - arr[i])
            if (t >= arr[i]) {
                pick = prev[t - arr[i]];
            }
            // Not pick: check previous row at t
            bool notPick = prev[t];
            curr[t] = pick || notPick;
        }
        
        prev = curr; // Update for next iteration
    }
    
    return prev[target];
}

signed main() {
    vector<int> arr = {1, 2, 3, 4};
    int n = arr.size();
    int target = 7;
    
    // Recursive
    bool ansRec = subsetSumRec(n - 1, target, arr);
    
    // Memoization
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    bool ansMemo = subsetSumMemo(n - 1, target, arr, dp);
    
    // Tabulation
    bool ansTab = subsetSumTab(n, target, arr);
    
    // Space Optimized
    bool ansSpace = subsetSumSpaceOpt(n, target, arr);
    
    cout << "Recursive:        " << (ansRec ? "true" : "false") << endl;
    cout << "Memoization:      " << (ansMemo ? "true" : "false") << endl;
    cout << "Tabulation:       " << (ansTab ? "true" : "false") << endl;
    cout << "Space Optimized:  " << (ansSpace ? "true" : "false") << endl;
    
    return 0;
}

