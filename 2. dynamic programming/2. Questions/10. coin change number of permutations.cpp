/*
Coin Change - Number of Permutations

Input:
n        -> number of coins
arr[]    -> coin denominations
amt      -> target amount

Goal:
Count number of PERMUTATIONS to form 'amt'
(order MATTERS, unlimited coins)

DP Meaning:
dp[x] = number of permutations to make amount x
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Sample test case: coins = {1, 2, 5}, amount = 5
    vector<int> arr = {1, 2, 5};
    int n = arr.size();
    int amt = 5;

    // dp[x] = number of permutations to make amount x
    vector<long long> dp(amt + 1, 0);

    // Base case:
    // One way to make amount 0 (empty sequence)
    dp[0] = 1;

    /*
    Amount loop outside ensures order matters
    Each state dp[i] builds permutations ending at i
    */
    for (int i = 1; i <= amt; i++) {
        for (int coin : arr) {
            if (i - coin >= 0) {
                dp[i] += dp[i - coin];
            }
        }
    }

    cout << dp[amt] << '\n';
    return 0;
}
