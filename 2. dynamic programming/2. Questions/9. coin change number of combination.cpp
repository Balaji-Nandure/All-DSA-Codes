/*
Coin Change – Number of Combinations

Input:
n          -> number of coins
arr[]      -> coin denominations
amt        -> target amount

Goal:
Count total number of combinations to form 'amt'
(order does NOT matter, unlimited coins)

DP Meaning:
dp[x] = number of ways to form amount x
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Dummy test case
    // Example: 3 coins (1, 2, 5), target amount 5
    vector<int> arr = {1, 2, 5};
    int n = arr.size();
    int amt = 5;

    // dp[x] = number of combinations to make amount x
    vector<long long> dp(amt + 1, 0);

    // Base case:
    // There is exactly 1 way to make amount 0 (choose nothing)
    dp[0] = 1;

    /*
    Outer loop on coins ensures:
    - Each coin is used in a fixed order
    - Prevents permutation counting
    */
    for (int i = 0; i < n; i++) {
        /*
        Inner loop goes forward (unbounded knapsack)
        allowing multiple usage of the same coin
        */
        for (int j = arr[i]; j <= amt; j++) {
            dp[j] += dp[j - arr[i]];
        }
    }

    cout << dp[amt] << '\n'; // outputs 4 for the example
    return 0;
}
