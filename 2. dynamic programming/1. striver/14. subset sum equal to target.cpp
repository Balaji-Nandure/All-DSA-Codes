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

// recursive approach
bool subsetSumRec(int idx, int target, vector<int> &arr) {
    if (target == 0) return true; // base case: target achieved
    if (idx < 0) return false; // base case: no elements left
    
    // Two choices:
    // 1. Pick current element: check if we can achieve (target - arr[idx]) with remaining elements
    // 2. Skip current element: check if we can achieve target with remaining elements
    bool pick = false;
    if (target >= arr[idx]) {
        pick = subsetSumRec(idx - 1, target - arr[idx], arr);
    }
    bool notPick = subsetSumRec(idx - 1, target, arr);
    
    return pick || notPick;
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

// tabulation approach
bool subsetSumTab(int n, int target, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
    
    // Base case: target = 0 is always achievable (empty subset)
    for (int i = 0; i < n; i++) {
        dp[i][0] = true;
    }
    
    // Base case: first element
    if (arr[0] <= target) {
        dp[0][arr[0]] = true;
    }
    
    // Fill the dp table
    for (int i = 1; i < n; i++) {
        for (int t = 1; t <= target; t++) {
            bool pick = false;
            if (t >= arr[i]) {
                pick = dp[i - 1][t - arr[i]];
            }
            bool notPick = dp[i - 1][t];
            dp[i][t] = pick || notPick;
        }
    }
    
    return dp[n - 1][target];
}

// space optimization approach
bool subsetSumSpaceOpt(int n, int target, vector<int> &arr) {
    // We only need previous row, so use 1D array
    vector<bool> prev(target + 1, false);
    
    // Base case: target = 0
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
            if (t >= arr[i]) {
                pick = prev[t - arr[i]];
            }
            bool notPick = prev[t];
            curr[t] = pick || notPick;
        }
        
        prev = curr;
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

