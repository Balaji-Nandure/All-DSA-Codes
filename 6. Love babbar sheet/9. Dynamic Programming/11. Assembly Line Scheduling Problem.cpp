#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Assembly Line Scheduling Problem (CLRS Classic)
 * 
 * A manufacturing factory has two parallel assembly lines (Line 1 and Line 2),
 * each with N stations.
 * - Station times: a[0][j] (Line 1) and a[1][j] (Line 2).
 * - Transfer times between lines: t[0][j] (Line 1 to 2) and t[1][j] (Line 2 to 1).
 * - Entry times: e[0] and e[1].
 * - Exit times: x[0] and x[1].
 * Find the minimum time required to assemble a product through all N stations.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike Gold Mine where choices were 3-way in an open 2D plane,
 *   here we have exactly TWO coupled parallel states with switching penalties.
 * - This is the canonical dual-state machine Dynamic Programming problem.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dual-State Dynamic Programming with O(1) Space:
 *   Let T1 be the minimum time to exit station j on Line 1.
 *   Let T2 be the minimum time to exit station j on Line 2.
 *   
 *   Base Case (Station 0):
 *     T1 = e[0] + a[0][0]
 *     T2 = e[1] + a[1][0]
 *   
 *   Transitions for station j (1 <= j < N):
 *     To arrive at station j on Line 1, we could have come:
 *     - From station (j - 1) on Line 1: cost = T1 + a[0][j]
 *     - From station (j - 1) on Line 2 with transfer t[1][j]: cost = T2 + t[1][j] + a[0][j]
 *     new_T1 = a[0][j] + min(T1, T2 + t[1][j])
 *     
 *     To arrive at station j on Line 2, we could have come:
 *     - From station (j - 1) on Line 2: cost = T2 + a[1][j]
 *     - From station (j - 1) on Line 1 with transfer t[0][j]: cost = T1 + t[0][j] + a[1][j]
 *     new_T2 = a[1][j] + min(T2, T1 + t[0][j])
 *   
 *   Final Result:
 *     min(T1 + x[0], T2 + x[1])
 */

class Solution {
public:
    int carAssembly(vector<vector<int>>& a, vector<vector<int>>& t, vector<int>& e, vector<int>& x) {
        int n = a[0].size();

        // Base cases: Entry into station 0 of each line
        int T1 = e[0] + a[0][0];
        int T2 = e[1] + a[1][0];

        // Process remaining stations 1 to n - 1
        for (int j = 1; j < n; j++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Minimum time to reach station j on Line 1 (stay on Line 1 vs transfer from Line 2)
            int next_T1 = a[0][j] + min(T1, T2 + t[1][j]);

            // Minimum time to reach station j on Line 2 (stay on Line 2 vs transfer from Line 1)
            int next_T2 = a[1][j] + min(T2, T1 + t[0][j]);

            T1 = next_T1;
            T2 = next_T2;
        }

        // Add final exit costs and return minimum
        // *** CRUCIAL LINE: Choose the optimal line to exit from ***
        return min(T1 + x[0], T2 + x[1]);
    }
};

int main() {
    Solution sol;
    // Station processing times on Line 1 and Line 2
    vector<vector<int>> a = {
        {4, 5, 3, 2},
        {2, 10, 1, 4}
    };
    // Transfer times from station j to switch lines
    vector<vector<int>> t = {
        {0, 7, 4, 5},
        {0, 9, 2, 8}
    };
    vector<int> e = {10, 12}; // Entry times
    vector<int> x = {18, 7};  // Exit times

    cout << "Minimum assembly time: " << sol.carAssembly(a, t, e, x) << "\n";
    // Expected: 35

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear pass through all stations.
 * - Space Complexity: O(1) auxiliary space maintaining only current line costs T1 and T2.
 */
