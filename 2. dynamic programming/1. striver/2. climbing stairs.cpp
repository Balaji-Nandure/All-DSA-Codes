#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

int climbingStairs(int n){
    if(n <= 1) return 1;
    return climbingStairs(n-1) + climbingStairs(n-2);
}

int climbingStairsMemoization(int n, vector<int> &dp){
    if(n <= 1) return 1;
    if(dp[n] != -1) return dp[n];
    return dp[n] = climbingStairsMemoization(n-1, dp) + climbingStairsMemoization(n-2, dp);
}

int climbingStairsTabulation(int n){
    vector<int> dp(n+1, -1);
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2; i <= n; i++) dp[i] = dp[i-1] + dp[i-2];
    return dp[n];
}

int climbingStairsSpaceOptimization(int n){
    int prev2 = 1;
    int prev1 = 1;
    for(int i = 2; i <= n; i++){
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

signed main() {
    int n = 10;
    int recursive = climbingStairs(n);

    vector<int> dp1(n+1, -1);
    int memoization = climbingStairsMemoization(n, dp1);

    int tabulation = climbingStairsTabulation(n);

    int spaceOptimization = climbingStairsSpaceOptimization(n);
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
}