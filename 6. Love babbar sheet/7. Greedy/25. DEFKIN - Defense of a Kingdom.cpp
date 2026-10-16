#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: DEFKIN - Defense of a Kingdom (SPOJ)
 * 
 * In a kingdom of size W x H (1-indexed coordinates: [1..W] x [1..H]), N defensive towers 
 * are placed at positions (X_i, Y_i).
 * Each tower guards its entire column (all points with x = X_i) and its entire row (all points with y = Y_i).
 * An unprotected rectangular penalty area consists of contiguous cells that are neither in 
 * guarded rows nor guarded columns.
 * Find the maximum area of such an unprotected rectangular region.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a 2D geometric grid partitioning problem.
 * - Key property: Row protection and Column protection are COMPLETELY ORTHOGONAL and INDEPENDENT.
 * - An unprotected rectangle's dimensions are (delta_X) * (delta_Y), where delta_X and delta_Y 
 *   depend solely on the gap between tower X-coordinates and Y-coordinates respectively.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Separation of Dimensions:
 *   Because column guards only depend on X and row guards only depend on Y:
 *   Max Area = (Max Unprotected X-interval) * (Max Unprotected Y-interval).
 * - For X dimension:
 *   Boundary towers exist at x = 0 and x = W + 1.
 *   Sort all X coordinates: [0, X_1, X_2, ..., X_N, W + 1].
 *   The unprotected width between consecutive towers x_i and x_{i-1} is: (x_i - x_{i-1} - 1).
 *   Max width = max_{i} (X[i] - X[i-1] - 1).
 * - For Y dimension:
 *   Boundary towers exist at y = 0 and y = H + 1.
 *   Sort all Y coordinates: [0, Y_1, Y_2, ..., Y_N, H + 1].
 *   Max height = max_{j} (Y[j] - Y[j-1] - 1).
 * - Result = max_width * max_height.
 */

class Solution {
public:
    long long maxUnprotectedArea(int W, int H, int N, vector<pair<int, int>>& towers) {
        if (N == 0) {
            return 1LL * W * H;
        }

        vector<int> X = {0};
        vector<int> Y = {0};

        for (int i = 0; i < N; i++) {
            X.push_back(towers[i].first);
            Y.push_back(towers[i].second);
        }

        // Add virtual boundary towers
        X.push_back(W + 1);
        Y.push_back(H + 1);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort X and Y coordinates independently to find maximum consecutive gaps
        sort(X.begin(), X.end());
        sort(Y.begin(), Y.end());

        int max_dx = 0;
        for (size_t i = 1; i < X.size(); i++) {
            // Number of empty unprotected columns strictly between X[i-1] and X[i]
            max_dx = max(max_dx, X[i] - X[i - 1] - 1);
        }

        int max_dy = 0;
        for (size_t i = 1; i < Y.size(); i++) {
            // Number of empty unprotected rows strictly between Y[i-1] and Y[i]
            max_dy = max(max_dy, Y[i] - Y[i - 1] - 1);
        }

        // *** CRUCIAL LINE: 2D rectangle area is the product of independent 1D maximal gaps ***
        return 1LL * max_dx * max_dy;
    }
};

int main() {
    Solution sol;
    // Kingdom size 15 x 8 with 3 towers
    int W = 15, H = 8, N = 3;
    vector<pair<int, int>> towers = {
        {3, 8},
        {11, 2},
        {8, 6}
    };

    cout << "Max Unprotected Area: " << sol.maxUnprotectedArea(W, H, N, towers) << "\n";
    // X sorted: 0, 3, 8, 11, 16
    // Gaps X: (3-0-1)=2, (8-3-1)=4, (11-8-1)=2, (16-11-1)=4 -> max_dx = 4
    // Y sorted: 0, 2, 6, 8, 9
    // Gaps Y: (2-0-1)=1, (6-2-1)=3, (8-6-1)=1, (9-8-1)=0 -> max_dy = 3
    // Area = 4 * 3 = 12

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) to sort the N tower coordinates.
 * - Space Complexity: O(N) to store X and Y coordinate vectors.
 */
