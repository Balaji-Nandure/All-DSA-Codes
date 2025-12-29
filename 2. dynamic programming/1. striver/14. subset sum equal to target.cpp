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

// 1. Recursive approach pick or not-pick
class SubsetSumRecursive {
public:
    bool solve(int idx, vector<int> &arr, int sum){
        if(sum == 0) return true;
        if(sum < 0) return false;
        if(idx == arr.size()) return false;
        // Pick
        bool pick = solve(idx + 1, arr, sum - arr[idx]);
        if(pick) return true;
        // Not pick
        return solve(idx + 1, arr, sum);
    }
    bool isSubsetSum(vector<int>& arr, int sum) {
        return solve(0, arr, sum);
    }
};

// 2. Recursive approach using for loop
class SubsetSumRecursiveForLoop {
public:
    bool solve(int idx, vector<int>& arr, int sum) {
        if (sum == 0) return true;
        if (sum < 0) return false;
        for (int i = idx; i < arr.size(); i++) {
            if (solve(i + 1, arr, sum - arr[i])) {
                return true;
            }
        }
        return false;
    }
    bool isSubsetSum(vector<int>& arr, int sum) {
        return solve(0, arr, sum);
    }
};

// 3. Memoization (top-down DP)
class SubsetSumMemoization {
public:
    // Returns true if there is a subset from arr[0..idx] with sum = target
    bool solve(int idx, int target, vector<int> &arr, vector<vector<int>> &dp) {
        // Base Case: target achieved (empty subset sum)
        if (target == 0) return true;
        if (idx < 0 || target < 0) return false;

        // If already solved, return cached result
        if (dp[idx][target] != -1) return dp[idx][target];

        // Try including the current element arr[idx], if possible
        bool pick = solve(idx - 1, target - arr[idx], arr, dp);;

        // Try excluding the current element
        bool notPick = solve(idx - 1, target, arr, dp);

        // Save and return if either pick or notPick is true
        return dp[idx][target] = (pick || notPick);
    }

    // Public method to check if subset sum equals sum
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        // dp[i][t] = -1 means not calculated, 1:true, 0:false
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return solve(n - 1, sum, arr, dp);
    }
};

// 4. Tabulation approach (Bottom-up DP)
class SubsetSumTabulation {
public:
    // Returns true if there is a subset of arr[] with sum = target
    bool isSubsetSum(vector<int>& arr, int target) {
        int n = arr.size();
        // dp[i][t]: can we get t using first (i+1) items?
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

        // Base Case: sum 0 can be made with empty subset
        for (int i = 0; i < n; i++) dp[i][0] = true;

        // Base Case: using only arr[0]
        if (arr[0] <= target) dp[0][arr[0]] = true;

        // Build table
        for (int i = 1; i < n; i++) {
            for (int t = 1; t <= target; t++) {
                // Include arr[i] if t >= arr[i]
                bool pick = false;
                if (t >= arr[i]) pick = dp[i-1][t-arr[i]];
                // Exclude arr[i]
                bool notPick = dp[i-1][t];
                dp[i][t] = pick || notPick;
            }
        }
        return dp[n-1][target];
    }
};

// 5. Space Optimization (Only Previous Row)
class SubsetSumSpaceOptimized {
public:
    // Optimized version using two 1D arrays (prev, curr)
    bool isSubsetSum(vector<int>& arr, int target) {
        int n = arr.size();
        // prev[t] : can we get sum t using first (i) elements
        vector<bool> prev(target + 1, false);

        // Base case: sum 0 is always possible
        prev[0] = true;
        // Base case: sum arr[0] is possible, if arr[0] <= target
        if (arr[0] <= target) prev[arr[0]] = true;

        // Iterate for each element
        for (int i = 1; i < n; i++) {
            vector<bool> curr(target + 1, false);  // Current row
            curr[0] = true; // Always possible to make sum 0

            for (int t = 1; t <= target; t++) {
                // Include arr[i] if t >= arr[i]
                bool pick = false;
                if (t >= arr[i]) pick = prev[t - arr[i]];
                // Not include arr[i]
                bool notPick = prev[t];

                curr[t] = pick || notPick;
            }
            prev = curr; // Move to next row
        }
        return prev[target];
    }
};
