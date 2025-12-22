#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: Frog Jump with K Steps
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/minimal-cost/1
 *
 * Frog can jump at most k steps from any stair. Find minimum energy to reach Nth stair.
 * Energy = |HEIGHT[i] - HEIGHT[j]|
 *
 * Example: HEIGHT = [10, 20, 30, 10, 20], k = 3
 * From stair 0, can jump to stairs 1, 2, or 3
 *
 * Time: O(n*k) with DP
 * Space: O(n) with DP, O(k) space optimized
 */

// Recursive approach
int frogJumpK(int idx, vector<int> &height, int k){
    // Base case: at first stair, no energy needed
    if(idx == 0) return 0;
    
    // Try all possible k steps and find minimum energy
    int minEnergy = INF;
    for(int j = 1; j <= k; j++){
        if(idx - j >= 0){
            // Energy to reach idx from (idx-j)
            int energy = frogJumpK(idx - j, height, k) + abs(height[idx] - height[idx - j]);
            minEnergy = min(minEnergy, energy);
        }
    }
    
    return minEnergy;
}

// Memoization approach (Top-down DP)
int frogJumpKMemoization(int idx, vector<int> &height, int k, vector<int> &dp){
    // Base case
    if(idx == 0) return 0;
    // Return cached result
    if(dp[idx] != -1) return dp[idx];
    
    // Try all k possible steps and find minimum
    int minEnergy = INF;
    for(int j = 1; j <= k; j++){
        if(idx - j >= 0){
            int energy = frogJumpKMemoization(idx - j, height, k, dp) + abs(height[idx] - height[idx - j]);
            minEnergy = min(minEnergy, energy);
        }
    }
    
    return dp[idx] = minEnergy;
}

// Tabulation approach (Bottom-up DP)
int frogJumpKTabulation(int n, vector<int> &height, int k){
    vector<int> dp(n, INF);
    dp[0] = 0; // Base case
    
    // For each stair, try all k possible previous positions
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= k; j++){
            if(i - j >= 0){
                int energy = dp[i - j] + abs(height[i] - height[i - j]);
                dp[i] = min(dp[i], energy);
            }
        }
    }
    
    return dp[n - 1];
}

// Space optimization: Use circular buffer of size k (only need last k values)
int frogJumpKSpaceOptimization(int n, vector<int> &height, int k){
    if(n == 1) return 0;
    
    vector<int> dp(k, INF); // Rolling array: dp[i % k] stores dp[i]
    dp[0] = 0; // dp[0] = 0

    for(int i = 1; i < n; i++){
        int minEnergy = INF;
        // Check all k possible previous positions
        for(int j = 1; j <= k; j++){
            if(i - j >= 0){
                int prevIdx = (i - j) % k; // Get previous value from circular buffer
                int energy = dp[prevIdx] + abs(height[i] - height[i - j]);
                minEnergy = min(minEnergy, energy);
            }
        }
        dp[i % k] = minEnergy; // Store in circular buffer
    }

    return dp[(n - 1) % k];
}

signed main() {
    vector<int> height = {10, 20, 30, 10, 20};
    int n = height.size();
    int k = 3;
    
    int recursive = frogJumpK(n - 1, height, k);
    
    vector<int> dp1(n, -1);
    int memoization = frogJumpKMemoization(n - 1, height, k, dp1);
    
    int tabulation = frogJumpKTabulation(n, height, k);
    int spaceOptimization = frogJumpKSpaceOptimization(n, height, k);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}
