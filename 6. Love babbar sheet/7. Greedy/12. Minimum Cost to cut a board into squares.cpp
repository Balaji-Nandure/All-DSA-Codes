/**
 * ============================================================================
 * Problem: Minimum Cost to Cut a Board into Squares (Chocolate Cutting / CHOCOLA)
 * Category: Greedy
 * 
 * Problem Statement:
 * A board of dimensions M x N is given. We need to break the board into M * N 
 * individual 1 x 1 squares.
 * 
 * There are (M - 1) horizontal cuts and (N - 1) vertical cuts.
 * Each cut has an associated cost:
 *   - `X[0...M-2]` represents costs of horizontal cuts.
 *   - `Y[0...N-2]` represents costs of vertical cuts.
 * 
 * Whenever a cut is performed, the cost incurred is:
 *   `cut_cost * (number of segments/pieces through which the cut passes)`.
 * 
 * Every horizontal cut increases the count of horizontal pieces by 1 and cuts
 * through all current vertical pieces.
 * Every vertical cut increases the count of vertical pieces by 1 and cuts
 * through all current horizontal pieces.
 * 
 * Find the MINIMUM total cost required to cut the board completely into unit squares.
 * 
 * Example 1:
 * Input:
 *   M = 6, N = 4
 *   X[] (Horizontal cuts) = {2, 1, 3, 1, 4}
 *   Y[] (Vertical cuts)   = {4, 1, 2}
 * Output: 42
 * 
 * Constraints:
 * 2 <= M, N <= 10^5
 * 1 <= X[i], Y[i] <= 10^4
 * Must run in O(M log M + N log N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Multiplicative Piece Expansion (Multiplier Penalty):
 *    - In previous greedy problems, the cost of an action was static and constant.
 *    - Here, the effective cost of a cut SCALES MULTIPLICATIVELY with the number
 *      of pieces already created in the orthogonal direction!
 * 2. Delay Minimization (Perform Costly Cuts First):
 *    - An expensive cut of weight 100 performed early costs 100 * 1 = 100.
 *    - If delayed until after 5 orthogonal cuts, it costs 100 * 6 = 600!
 *    - Therefore, the greedy choice is strictly to execute the globally most expensive
 *      remaining cut (whether horizontal or vertical) first.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy by Decreasing Cut Cost O(M log M + N log N) Time, O(1) Space:
 *   - Step 1: Sort both horizontal cuts `X` and vertical cuts `Y` in descending order.
 *   - Step 2: Initialize multipliers:
 *       `horizontalPieces = 1;`
 *       `verticalPieces = 1;`
 *   - Step 3: Two pointers `i = 0` (for X), `j = 0` (for Y):
 *       - While both cuts remain:
 *           - If `X[i] >= Y[j]`:
 *               Horizontal cut is more expensive! Perform it now:
 *               `totalCost += X[i] * verticalPieces;`
 *               `horizontalPieces++;`
 *               `i++;`
 *           - Else:
 *               Vertical cut is more expensive! Perform it now:
 *               `totalCost += Y[j] * horizontalPieces;`
 *               `verticalPieces++;`
 *               `j++;`
 *   - Step 4: Add remaining cuts multiplied by the final piece counts.
 *   - Return `totalCost`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates minimum cost to cut an M x N board into unit squares.
     * @param m Number of rows.
     * @param n Number of columns.
     * @param X Array of horizontal cut costs (size m - 1).
     * @param Y Array of vertical cut costs (size n - 1).
     * @return Minimum total cost.
     */
    long long minimumCostOfBreaking(int m, int n, vector<int>& X, vector<int>& Y) {
        // Step 1: Sort cut costs in descending order
        sort(X.begin(), X.end(), greater<int>());
        sort(Y.begin(), Y.end(), greater<int>());

        int i = 0, j = 0;
        long long horizontalPieces = 1;
        long long verticalPieces = 1;
        long long totalCost = 0;

        // Step 2: Greedily pick the largest available cut
        while (i < m - 1 && j < n - 1) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Perform the most expensive cut first so that its cost is multiplied by
            // the smallest possible number of opposing pieces.
            if (X[i] >= Y[j]) {
                totalCost += (long long)X[i] * verticalPieces;
                horizontalPieces++;
                i++;
            } else {
                totalCost += (long long)Y[j] * horizontalPieces;
                verticalPieces++;
                j++;
            }
        }

        // Add remaining horizontal cuts, if any
        while (i < m - 1) {
            totalCost += (long long)X[i] * verticalPieces;
            i++;
        }

        // Add remaining vertical cuts, if any
        while (j < n - 1) {
            totalCost += (long long)Y[j] * horizontalPieces;
            j++;
        }

        return totalCost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case: M = 6, N = 4
    // X = {2, 1, 3, 1, 4}
    // Y = {4, 1, 2}
    // Expected: 42
    int m = 6, n = 4;
    vector<int> X = {2, 1, 3, 1, 4};
    vector<int> Y = {4, 1, 2};

    cout << "Minimum Cost to Cut Board = " 
         << solver.minimumCostOfBreaking(m, n, X, Y) 
         << " (Expected: 42)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting X of size (M - 1): O(M log M).
 *   - Sorting Y of size (N - 1): O(N log N).
 *   - Two-pointer greedy merging: O(M + N).
 *   - Total Time: O(M log M + N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) in-place without auxiliary vectors.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. When an action's future cost grows monotonically with time, execute the
 *    heaviest actions first.
 * 2. Horizontal cuts scale with `verticalPieces`, and vertical cuts scale with `horizontalPieces`.
 */
