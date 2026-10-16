#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Picking Up Chicks (Google Code Jam / SPOJ GCJ101BB)
 * 
 * N chicks are running toward a barn at position B.
 * Chick i starts at position X[i] and runs with constant speed V[i].
 * Time limit is T seconds.
 * A chick reaches the barn if X[i] + V[i] * T >= B.
 * Chicks cannot pass each other unless swapped. One swap allows a chick to overtake 
 * the chick immediately in front of it.
 * Find the minimum number of swaps required so that at least K chicks reach the barn within time T.
 * If impossible, return -1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an inversion/obstacle counting problem with physical constraints (position order).
 * - Slower chicks block faster chicks behind them unless an explicit swap is paid.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy from Right to Left (Closest to Barn to Furthest):
 *   1. Chicks closer to the barn have fewer obstacles ahead of them.
 *      To minimize total swaps, we should greedily prioritize the capable chicks closest to the barn.
 *   2. Iterate from index N - 1 down to 0:
 *      - Check if chick i can reach the barn: X[i] + V[i] * T >= B.
 *      - If YES (capable):
 *        To reach the barn, this chick must overtake ALL currently counted incapable chicks 
 *        that stand between it and the barn!
 *        swaps += incapable_count;
 *        capable_count++;
 *        If capable_count reaches K, we are done!
 *      - If NO (incapable):
 *        This chick will act as an obstacle for any capable chicks coming from further behind.
 *        incapable_count++;
 *   3. If we check all chicks and capable_count < K, it is physically impossible.
 */

class Solution {
public:
    int minSwaps(int N, int K, int B, int T, vector<int>& X, vector<int>& V) {
        if (K == 0) return 0;

        int capable_count = 0;
        int incapable_count = 0;
        int total_swaps = 0;

        // Traverse from right to left (closest to barn to furthest)
        for (int i = N - 1; i >= 0; i--) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if chick i can cover the distance to barn B within time T
            long long max_distance = (long long)X[i] + (long long)V[i] * T;

            if (max_distance >= B) {
                // Chick i is capable: it must jump over all slower obstacles in front of it
                total_swaps += incapable_count;
                capable_count++;

                // *** CRUCIAL LINE: Stop as soon as K chicks have successfully made it ***
                if (capable_count == K) {
                    return total_swaps;
                }
            } else {
                // Chick i cannot make it, becoming an obstacle for all chicks behind it
                incapable_count++;
            }
        }

        // If fewer than K chicks could reach the barn even with swaps
        return -1;
    }
};

int main() {
    Solution sol;
    // N = 5, K = 3, B = 10, T = 5
    // X = 0 2 5 6 7
    // V = 1 1 1 1 4
    int N = 5, K = 3, B = 10, T = 5;
    vector<int> X = {0, 2, 5, 6, 7};
    vector<int> V = {1, 1, 1, 1, 4};

    cout << "Min swaps: " << sol.minSwaps(N, K, B, T, X, V) << "\n";
    // Distances reachable at T=5:
    // Chick 4: 7 + 4*5 = 27 >= 10 (Capable, 0 obstacles) -> swaps = 0, count = 1
    // Chick 3: 6 + 1*5 = 11 >= 10 (Capable, 0 obstacles) -> swaps = 0, count = 2
    // Chick 2: 5 + 1*5 = 10 >= 10 (Capable, 0 obstacles) -> swaps = 0, count = 3 == K! Total swaps = 0.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single right-to-left scan.
 * - Space Complexity: O(1) auxiliary space.
 */
