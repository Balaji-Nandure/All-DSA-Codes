#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;
// recursive approach
int fibonacci(int n){
    if(n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// memoization approach
int fibonacciMemoization(int n, vector<int> &dp){
    if(n <= 1) return n;
    if(dp[n] != -1) return dp[n];
    return dp[n] = fibonacciMemoization(n-1, dp) + fibonacciMemoization(n-2, dp);
}

// tabulation approach
int fibonacciTabulation(int n){
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// space optimization approach
int fibonacciSpaceOptimization(int n){
    int prev2 = 0;
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
    int recursive = fibonacci(n);

    vector<int> dp1(n+1, -1);
    int memoization = fibonacciMemoization(n, dp1);

    int tabulation = fibonacciTabulation(n);
    int spaceOptimization = fibonacciSpaceOptimization(n);

    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
}