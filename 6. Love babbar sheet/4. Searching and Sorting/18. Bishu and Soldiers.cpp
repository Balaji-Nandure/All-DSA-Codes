// Problem: Bishu and Soldiers
// Link (HackerEarth): https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/bishu-and-soldiers-22/
// Difficulty: Easy
// Topic: Searching, Binary Search (upper_bound), Prefix Sum, Offline Queries

/*
Problem Statement:
There are N soldiers, where the i-th soldier has a power A[i].
Bishu goes to fight the soldiers. In each of Q rounds, Bishu has a power P.
In a round, Bishu can defeat all soldiers whose power is LESS THAN OR EQUAL TO his power P, 
and he absorbs their cumulative power.

For each query with Bishu's power P, output two space-separated integers:
  1. The total number of soldiers Bishu can defeat.
  2. The total sum of power of all those defeated soldiers.

Example 1:
Input:
N = 7
soldiers = [1, 2, 3, 4, 5, 6, 7]
Q = 3 queries:
P = 3 -> Output: 3 6 (Can beat 1, 2, 3; total power = 1 + 2 + 3 = 6)
P = 10 -> Output: 7 28 (Can beat all 7; total power = 28)
P = 2 -> Output: 2 3 (Can beat 1, 2; total power = 3)

Constraints:
- 1 <= N <= 10^4
- 1 <= A[i] <= 100
- 1 <= Q <= 10^4
- 1 <= P <= 100
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In standard binary search:
//   * We search for a single element in a single query.
// - In Bishu and Soldiers:
//   * We have MULTIPLE QUERIES (Q rounds).
//   * Answering each query naively by linear scan takes O(N), leading to O(Q * N) overall.
//   * By pre-sorting the soldiers and pre-computing a Prefix Sum array:
//       1. Number of defeated soldiers is found in O(log N) using `upper_bound`.
//       2. Cumulative sum of powers is retrieved in O(1) from the prefix sum table!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Sorting + Prefix Sums + Binary Search (Optimal & Chosen):
//   - Step 1: Sort the soldier powers array: O(N log N).
//   - Step 2: Build prefix sum array `pref` of size N + 1 where `pref[i] = sum(A[0 .. i-1])`.
//   - Step 3: For each query P:
//       * Use `upper_bound` to find the first soldier with power > P.
//       * The number of defeated soldiers is `count = upper_bound(A.begin(), A.end(), P) - A.begin()`.
//       * Total power absorbed is `sumPower = pref[count]`.
//   - Complexity: O((N + Q) log N) time, O(N) auxiliary space.
//   - Why this approach: Answering Q queries in logarithmic time per query is optimal.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> processQueries(vector<int>& soldiers, const vector<int>& queries) {
        int n = soldiers.size();
        sort(soldiers.begin(), soldiers.end());

        // Precompute prefix sums of soldier powers
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + soldiers[i];
        }

        vector<pair<int, int>> results;
        results.reserve(queries.size());

        for (int P : queries) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // upper_bound returns iterator to first soldier with power > P.
            // Subtracting begin() gives the exact count of soldiers with power <= P in O(log N)!
            int count = upper_bound(soldiers.begin(), soldiers.end(), P) - soldiers.begin();

            // O(1) prefix sum lookup for cumulative defeated power
            int totalPower = pref[count];

            results.push_back({count, totalPower});
        }

        return results;
    }
};

int main() {
    Solution sol;
    vector<int> soldiers = {1, 2, 3, 4, 5, 6, 7};
    vector<int> queries = {3, 10, 2};

    vector<pair<int, int>> answers = sol.processQueries(soldiers, queries);
    for (size_t i = 0; i < queries.size(); ++i) {
        cout << "Query Power " << queries[i] << " -> Soldiers Defeated: " 
             << answers[i].first << ", Total Power: " << answers[i].second << "\n";
    }

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * Sorting: O(N log N).
  * Prefix Sum computation: O(N).
  * Query processing: Q * O(log N).
  * Total Time: O((N + Q) log N), finishing 10^4 queries in < 5 milliseconds.
- Space Complexity: O(N) auxiliary space for the prefix sum array.

Key Takeaways:
- Combining Binary Search (`upper_bound`) with Prefix Sum arrays is the standard 
  formula for multi-query cumulative range problems.
*/
