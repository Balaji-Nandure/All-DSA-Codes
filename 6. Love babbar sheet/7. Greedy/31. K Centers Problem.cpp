#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: K Centers Problem (Greedy 2-Approximation Algorithm)
 * 
 * Given N cities and an N x N distance matrix `dist` satisfying metric properties 
 * (dist[i][j] >= 0, dist[i][i] = 0, dist[i][j] = dist[j][i], and triangle inequality).
 * Select K cities to serve as centers such that the maximum distance from any city 
 * to its nearest selected center is minimized.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an NP-Hard facility location optimization problem.
 * - Unlike problems where greedy yields exact global optima, here Greedy provides 
 *   a provably optimal 2-Approximation factor (Gonzalez's Algorithm).
 * - No polynomial algorithm can achieve an approximation ratio < 2 unless P = NP.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Gonzalez's Furthest-Point Greedy Algorithm:
 *   1. Arbitrarily pick an initial center (e.g., city 0).
 *   2. Maintain an array `min_dist[i]` storing the distance from each city `i` to its nearest chosen center.
 *   3. At each subsequent iteration (up to K centers):
 *      - Find the city `u` that has the MAXIMUM distance to its nearest center:
 *        u = argmax_{i} min_dist[i].
 *      - Select `u` as the new center.
 *      - Update `min_dist[v] = min(min_dist[v], dist[u][v])` for all cities v.
 *   4. After selecting K centers, the maximum distance of any city to its nearest center 
 *      is max_{i} min_dist[i].
 * 
 * - Proof of 2-Approximation:
 *   Suppose the optimal radius is R*. If we pick K+1 centers using furthest-first,
 *   by Pigeonhole Principle, two of these K+1 points must belong to the same cluster in the optimal clustering.
 *   By triangle inequality, the distance between them is at most 2*R*.
 *   Because every newly selected center was the furthest available point, the distance to any point 
 *   cannot exceed 2*R*.
 */

class Solution {
public:
    pair<int, vector<int>> selectKCenters(int N, int K, vector<vector<int>>& dist) {
        vector<int> centers;
        vector<int> min_dist(N);

        // Step 1: Pick city 0 as the first center
        centers.push_back(0);
        for (int i = 0; i < N; i++) {
            min_dist[i] = dist[0][i];
        }

        // Step 2: Greedily pick the remaining K - 1 centers
        for (int step = 1; step < K; step++) {
            int furthest_city = 0;
            int max_distance = -1;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Find the city that is currently furthest away from any chosen center
            for (int i = 0; i < N; i++) {
                if (min_dist[i] > max_distance) {
                    max_distance = min_dist[i];
                    furthest_city = i;
                }
            }

            // Add the furthest city as a new center
            centers.push_back(furthest_city);

            // *** CRUCIAL LINE: Update distances of all cities to include the new center ***
            for (int i = 0; i < N; i++) {
                min_dist[i] = min(min_dist[i], dist[furthest_city][i]);
            }
        }

        // Step 3: Find maximum distance from any city to its nearest center
        int max_radius = 0;
        for (int i = 0; i < N; i++) {
            max_radius = max(max_radius, min_dist[i]);
        }

        return {max_radius, centers};
    }
};

int main() {
    Solution sol;
    int N = 4, K = 2;
    vector<vector<int>> dist = {
        {0, 10, 7, 6},
        {10, 0, 8, 5},
        {7, 8, 0, 12},
        {6, 5, 12, 0}
    };

    auto result = sol.selectKCenters(N, K, dist);
    cout << "Max distance to nearest center: " << result.first << "\n";
    cout << "Selected Centers: ";
    for (int c : result.second) {
        cout << c << " ";
    }
    cout << "\n";

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(K * N). In each of the K steps, we scan all N vertices to find the max and update distances.
 * - Space Complexity: O(N) to store `min_dist` and `centers`.
 */
