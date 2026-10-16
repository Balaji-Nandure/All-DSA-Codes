#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Friends Pairing Problem
 * 
 * Given N friends, each one can remain single or can be paired up with some other friend.
 * Each friend can be paired only once.
 * Find the total number of ways in which friends can remain single or be paired up.
 * Return the result modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike Subset Sum or Knapsack which track cumulative weights/sums,
 *   this is a combinatoric counting recurrence on partitions of sets into size 1 (singles) and size 2 (pairs).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Linear Dynamic Programming with O(1) Space:
 *   Consider the N-th friend:
 *   - Option 1 (Single):
 *     The N-th person decides to remain single.
 *     The remaining (N - 1) friends can be configured in f(N - 1) ways.
 *   
 *   - Option 2 (Paired):
 *     The N-th person pairs up with one of the remaining (N - 1) people.
 *     There are (N - 1) possible partners to choose from.
 *     Once this pair is formed, the remaining (N - 2) friends can be configured in f(N - 2) ways.
 *     Total ways for this option: (N - 1) * f(N - 2).
 *   
 *   Recurrence Relation:
 *     f(n) = f(n - 1) + (n - 1) * f(n - 2)  (modulo 10^9 + 7)
 *   
 *   Base Cases:
 *     f(1) = 1 (1 person can only remain single).
 *     f(2) = 2 (either both remain single {1}, {2}, or pair together {1, 2}).
 *   
 *   Space Optimization:
 *     Because f(n) depends only on the previous two values, we can store just two rolling 
 *     variables `prev2` and `prev1`, reducing space complexity to strictly O(1)!
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    int countFriendsPairings(int n) {
        if (n <= 2) return n;

        long long prev2 = 1; // f(1)
        long long prev1 = 2; // f(2)
        long long curr = 0;

        for (int i = 3; i <= n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // f(i) = f(i - 1) + (i - 1) * f(i - 2) % MOD
            curr = (prev1 + (1LL * (i - 1) * prev2) % MOD) % MOD;

            // Rolling state update for O(1) space
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;
    cout << "Pairing ways for N = 1: " << sol.countFriendsPairings(1) << "\n"; // Expected: 1
    cout << "Pairing ways for N = 2: " << sol.countFriendsPairings(2) << "\n"; // Expected: 2
    cout << "Pairing ways for N = 3: " << sol.countFriendsPairings(3) << "\n"; // Expected: 4 ({1},{2},{3}; {1,2},{3}; {1,3},{2}; {2,3},{1})
    cout << "Pairing ways for N = 4: " << sol.countFriendsPairings(4) << "\n"; // Expected: 10

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single loop from 3 up to N.
 * - Space Complexity: O(1) auxiliary space (tracks only rolling `prev1` and `prev2`).
 */
