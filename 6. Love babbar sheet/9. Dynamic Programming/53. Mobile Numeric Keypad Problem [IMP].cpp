#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/**
 * Problem: Mobile Numeric Keypad Problem
 * 
 * Given the standard mobile phone keypad:
 *   1  2  3
 *   4  5  6
 *   7  8  9
 *   *  0  #
 * You can start from any digit. From any digit, you can either:
 * - Press the SAME button again.
 * - Move to any directly ADJACENT button (Up, Down, Left, Right).
 * You CANNOT press '*' or '#'.
 * Given an integer N, count the total number of valid digit sequences of length N.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a graph random-walk counting problem with self-loops on a fixed 10-vertex topology.
 * - Rather than free movement, each digit d has a strictly predefined set of accessible neighbors.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Fixed-Graph Markov Dynamic Programming in O(N) Time and O(1) Space:
 *   Build the adjacency list for each digit (including the digit itself for repeated presses):
 *     0: {0, 8}
 *     1: {1, 2, 4}
 *     2: {2, 1, 3, 5}
 *     3: {3, 2, 6}
 *     4: {4, 1, 5, 7}
 *     5: {5, 2, 4, 6, 8}
 *     6: {6, 3, 5, 9}
 *     7: {7, 4, 8}
 *     8: {8, 5, 7, 9, 0}
 *     9: {9, 6, 8}
 *   
 *   Let dp[d] be the number of valid sequences of current length ending with digit d.
 *   
 *   Base Case (Length 1):
 *     dp[d] = 1 for all d in [0 ... 9]. Total = 10.
 *   
 *   Transitions for length step 2 to N:
 *     For each digit d:
 *       new_dp[d] = sum_{prev in adj[d]} dp[prev]
 *   
 *   Result:
 *     sum_{d=0}^9 dp[d]
 */

class Solution {
public:
    long long getCount(int N) {
        if (N <= 0) return 0;
        if (N == 1) return 10;

        // Adjacency graph for digits 0-9
        vector<vector<int>> adj = {
            {0, 8},             // 0
            {1, 2, 4},          // 1
            {2, 1, 3, 5},       // 2
            {3, 2, 6},          // 3
            {4, 1, 5, 7},       // 4
            {5, 2, 4, 6, 8},    // 5
            {6, 3, 5, 9},       // 6
            {7, 4, 8},          // 7
            {8, 5, 7, 9, 0},    // 8
            {9, 6, 8}           // 9
        };

        // dp[d] stores number of sequences of current length ending in digit d
        vector<long long> prev(10, 1);
        vector<long long> curr(10, 0);

        for (int step = 2; step <= N; step++) {
            for (int d = 0; d < 10; d++) {
                curr[d] = 0;
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Sum paths from all valid preceding adjacent keys and self-loop
                for (int neighbor : adj[d]) {
                    curr[d] += prev[neighbor];
                }
            }
            prev = curr;
        }

        // Total sequences of length N across all 10 ending digits
        long long total = 0;
        for (int d = 0; d < 10; d++) {
            total += prev[d];
        }

        return total;
    }
};

int main() {
    Solution sol;
    cout << "Keypad sequences (N=1): " << sol.getCount(1) << "\n"; // Expected: 10
    cout << "Keypad sequences (N=2): " << sol.getCount(2) << "\n"; // Expected: 36
    cout << "Keypad sequences (N=3): " << sol.getCount(3) << "\n"; // Expected: 138
    cout << "Keypad sequences (N=4): " << sol.getCount(4) << "\n"; // Expected: 532

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * 10) = O(N). Outer loop runs N times, inner loop visits fixed 10 keys and their neighbors.
 * - Space Complexity: O(1) auxiliary space (using only two 10-element vectors).
 */
