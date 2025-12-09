#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Frog Jump
A frog is standing on the 1st stair of an N stairs long staircase. The frog wants to reach the Nth stair.
- HEIGHT[i] represents the height of the (i+1)th stair (0-indexed array)
- When the frog jumps from the ith stair to the jth stair, the energy lost is |HEIGHT[i] - HEIGHT[j]|
- From any ith stair, the frog can jump either to the (i+1)th stair or to the (i+2)th stair
- Find the minimum total energy the frog needs to use to travel from the 1st stair to the Nth stair

Example:
HEIGHT = [10, 20, 30, 10]
Path: 1st -> 2nd -> 4th
Energy: |10-20| + |20-10| = 10 + 10 = 20
*/

// recursive approach
int frogJump(int idx, vector<int> &height){
    if(idx == 0) return 0; // base case: at first stair, no energy needed
    // if(idx == 1) return abs(height[1] - height[0]); // can only come from stair 0
    
    int oneStep = frogJump(idx - 1, height) + abs(height[idx] - height[idx - 1]);
    int twoStep = 1e9;
    if(idx > 1) twoStep = frogJump(idx - 2, height) + abs(height[idx] - height[idx - 2]);
    
    return min(oneStep, twoStep);
}

// memoization approach
int frogJumpMemoization(int idx, vector<int> &height, vector<int> &dp){
    if(idx == 0) return 0;
    // if(idx == 1) return abs(height[1] - height[0]);
    if(dp[idx] != -1) return dp[idx];
    
    int oneStep = frogJumpMemoization(idx - 1, height, dp) + abs(height[idx] - height[idx - 1]);
    int twoStep = 1e9;
    if(idx > 1) twoStep = frogJumpMemoization(idx - 2, height, dp) + abs(height[idx] - height[idx - 2]);
    
    return dp[idx] = min(oneStep, twoStep);
}

// tabulation approach
int frogJumpTabulation(int n, vector<int> &height){
    vector<int> dp(n, 0);
    dp[0] = 0;
    if(n > 1) dp[1] = abs(height[1] - height[0]);
    
    for(int i = 2; i < n; i++){
        int oneStep = dp[i - 1] + abs(height[i] - height[i - 1]);
        int twoStep = dp[i - 2] + abs(height[i] - height[i - 2]);
        dp[i] = min(oneStep, twoStep);
    }
    
    return dp[n - 1];
}

// space optimization approach
int frogJumpSpaceOptimization(int n, vector<int> &height){
    if(n == 1) return 0;
    
    int prev2 = 0; // dp[0]
    int prev1 = abs(height[1] - height[0]); // dp[1]
    
    for(int i = 2; i < n; i++){
        int oneStep = prev1 + abs(height[i] - height[i - 1]);
        int twoStep = prev2 + abs(height[i] - height[i - 2]);
        int curr = min(oneStep, twoStep);
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

signed main() {
    vector<int> height = {10, 20, 30, 10};
    int n = height.size();
    
    int recursive = frogJump(n - 1, height);
    
    vector<int> dp1(n, -1);
    int memoization = frogJumpMemoization(n - 1, height, dp1);
    
    int tabulation = frogJumpTabulation(n, height);
    int spaceOptimization = frogJumpSpaceOptimization(n, height);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

