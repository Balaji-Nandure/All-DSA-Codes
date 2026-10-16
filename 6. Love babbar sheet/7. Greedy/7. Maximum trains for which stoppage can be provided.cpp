/**
 * ============================================================================
 * Problem: Maximum Trains for Which Stoppage Can Be Provided
 * Category: Greedy
 * 
 * Problem Statement:
 * Given N platforms and M trains. Each train has an arrival time, a departure 
 * time, and a designated platform number where it must stop.
 * 
 * Find the maximum number of trains for which stoppage can be provided such that
 * no two trains overlap on the same platform.
 * (A train can stop at a platform if its arrival time >= departure time of the 
 * previously stopped train on that same platform).
 * 
 * Example:
 * Input:
 *   Platforms N = 3, Trains M = 6
 *   Train 1: (1000, 1030, Platform 1)
 *   Train 2: (1010, 1020, Platform 1)
 *   Train 3: (1025, 1040, Platform 1)
 *   Train 4: (1000, 1020, Platform 2)
 *   Train 5: (1030, 1045, Platform 2)
 *   Train 6: (1200, 1230, Platform 3)
 * Output: 5
 * Explanation:
 *   Platform 1: Train 2 (1010-1020) and Train 3 (1025-1040) -> 2 trains.
 *   Platform 2: Train 4 (1000-1020) and Train 5 (1030-1045) -> 2 trains.
 *   Platform 3: Train 6 (1200-1230) -> 1 train.
 *   Total trains = 2 + 2 + 1 = 5.
 * 
 * Constraints:
 * 1 <= N <= 10^3 (number of platforms)
 * 1 <= M <= 10^4 (number of trains)
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single Room vs Fixed-Assignment Multi-Platform Scheduling:
 *    - In Problem 1 (N Meetings in One Room), all activities competed for 1 shared resource.
 *    - In Minimum Platforms (Problem 8), any train can use any platform.
 *    - HERE, each train has a STRICTLY PRE-ASSIGNED platform number.
 *    - Platforms are mutually independent: a conflict on Platform 1 has zero effect
 *      on Platform 2.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Partitioned Activity Selection O(M log M) Time, O(M) Space:
 *   - Step 1: Group all M trains by their assigned platform into `vector<Train> platformTrains[N + 1]`.
 *   - Step 2: For each platform independently:
 *       - Sort its trains by departure time in non-decreasing order.
 *       - Greedily schedule trains:
 *           `count++; lastDeparture = train[0].departure;`
 *           For remaining trains: if `arrival >= lastDeparture`, schedule it and update `lastDeparture`.
 *   - Step 3: Sum the accommodated trains across all N platforms.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Train {
    int arrival;
    int departure;
    int platform;
};

class Solution {
public:
    /**
     * Computes the maximum number of trains that can be accommodated across all platforms.
     * @param n Number of platforms.
     * @param m Number of trains.
     * @param trains Vector of Train structs.
     * @return Maximum trains stopped.
     */
    int maxStop(int n, int m, vector<Train>& trains) {
        // Group trains by their assigned platform
        vector<vector<Train>> platformGroups(n + 1);

        for (int i = 0; i < m; ++i) {
            platformGroups[trains[i].platform].push_back(trains[i]);
        }

        int totalAccommodated = 0;

        // Process each platform independently using Activity Selection
        for (int p = 1; p <= n; ++p) {
            if (platformGroups[p].empty()) continue;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Sorting trains per platform by departure time reduces the multi-platform
            // problem into N isolated, independent Activity Selection subproblems.
            sort(platformGroups[p].begin(), platformGroups[p].end(), [](const Train& a, const Train& b) {
                return a.departure < b.departure;
            });

            // Greedily pick the first train
            int count = 1;
            int lastDeparture = platformGroups[p][0].departure;

            for (size_t i = 1; i < platformGroups[p].size(); ++i) {
                if (platformGroups[p][i].arrival >= lastDeparture) {
                    count++;
                    lastDeparture = platformGroups[p][i].departure;
                }
            }

            totalAccommodated += count;
        }

        return totalAccommodated;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // N = 3, M = 6
    // Trains:
    // (1000, 1030, 1), (1010, 1020, 1), (1025, 1040, 1)
    // (1000, 1020, 2), (1030, 1045, 2)
    // (1200, 1230, 3)
    vector<Train> trains = {
        {1000, 1030, 1},
        {1010, 1020, 1},
        {1025, 1040, 1},
        {1000, 1020, 2},
        {1030, 1045, 2},
        {1200, 1230, 3}
    };
    int N = 3, M = trains.size();

    cout << "Max Trains Accommodated = " << solver.maxStop(N, M, trains) 
         << " (Expected: 5)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Partitioning trains into platform buckets: O(M).
 *   - Sorting each bucket: sum(M_i log M_i) <= O(M log M).
 *   - Greedy selection per bucket: O(M).
 *   - Total Time: O(M log M).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N + M) to store platform buckets.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Independent resource allocations decouple a multi-resource scheduling problem
 *    into independent single-resource greedy instances.
 */
