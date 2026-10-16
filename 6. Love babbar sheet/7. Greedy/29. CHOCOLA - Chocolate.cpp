#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: CHOCOLA - Chocolate (SPOJ)
 * 
 * A chocolate of size M x N is composed of M x N square pieces.
 * We want to break it completely into 1 x 1 individual squares.
 * Cutting costs:
 * - Horizontal cut costs: X[0 ... M-2]
 * - Vertical cut costs:   Y[0 ... N-2]
 * When a cut is made across all current pieces in that direction, its cost is 
 * (base_cost * number_of_pieces_to_cut_through).
 * Find the minimal total cost of breaking the chocolate into 1 x 1 squares.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is the multi-test SPOJ version of "12. Minimum Cost to cut a board into squares".
 * - Cutting in one direction increases the multiplier of all subsequent cuts in the orthogonal direction.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy by Largest Base Cost First:
 *   Let H_count be the number of horizontal chocolate segments (initially 1).
 *   Let V_count be the number of vertical chocolate segments (initially 1).
 *   If we make a horizontal cut with cost C_h, it must cut through all current vertical pieces:
 *     Cost added = C_h * V_count, and H_count increases by 1.
 *   If we make a vertical cut with cost C_v, it must cut through all current horizontal pieces:
 *     Cost added = C_v * H_count, and V_count increases by 1.
 *   
 *   To minimize total cost, the largest cut costs must be multiplied by the SMALLEST segment counts!
 *   Therefore, we must always choose the largest available cost (whether horizontal or vertical) first.
 */

class Solution {
public:
    long long minChocolateCutCost(int M, int N, vector<int>& X, vector<int>& Y) {
        // Sort both horizontal and vertical cuts descending
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        sort(X.begin(), X.end(), greater<int>());
        sort(Y.begin(), Y.end(), greater<int>());

        int i = 0, j = 0;
        long long horizontal_pieces = 1;
        long long vertical_pieces = 1;
        long long total_cost = 0;

        int m_cuts = M - 1; // number of horizontal cuts
        int n_cuts = N - 1; // number of vertical cuts

        while (i < m_cuts && j < n_cuts) {
            // Pick the cut with the larger cost
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            if (X[i] >= Y[j]) {
                total_cost += 1LL * X[i] * vertical_pieces;
                horizontal_pieces++;
                i++;
            } else {
                total_cost += 1LL * Y[j] * horizontal_pieces;
                vertical_pieces++;
                j++;
            }
        }

        // Add remaining horizontal cuts
        while (i < m_cuts) {
            total_cost += 1LL * X[i] * vertical_pieces;
            i++;
        }

        // Add remaining vertical cuts
        while (j < n_cuts) {
            total_cost += 1LL * Y[j] * horizontal_pieces;
            j++;
        }

        return total_cost;
    }
};

int main() {
    Solution sol;
    // Chocolate size 6 x 4 -> 5 horizontal cuts, 3 vertical cuts
    int M = 6, N = 4;
    vector<int> X = {2, 1, 3, 1, 4}; // horizontal costs
    vector<int> Y = {4, 1, 2};       // vertical costs

    cout << "Min Cut Cost: " << sol.minChocolateCutCost(M, N, X, Y) << "\n";
    // Expected: 42

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M log M + N log N) for sorting both cut cost arrays. The two-pointer merge is O(M + N).
 * - Space Complexity: O(1) auxiliary space beyond the input vectors.
 */
