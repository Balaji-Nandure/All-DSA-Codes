#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Partition A Set Into Two Subsets With Minimum Absolute Sum Difference

GeeksforGeeks: https://practice.geeksforgeeks.org/problems/minimum-sum-partition3317/1

Given an array of integers, partition it into two subsets such that the 
absolute difference between the sums of the subsets is minimized.

Key Insight:
- If we partition into subsets S1 and S2, and total sum is `sum`, then:
  - S1 + S2 = sum
  - We want to minimize |S1 - S2|
  - This is equivalent to minimizing |S1 - (sum - S1)| = |2*S1 - sum|
  - Or minimizing |sum - 2*S1|
- So we need to find all possible subset sums S1, and find the one closest to sum/2
- Use subset sum DP to find all possible sums, then find minimum difference

Example:
arr = [1, 2, 3, 4]
Total sum = 10
Best partition: S1 = 5, S2 = 5, difference = 0
Or: S1 = 4, S2 = 6, difference = 2
Minimum difference = 0

DP State: dp[i][target] = can we achieve target sum using elements from index 0 to i
Recurrence:
dp[i][target] = dp[i-1][target] OR dp[i-1][target - arr[i]]
- dp[i-1][target]: not pick arr[i]
- dp[i-1][target - arr[i]]: pick arr[i] (if target >= arr[i])

Base Cases:
- dp[i][0] = true (empty subset always sums to 0)
- dp[0][arr[0]] = true (if first element equals target and arr[0] <= target)

Time Complexity: O(n * sum) where sum is total array sum
Space Complexity: O(n * sum) for memoization/tabulation, O(sum) for space optimization
*/

// 1. Recursive approach (take/not take method)
//  this method is not recommanded because of for loop and then recursion
//  even with memoisation this method is not recommanded (same reason)

// class MinPartitionDifferenceRecursive {
// public:
//     // TC: O(2^n) exponential, SC: O(n) recursion stack
//     bool solve(int idx, vector<int> &arr, int sum) {
//         // Base case: target achieved
//         if (sum == 0) return true;
//         // Base case: no more elements or sum becomes negative
//         if (idx < 0 || sum < 0) return false;
        
//         // Two choices: pick or not pick
//         bool pick = false;
//         if (sum >= arr[idx]) {
//             pick = solve(idx - 1, arr, sum - arr[idx]); // Pick current element
//         }
//         bool notPick = solve(idx - 1, arr, sum); // Not pick current element
        
//         return pick || notPick;
//     }
    
//     int minDifference(vector<int>& arr) {
//         int n = arr.size();
//         int totalSum = accumulate(arr.begin(), arr.end(), 0);
        
//         // Try all possible subset sums from 0 to totalSum/2
//         int minDiff = INF;
//         for (int s1 = 0; s1 <= totalSum / 2; s1++) {
//             if (solve(n - 1, arr, s1)) {
//                 int s2 = totalSum - s1;
//                 minDiff = min(minDiff, abs(s1 - s2));
//             }
//         }
        
//         return minDiff;
//     }
// };

//  This is the most optimal method.
// 3. Tabulation approach (Bottom-up DP)
//  this is best because it builds the tablle in one go. no need of multiple calls.
class MinPartitionDifferenceTabulation {
public:
    // TC: O(n * sum), SC: O(n * sum) for dp array
    int minDifference(vector<int>& arr) {
        int n = arr.size();
        int totalSum = accumulate(arr.begin(), arr.end(), 0);
        int target = totalSum / 2;
        
        // dp[i][t]: can we get sum t using first (i+1) items?
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
        
        // Base Case: sum 0 can be made with empty subset
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        
        // Base Case: using only arr[0]
        if (arr[0] <= target) {
            dp[0][arr[0]] = true;
        }
        
        // Build table
        for (int i = 1; i < n; i++) {
            for (int t = 1; t <= target; t++) {
                // Include arr[i] if t >= arr[i]
                bool pick = false;
                if (t >= arr[i]) {
                    pick = dp[i-1][t - arr[i]];
                }
                // Exclude arr[i]
                bool notPick = dp[i-1][t];
                
                dp[i][t] = pick || notPick;
            }
        }
        
        // Find minimum difference by checking all possible subset sums
        int minDiff = INF;
        for (int s1 = 0; s1 <= target; s1++) {
            if (dp[n-1][s1]) {
                int s2 = totalSum - s1;
                minDiff = min(minDiff, abs(s1 - s2));
            }
        }
        
        return minDiff;
    }
};
