#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Minimum number of jumps to reach end (Jump Game II)
 * 
 * Given an array arr of non-negative integers where arr[i] represents the maximum 
 * jump length from index i, find the minimum number of jumps to reach index N - 1.
 * If the last index cannot be reached, return -1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike standard shortest path on general graphs (Dijkstra), the transitions here 
 *   are continuous intervals [i + 1 ... i + arr[i]].
 * - While 1D DP takes O(N^2), the contiguous nature of intervals allows a BFS-like 
 *   sliding window to solve the problem in strictly O(N) time and O(1) space!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Optimal O(N) Greedy Window (Implicit BFS):
 *   Treat the jumps as BFS levels:
 *   - Level 0: [0, 0] (0 jumps).
 *   - Level 1: [1, arr[0]] (1 jump).
 *   - Level 2: [arr[0] + 1, max_reach achievable from Level 1], and so on.
 *   
 *   Algorithm:
 *   1. Track `max_reach`: the furthest index that can be reached from ANY visited position.
 *   2. Track `curr_end`: the boundary of the CURRENT jump.
 *   3. Traverse index i from 0 to N - 2:
 *      - max_reach = max(max_reach, i + arr[i])
 *      - If i reaches curr_end:
 *        We are forced to take another jump to advance!
 *        jumps++
 *        curr_end = max_reach
 *        If curr_end <= i: We are trapped and cannot advance any further -> return -1.
 *   4. If loop completes, return jumps.
 */

class Solution {
public:
    // Optimal O(N) Time and O(1) Space Greedy BFS
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;
        if (arr[0] == 0) return -1; // Cannot make initial jump

        int max_reach = arr[0];
        int curr_end = arr[0];
        int jumps = 1;

        for (int i = 1; i < n; i++) {
            // Destination reached!
            if (i == n - 1) {
                return jumps;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Greedily expand the furthest boundary reachable from any point in current window
            max_reach = max(max_reach, i + arr[i]);

            // When we exhaust the reach of the current jump
            if (i == curr_end) {
                jumps++;

                // *** CRUCIAL LINE: Check if unable to advance past current index (dead end) ***
                if (max_reach <= i) {
                    return -1;
                }

                curr_end = max_reach;
            }
        }

        return jumps;
    }

    // Classic 1D DP in O(N^2) Time
    int minJumpsDP(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (j + arr[j] >= i && dp[j] != INT_MAX) {
                    dp[i] = min(dp[i], dp[j] + 1);
                    break; // Since we iterate j from 0 up, first j that reaches i has smallest dp[j]
                }
            }
        }

        return (dp[n - 1] == INT_MAX) ? -1 : dp[n - 1];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    cout << "Min Jumps 1 (O(N)):   " << sol.minJumps(arr1) << "\n";   // Expected: 3 (0 -> 1 -> 3 -> 10)
    cout << "Min Jumps 1 (O(N^2)): " << sol.minJumpsDP(arr1) << "\n";

    vector<int> arr2 = {1, 1, 1, 1, 1};
    cout << "Min Jumps 2: " << sol.minJumps(arr2) << "\n"; // Expected: 4

    vector<int> arr3 = {0, 1, 2};
    cout << "Min Jumps 3: " << sol.minJumps(arr3) << "\n"; // Expected: -1

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Optimal Method: Time Complexity O(N) single pass. Space Complexity O(1).
 * - DP Method: Time Complexity O(N^2), Space Complexity O(N).
 */
