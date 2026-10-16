// Problem: Aggressive Cows (Allocate Minimum Distance Maximization)
// Link (GFG): https://www.geeksforgeeks.org/problems/aggressive-cows/1
// Difficulty: Hard
// Topic: Searching, Binary Search on Answer, Greedy Feasibility Check

/*
Problem Statement:
You are given an array of integers `stalls` which represents the positions of stalls 
along a straight line, and an integer `k` representing the number of aggressive cows.
Assign stalls to `k` cows such that the MINIMUM distance between any two of them is as LARGE as possible.
Return the largest possible minimum distance.

Example 1:
Input: stalls = [1, 2, 4, 8, 9], k = 3
Output: 3
Explanation: Place 3 cows at stalls 1, 4, and 8 (or 9).
Distances: 4 - 1 = 3, 8 - 4 = 4.
The minimum distance is min(3, 4) = 3. No assignment can achieve minimum distance > 3.

Example 2:
Input: stalls = [10, 1, 2, 7, 5], k = 3
Output: 4
Explanation: Sorted stalls: [1, 2, 5, 7, 10]. Place cows at 1, 5, 10 -> min dist = 4.

Constraints:
- 2 <= stalls.size() <= 10^5
- 2 <= k <= stalls.size()
- 0 <= stalls[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In standard Binary Search:
//   * We checked whether an element exists in a static list.
// - In Aggressive Cows (Minimax / Maximize the Minimum):
//   * We perform "Binary Search on Answer Space".
//   * Monotonicity Property:
//     If it is POSSIBLE to place k cows with minimum separation `dist`, 
//     then it is guaranteed to be possible with any separation `< dist`!
//     If it is IMPOSSIBLE with `dist`, it is impossible with any separation `> dist`!
//   * This monotonic predicate `canPlace(dist)` allows binary searching the distance directly.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Distance Range + Greedy Placement (Optimal & Chosen):
//   - Step 1: Sort stalls in ascending order: O(N log N).
//   - Step 2: Establish search range for minimum distance `dist`:
//       `low = 1`, `high = stalls[n - 1] - stalls[0]`.
//   - Step 3: Feasibility Check `canPlace(dist)`:
//       * Greedily place the 1st cow at `stalls[0]`.
//       * For each subsequent stall `stalls[i]`:
//           If `stalls[i] - lastPlacedStall >= dist`:
//             Place next cow here! `count++`, `lastPlacedStall = stalls[i]`.
//             If `count == k`: Return `true`!
//       * Return `false` if fewer than `k` cows could be placed.
//   - Step 4: Binary Search:
//       * If `canPlace(mid)`: `ans = mid; low = mid + 1;` (greedily test larger separations).
//       * Else: `high = mid - 1;` (separation too ambitious).
//   - Complexity: O(N log N + N log(max_dist)) time, O(1) space.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function: Greedily verifies whether k cows can be placed with at least `dist` separation
    bool canPlaceCows(const vector<int>& stalls, int k, int dist) {
        int cowsPlaced = 1; // Always place the first cow at the first available stall
        int lastPos = stalls[0];

        for (size_t i = 1; i < stalls.size(); ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Greedy placement: As soon as a stall is at least `dist` away from the previous cow,
            // place a cow immediately! Placing cows as early as possible leaves maximum room for remaining cows.
            if (stalls[i] - lastPos >= dist) {
                cowsPlaced++;
                lastPos = stalls[i];

                if (cowsPlaced >= k) {
                    return true; // Successfully placed all k cows
                }
            }
        }

        return false; // Could not place all k cows
    }

public:
    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());

        int n = stalls.size();
        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If mid distance is feasible, record it and try to search for an even larger distance in right half
            if (canPlaceCows(stalls, k, mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1; // Distance too large, contract search to left half
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> stalls1 = {1, 2, 4, 8, 9};
    int k1 = 3;
    cout << "Max minimum distance (stalls1): " << sol.aggressiveCows(stalls1, k1) << "\n";

    vector<int> stalls2 = {10, 1, 2, 7, 5};
    int k2 = 3;
    cout << "Max minimum distance (stalls2): " << sol.aggressiveCows(stalls2, k2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N log N + N * log(max_distance)).
  * Sorting stalls: O(N log N).
  * Binary search iterations: log2(10^9) ≈ 30.
  * In each iteration, `canPlaceCows` traverses the array in O(N).
  * Total time: 30 * 10^5 ≈ 3 * 10^6 ops (executes in ~10 ms).
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Aggressive Cows is the benchmark problem for "Maximize the Minimum" Binary Search on Answer.
*/
