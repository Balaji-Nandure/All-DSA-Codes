#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum Length of Pair Chain (LeetCode 646)
 * 
 * You are given an array of n pairs pairs[i] = [left_i, right_i] with left_i < right_i.
 * A pair p2 = [c, d] follows a pair p1 = [a, b] if and only if b < c.
 * A chain of pairs can be formed in this fashion.
 * Return the length longest chain which can be formed.
 * You do not need to use up all the given pairs. You can select pairs in any order.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "16. LIS", the order of elements was strictly FIXED and could not be permuted.
 * - Here, pairs can be picked in ANY order.
 * - This problem bridges Dynamic Programming and Greedy Algorithms:
 *   - DP view: Sort pairs by first element, then run LIS in O(N^2) or O(N log N).
 *   - Greedy view: Sort pairs by second element (earliest finish time) in O(N log N) time and O(1) space.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Dynamic Programming (LIS on Interval Graph):
 *   1. Sort pairs ascending by their FIRST coordinate: pair[0].first <= pair[1].first <= ...
 *   2. Let dp[i] be the length of the longest chain ending with pair i.
 *      dp[i] = 1 + max_{0 <= j < i, pairs[j][1] < pairs[i][0]} dp[j].
 *      Result = max(dp[i]).
 *      Time: O(N^2), Space: O(N).
 * 
 * - Method 2: Optimal Greedy (Interval Scheduling):
 *   Because any two pairs that don't overlap are compatible, choosing the pair that 
 *   FINISHES EARLIEST (smallest right_i) leaves maximum room for future pairs.
 *   Sort by second coordinate (right_i).
 *   Time: O(N log N), Space: O(1).
 */

class Solution {
public:
    // Method 1: Dynamic Programming Approach (O(N^2) Time, O(N) Space)
    int findLongestChainDP(vector<vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;

        // Sort by first element
        sort(pairs.begin(), pairs.end());

        vector<int> dp(n, 1);
        int max_chain = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Chain extension condition: previous pair's end < current pair's start
                if (pairs[j][1] < pairs[i][0]) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            max_chain = max(max_chain, dp[i]);
        }

        return max_chain;
    }

    // Method 2: Optimal Greedy (O(N log N) Time, O(1) Space)
    int findLongestChain(vector<vector<int>>& pairs) {
        if (pairs.empty()) return 0;

        // Sort primarily by end coordinate ascending
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int chain_len = 1;
        int curr_end = pairs[0][1];

        for (size_t i = 1; i < pairs.size(); i++) {
            // *** CRUCIAL LINE: Pick pair with earliest end time that starts after current end ***
            if (pairs[i][0] > curr_end) {
                chain_len++;
                curr_end = pairs[i][1];
            }
        }

        return chain_len;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> pairs1 = {{1, 2}, {2, 3}, {3, 4}};
    cout << "Max Chain Length (Greedy): " << sol.findLongestChain(pairs1) << "\n";   // Expected: 2 ([1,2] -> [3,4])
    cout << "Max Chain Length (DP):     " << sol.findLongestChainDP(pairs1) << "\n"; // Expected: 2

    vector<vector<int>> pairs2 = {{1, 2}, {7, 8}, {4, 5}};
    cout << "Max Chain Length 2: " << sol.findLongestChain(pairs2) << "\n"; // Expected: 3 ([1,2] -> [4,5] -> [7,8])

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Dynamic Programming Method: Time Complexity O(N^2), Space Complexity O(N).
 * - Optimal Greedy Method: Time Complexity O(N log N), Space Complexity O(1).
 */
