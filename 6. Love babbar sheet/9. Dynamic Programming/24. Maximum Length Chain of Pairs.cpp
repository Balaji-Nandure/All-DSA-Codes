#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum Length Chain of Pairs
 * 
 * Given N pairs of numbers (a, b) where a < b.
 * A pair (c, d) can follow (a, b) if b < c.
 * Find the longest chain of pairs which can be formed from any subset of pairs.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "16. LIS", the order of the original array was FIXED and could not be altered.
 * - Here, pairs can be chosen in ANY ORDER.
 * - This reveals that Maximum Length Chain of Pairs is isomorphic to the 
 *   ACTIVITY SELECTION PROBLEM (Greedy Category 7, Problem 1)!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Optimal Greedy by Earliest Finish Time (O(N log N) Time, O(1) Space):
 *   1. Treat each pair (a, b) as an interval [start, finish].
 *   2. To maximize the number of non-overlapping intervals, we should always choose the interval 
 *      that FINISHES EARLIEST!
 *      Finishing early frees up the number line at the lowest possible coordinate, leaving 
 *      maximum remaining room for future pairs.
 *   3. Sort pairs strictly by second element (b) in ascending order.
 *   4. Greedily pick the next pair whenever its start (a) > end of previously chosen pair.
 * 
 * - Alternative DP Approach:
 *   Sort by first element, then run LIS: dp[i] = 1 + max_{j < i, pairs[j].second < pairs[i].first} dp[j].
 *   Greedy is strictly superior: O(N log N) vs O(N^2).
 */

struct val {
    int first;
    int second;
};

class Solution {
public:
    static bool comparePairs(const val& p1, const val& p2) {
        return p1.second < p2.second; // Earliest finish time
    }

    // Greedy Solution: O(N log N) Time, O(1) Space
    int maxChainLen(val p[], int n) {
        if (n == 0) return 0;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort pairs by their second element (finish coordinate) ascending
        sort(p, p + n, comparePairs);

        int count = 1;
        int last_end = p[0].second;

        for (int i = 1; i < n; i++) {
            // *** CRUCIAL LINE: Check if current pair starts strictly after last chosen pair ended ***
            if (p[i].first > last_end) {
                count++;
                last_end = p[i].second;
            }
        }

        return count;
    }
};

int main() {
    Solution sol;
    val pairs[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n = sizeof(pairs) / sizeof(pairs[0]);

    cout << "Max Chain Length: " << sol.maxChainLen(pairs, n) << "\n";
    // Pairs sorted by second:
    // {5, 24} (pick, end=24)
    // {15, 28} (15 <= 24, skip)
    // {27, 40} (27 > 24, pick, end=40)
    // {39, 60} (39 <= 40, skip)
    // {50, 90} (50 > 40, pick, end=90)
    // Chain: {5, 24} -> {27, 40} -> {50, 90} (length 3). Expected: 3.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting the pairs. Linear O(N) scan.
 * - Space Complexity: O(1) auxiliary space beyond the input array.
 */
