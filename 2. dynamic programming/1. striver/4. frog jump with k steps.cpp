#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Frog Jump with K Steps
A frog is standing on the 1st stair of an N stairs long staircase. The frog wants to reach the Nth stair.
- HEIGHT[i] represents the height of the (i+1)th stair (0-indexed array)
- When the frog jumps from the ith stair to the jth stair, the energy lost is |HEIGHT[i] - HEIGHT[j]|
- From any ith stair, the frog can jump to any stair from (i+1)th to (i+k)th stair (at most k steps)
- Find the minimum total energy the frog needs to use to travel from the 1st stair to the Nth stair

Example:
HEIGHT = [10, 20, 30, 10, 20], k = 3
From stair 0, can jump to stairs 1, 2, or 3
From stair 1, can jump to stairs 2, 3, or 4
*/

// recursive approach
int frogJumpK(int idx, vector<int> &height, int k){
    if(idx == 0) return 0; // base case: at first stair, no energy needed
    
    int minEnergy = INF;
    for(int j = 1; j <= k; j++){
        if(idx - j >= 0){
            int energy = frogJumpK(idx - j, height, k) + abs(height[idx] - height[idx - j]);
            minEnergy = min(minEnergy, energy);
        }
    }
    
    return minEnergy;
}

// memoization approach
int frogJumpKMemoization(int idx, vector<int> &height, int k, vector<int> &dp){
    if(idx == 0) return 0;
    if(dp[idx] != -1) return dp[idx];
    
    int minEnergy = INF;
    for(int j = 1; j <= k; j++){
        if(idx - j >= 0){
            int energy = frogJumpKMemoization(idx - j, height, k, dp) + abs(height[idx] - height[idx - j]);
            minEnergy = min(minEnergy, energy);
        }
    }
    
    return dp[idx] = minEnergy;
}

// tabulation approach
int frogJumpKTabulation(int n, vector<int> &height, int k){
    vector<int> dp(n, INF);
    dp[0] = 0;
    
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

// space optimization approach using a circular buffer and modulo for O(k) space
// This approach uses modulo arithmetic to maintain only k previous dp values
int frogJumpKSpaceOptimization(int n, vector<int> &height, int k){
    if(n == 1) return 0;
    
    vector<int> dp(k, INF); // rolling array for sliding window, size k (dp[i % k])
    dp[0] = 0; // dp[0] = 0

    for(int i = 1; i < n; i++){
        int minEnergy = INF;
        for(int j = 1; j <= k; j++){
            if(i - j >= 0){
                int prevIdx = (i - j) % k;
                int energy = dp[prevIdx] + abs(height[i] - height[i - j]);
                minEnergy = min(minEnergy, energy);
            }
        }
        dp[i % k] = minEnergy;
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
