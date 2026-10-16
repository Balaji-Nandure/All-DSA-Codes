#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/**
 * Problem: DIEHARD - DIE HARD (SPOJ)
 * 
 * Given initial Health H and Armor A.
 * You can move between 3 environments:
 *   1. Air:   H += 3,  A += 2
 *   2. Water: H -= 5,  A -= 10
 *   3. Fire:  H -= 20, A += 5
 * 
 * Constraints:
 * - Cannot stay in the same environment in two consecutive turns.
 * - Game ends immediately if H <= 0 or A <= 0.
 * Find the maximum time you can survive.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an alternating state transition problem with strict positive invariants (H > 0, A > 0).
 * - One state (Air) is strictly restorative (+3 H, +2 A), while the other two are consumptive.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Alternating Observation:
 *   Because Air strictly INCREASES both Health and Armor with zero penalties,
 *   we should ALWAYS visit Air whenever legally permitted (every alternate move)!
 *   - Turn 1: Always Air (H += 3, A += 2).
 *   - Turn 2: Forced to choose between Water and Fire.
 *   - Turn 3: Air again.
 *   - Turn 4: Forced choice between Water and Fire.
 * 
 * - Decision between Water and Fire:
 *   Water consumes 5 H and 10 A.
 *   Fire consumes 20 H and gives +5 A.
 *   Notice: Fire consumes 4x more Health (20 vs 5).
 *   Therefore, if Armor > 10, Water is far superior because preserving Health allows 
 *   many more future Air restorations (+3 per visit).
 *   Only when Armor is low (<= 10) and Health is plentiful (> 20) do we choose Fire to replenish Armor.
 * 
 * - Both Greedy Simulation and Memoized DP are provided.
 */

class Solution {
    int memo[1050][1050][4]; // H, A, last_state (1: Air, 2: Water, 3: Fire)

    int solveDP(int h, int a, int last) {
        if (h <= 0 || a <= 0) return -1;
        if (memo[h][a][last] != -1) return memo[h][a][last];

        int ans = 0;
        // Option 1: Air
        if (last != 1) {
            ans = max(ans, 1 + solveDP(h + 3, a + 2, 1));
        }
        // Option 2: Water
        if (last != 2 && h > 5 && a > 10) {
            ans = max(ans, 1 + solveDP(h - 5, a - 10, 2));
        }
        // Option 3: Fire
        if (last != 3 && h > 20) {
            ans = max(ans, 1 + solveDP(h - 20, a + 5, 3));
        }

        return memo[h][a][last] = ans;
    }

public:
    int maxSurvivalTimeGreedy(int H, int A) {
        int time = 0;
        bool in_air = false;

        // Turn 1 always starts in Air for free stats
        while (true) {
            if (!in_air) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Air strictly enhances state; always choose Air when not in Air
                H += 3;
                A += 2;
                in_air = true;
                time++;
            } else {
                // Must leave Air: pick Water if armor allows (saves health), else Fire
                if (H > 5 && A > 10) {
                    // *** CRUCIAL LINE: Water is preferred over Fire because Health loss is 5 vs 20 ***
                    H -= 5;
                    A -= 10;
                    in_air = false;
                    time++;
                } else if (H > 20) {
                    // Fire sacrifices health to rescue depleted armor
                    H -= 20;
                    A += 5;
                    in_air = false;
                    time++;
                } else {
                    // Cannot make any legal move without dying
                    break;
                }
            }
        }

        return time;
    }

    int maxSurvivalTime(int H, int A) {
        memset(memo, -1, sizeof(memo));
        // Start by entering Air at t = 1
        return 1 + solveDP(H + 3, A + 2, 1);
    }
};

int main() {
    Solution sol;
    int H1 = 4, A1 = 20;
    cout << "Greedy Survival 1: " << sol.maxSurvivalTimeGreedy(H1, A1) << "\n"; // Expected: 1
    cout << "DP Survival 1:     " << sol.maxSurvivalTime(H1, A1) << "\n";

    int H2 = 20, A2 = 8;
    cout << "Greedy Survival 2: " << sol.maxSurvivalTimeGreedy(H2, A2) << "\n"; // Expected: 5
    cout << "DP Survival 2:     " << sol.maxSurvivalTime(H2, A2) << "\n";

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(H + A) for Greedy simulation; O(H * A) for DP.
 * - Space Complexity: O(1) for Greedy simulation.
 */
