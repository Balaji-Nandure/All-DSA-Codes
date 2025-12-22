#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Frog Jump
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/geek-jump/1
 *
 * A frog wants to reach the Nth stair. From ith stair, can jump to (i+1)th or (i+2)th.
 * Energy lost = |HEIGHT[i] - HEIGHT[j]|. Find minimum total energy.
 *
 * Example: HEIGHT = [10, 20, 30, 10]
 * Path: 0->1->3, Energy: |10-20| + |20-10| = 20
 *
 * Time: O(n) with DP, O(2^n) recursive
 * Space: O(n) with DP, O(1) space optimized
 */

// Recursive approach
int frogJump(int idx, vector<int> &height){
    // Base case: at first stair, no energy needed
    if(idx == 0) return 0;
    
    // Option 1: Jump 1 step from previous stair
    int oneStep = frogJump(idx - 1, height) + abs(height[idx] - height[idx - 1]);
    
    // Option 2: Jump 2 steps (only if idx >= 2)
    int twoStep = 1e9;
    if(idx > 1) twoStep = frogJump(idx - 2, height) + abs(height[idx] - height[idx - 2]);
    
    // Return minimum energy
    return min(oneStep, twoStep);
}

// Memoization approach (Top-down DP)
int frogJumpMemoization(int idx, vector<int> &height, vector<int> &dp){
    // Base case
    if(idx == 0) return 0;
    // Return cached result if available
    if(dp[idx] != -1) return dp[idx];
    
    // Compute minimum energy
    int oneStep = frogJumpMemoization(idx - 1, height, dp) + abs(height[idx] - height[idx - 1]);
    int twoStep = 1e9;
    if(idx > 1) twoStep = frogJumpMemoization(idx - 2, height, dp) + abs(height[idx] - height[idx - 2]);
    
    // Store and return result
    return dp[idx] = min(oneStep, twoStep);
}

// Tabulation approach (Bottom-up DP)
int frogJumpTabulation(int n, vector<int> &height){
    vector<int> dp(n, 0);
    dp[0] = 0; // Base case: no energy at first stair
    if(n > 1) dp[1] = abs(height[1] - height[0]); // Only one way to reach second stair
    
    // Fill dp array from left to right
    for(int i = 2; i < n; i++){
        int oneStep = dp[i - 1] + abs(height[i] - height[i - 1]);
        int twoStep = dp[i - 2] + abs(height[i] - height[i - 2]);
        dp[i] = min(oneStep, twoStep);
    }
    
    return dp[n - 1];
}

// Space optimization (only need last 2 values)
int frogJumpSpaceOptimization(int n, vector<int> &height){
    if(n == 1) return 0;
    
    int prev2 = 0; // dp[0]
    int prev1 = abs(height[1] - height[0]); // dp[1]
    
    for(int i = 2; i < n; i++){
        int oneStep = prev1 + abs(height[i] - height[i - 1]);
        int twoStep = prev2 + abs(height[i] - height[i - 2]);
        int curr = min(oneStep, twoStep);
        // Update for next iteration
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

