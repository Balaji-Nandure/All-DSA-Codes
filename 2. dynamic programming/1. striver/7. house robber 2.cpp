#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: House Robber II
 *
 * LeetCode 213: House Robber II
 * GeeksforGeeks: https://www.geeksforgeeks.org/maximum-sum-in-circular-array-such-that-no-two-elements-are-adjacent/
 *
 * Given an array of integers representing money in each house arranged in a circle,
find the maximum sum we can obtain by robbing houses such that:
- No two adjacent houses can be robbed
- First and last houses are adjacent (circular constraint)

Key Insight:
Since first and last are adjacent, we can't rob both.
So we solve two subproblems:
1. Rob houses from 0 to n-2 (excluding last house)
2. Rob houses from 1 to n-1 (excluding first house)
Take the maximum of these two.

Example:
arr = [2, 3, 2]
Case 1: [2, 3] -> max = 3
Case 2: [3, 2] -> max = 3
Answer = 3 (can't rob first and last together)
*/

// recursive approach
int houseRobber2Recursive(int idx, vector<int> &arr, bool includeFirst){
    int n = arr.size();
    
    if(includeFirst){
        // Case 1: Include first house, exclude last
        if(idx < 0) return 0;
        if(idx == 0) return arr[0];
        if(idx == n - 1) return houseRobber2Recursive(idx - 1, arr, includeFirst); // skip last
        
        int pick = arr[idx] + houseRobber2Recursive(idx - 2, arr, includeFirst);
        int notPick = houseRobber2Recursive(idx - 1, arr, includeFirst);
        return max(pick, notPick);
    } else {
        // Case 2: Exclude first house, can include last
        if(idx <= 0) return 0; // skip first house
        if(idx == 1) return arr[1];
        
        int pick = arr[idx] + houseRobber2Recursive(idx - 2, arr, includeFirst);
        int notPick = houseRobber2Recursive(idx - 1, arr, includeFirst);
        return max(pick, notPick);
    }
}

// memoization approach
int houseRobber2Memoization(int idx, vector<int> &arr, vector<int> &dp, bool includeFirst){
    int n = arr.size();
    
    if(includeFirst){
        if(idx < 0) return 0;
        if(idx == 0) return arr[0];
        if(idx == n - 1) return houseRobber2Memoization(idx - 1, arr, dp, includeFirst);
        if(dp[idx] != -1) return dp[idx];
        
        int pick = arr[idx] + houseRobber2Memoization(idx - 2, arr, dp, includeFirst);
        int notPick = houseRobber2Memoization(idx - 1, arr, dp, includeFirst);
        return dp[idx] = max(pick, notPick);
    } else {
        if(idx <= 0) return 0;
        if(idx == 1) return arr[1];
        if(dp[idx] != -1) return dp[idx];
        
        int pick = arr[idx] + houseRobber2Memoization(idx - 2, arr, dp, includeFirst);
        int notPick = houseRobber2Memoization(idx - 1, arr, dp, includeFirst);
        return dp[idx] = max(pick, notPick);
    }
}

// Helper function: Maximum sum of non-adjacent elements (from previous problem)
// This will be used to solve the linear subproblems
int maxSumNonAdjacentHelper(int start, int end, vector<int> &arr){
    if(start > end) return 0;
    if(start == end) return arr[start];
    
    int prev2 = arr[start];
    int prev1 = max(arr[start], arr[start + 1]);
    
    for(int i = start + 2; i <= end; i++){
        int pick = arr[i] + prev2;
        int notPick = prev1;
        int curr = max(pick, notPick);
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

// tabulation approach (cleaner implementation)
int houseRobber2Tabulation(int n, vector<int> &arr){
    if(n == 0) return 0;
    if(n == 1) return arr[0];
    if(n == 2) return max(arr[0], arr[1]);
    
    // Case 1: Include first, exclude last (houses 0 to n-2)
    int case1 = maxSumNonAdjacentHelper(0, n - 2, arr);
    
    // Case 2: Exclude first, include last (houses 1 to n-1)
    int case2 = maxSumNonAdjacentHelper(1, n - 1, arr);
    
    return max(case1, case2);
}

// space optimization approach (using helper function which is already optimized)
int houseRobber2SpaceOptimization(int n, vector<int> &arr){
    if(n == 0) return 0;
    if(n == 1) return arr[0];
    if(n == 2) return max(arr[0], arr[1]);
    
    // Case 1: Rob houses 0 to n-2
    int prev2_case1 = arr[0];
    int prev1_case1 = max(arr[0], arr[1]);
    
    for(int i = 2; i < n - 1; i++){ // stop at n-2
        int pick = arr[i] + prev2_case1;
        int notPick = prev1_case1;
        int curr = max(pick, notPick);
        prev2_case1 = prev1_case1;
        prev1_case1 = curr;
    }
    
    // Case 2: Rob houses 1 to n-1
    int prev2_case2 = arr[1];
    int prev1_case2 = max(arr[1], arr[2]);
    
    for(int i = 3; i < n; i++){ // start from index 3
        int pick = arr[i] + prev2_case2;
        int notPick = prev1_case2;
        int curr = max(pick, notPick);
        prev2_case2 = prev1_case2;
        prev1_case2 = curr;
    }
    
    return max(prev1_case1, prev1_case2);
}

signed main() {
    vector<int> arr = {2, 3, 2};
    int n = arr.size();
    
    // Recursive approach
    int recursive_case1 = houseRobber2Recursive(n - 2, arr, true); // exclude last
    int recursive_case2 = houseRobber2Recursive(n - 1, arr, false); // exclude first
    int recursive = max(recursive_case1, recursive_case2);
    
    // Memoization approach
    vector<int> dp1(n, -1);
    int memoization_case1 = houseRobber2Memoization(n - 2, arr, dp1, true);
    vector<int> dp2(n, -1);
    int memoization_case2 = houseRobber2Memoization(n - 1, arr, dp2, false);
    int memoization = max(memoization_case1, memoization_case2);
    
    int tabulation = houseRobber2Tabulation(n, arr);
    int spaceOptimization = houseRobber2SpaceOptimization(n, arr);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

