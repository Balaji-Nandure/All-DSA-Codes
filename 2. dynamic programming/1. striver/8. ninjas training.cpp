#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Ninja's Training
A ninja has N days of training. Each day, he can perform one of three activities:
- Activity 0: Training type 0
- Activity 1: Training type 1
- Activity 2: Training type 2

Each activity gives different merit points. The ninja cannot perform the same activity
on two consecutive days. Find the maximum merit points the ninja can earn.

Given:
- points[N][3]: points[i][j] = merit points for day i, activity j

Example:
points = [[1, 2, 5],
          [3, 1, 1],
          [3, 3, 3]]
Day 0: Activity 2 -> 5 points
Day 1: Activity 0 -> 3 points (can't do activity 2 again)
Day 2: Activity 1 or 2 -> 3 points
Maximum = 5 + 3 + 3 = 11
*/

// Recursive approach
int f(int d, int l, vector<vector<int>> &p) {
    if(d < 0) return 0;
    int res = 0;
    for(int a = 0; a < 3; a++) {
        if(a != l) {
            int tmp = p[d][a] + f(d-1, a, p);
            res = max(res, tmp);
        }
    }
    return res;
}

// Memoization approach
int fm(int d, int l, vector<vector<int>> &p, vector<vector<int>> &dp) {
    if(d < 0) return 0;
    if(dp[d][l] != -1) return dp[d][l];
    int res = 0;
    for(int a = 0; a < 3; a++) {
        if(a != l) {
            int tmp = p[d][a] + fm(d-1, a, p, dp);
            res = max(res, tmp);
        }
    }
    return dp[d][l] = res;
}

int ft(vector<vector<int>>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(3));

    // base case
    dp[0][0] = arr[0][0];
    dp[0][1] = arr[0][1];
    dp[0][2] = arr[0][2];

    for (int i = 1; i < n; i++) {
        dp[i][0] = arr[i][0] + max(dp[i-1][1], dp[i-1][2]); // can't repeat 0
        dp[i][1] = arr[i][1] + max(dp[i-1][0], dp[i-1][2]); // can't repeat 1
        dp[i][2] = arr[i][2] + max(dp[i-1][0], dp[i-1][1]); // can't repeat 2
    }

    return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}

int fs(vector<vector<int>>& arr) {
    int n = arr.size();
    // prev[i] = max points till previous day ending with activity i
    vector<int> prev(3);

    // base case (day 0)
    prev[0] = arr[0][0];
    prev[1] = arr[0][1];
    prev[2] = arr[0][2];

    for (int i = 1; i < n; i++) {
        vector<int> curr(3);

        curr[0] = arr[i][0] + max(prev[1], prev[2]); // do activity 0 today
        curr[1] = arr[i][1] + max(prev[0], prev[2]); // do activity 1 today
        curr[2] = arr[i][2] + max(prev[0], prev[1]); // do activity 2 today

        prev = curr; // move to next day
    }

    return max({prev[0], prev[1], prev[2]});
}


signed main() {
    vector<vector<int>> p = {
        {1,2,5},
        {3,1,1},
        {3,3,3}
    };
    int n = p.size();

    int res1 = f(n-1, 3, p); // recursive
    vector<vector<int>> dpm(n, vector<int>(4, -1));
    int res2 = fm(n-1, 3, p, dpm); // memo
    int res3 = ft(n, p); // tab
    int res4 = fs(n, p); // space opt

    cout << "Recursive: " << res1 << endl;
    cout << "Memoization: " << res2 << endl;
    cout << "Tabulation: " << res3 << endl;
    cout << "Space Optimization: " << res4 << endl;

    return 0;
}
