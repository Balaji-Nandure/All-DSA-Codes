/**
 * ============================================================================
 * Problem: Check if it is Possible to Survive on Island
 * Category: Greedy / Mathematics
 * 
 * Problem Statement:
 * You are a person stranded on an island. You need to survive for S days.
 * The town has only one shop selling food with the following constraints:
 *   - S = Number of days you need to survive.
 *   - N = Maximum units of food you can purchase per day.
 *   - M = Units of food required per day to stay alive.
 *   - The shop is OPEN every day EXCEPT Sunday (days 7, 14, 21, 28... are Sundays).
 * 
 * Find the MINIMUM number of days you need to buy food from the shop to survive
 * all S days. If survival is impossible under these constraints, return -1.
 * 
 * Example 1:
 * Input: S = 10, N = 16, M = 2
 * Output: 2
 * Explanation:
 *   Total food required = 10 * 2 = 20 units.
 *   Buying on Day 1 (16 units) and Day 2 (4 units) gives 20 units in 2 days.
 * 
 * Example 2:
 * Input: S = 10, N = 9, M = 8
 * Output: -1
 * Explanation:
 *   Total food needed = 10 * 8 = 80 units.
 *   Total open days = 10 - (10 / 7) = 9 days.
 *   Max food purchasable = 9 * 9 = 81 units?
 *   Wait! Before Sunday (Day 7), you have only 6 buying days:
 *   Max food before Day 7 = 6 * 9 = 54 units.
 *   Food needed through Day 7 = 7 * 8 = 56 units.
 *   Since 54 < 56, you will starve on Day 7! Impossible -> -1.
 * 
 * Constraints:
 * 1 <= S, N, M <= 10^5
 * Must run in O(1) time and O(1) space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Periodic Supply Blackout (Sundays):
 *    - In standard supply chain problems, resources can be gathered every day.
 *    - Here, every 7th day is a non-purchasing day.
 *    - You must front-load purchases during open days to stockpile food for Sundays.
 * 2. Feasibility Bounds:
 *    - Condition 1: Daily demand cannot exceed daily shop capacity: M <= N.
 *    - Condition 2: Total purchasable food in (S - S/7) days must cover total demand S * M.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * O(1) Mathematical Formulation:
 *   - Total food required: `totalFood = S * M`.
 *   - Number of Sundays in S days: `sundays = S / 7`.
 *   - Total buying days available: `buyingDays = S - sundays`.
 *   - Maximum food obtainable: `maxFoodPossible = buyingDays * N`.
 *   - If `maxFoodPossible < totalFood`: Survival is impossible -> return -1.
 *   - Otherwise, survival is guaranteed!
 *   - Minimum transactions needed:
 *       `minDays = ceil(totalFood / N) = (totalFood + N - 1) / N`.
 *   - Return `minDays`.
 * ============================================================================
 */

#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Determines the minimum buying days required to survive on the island.
     * @param S Number of days to survive.
     * @param N Maximum units of food purchasable per day.
     * @param M Units of food required per day.
     * @return Minimum days to buy food, or -1 if impossible.
     */
    int minimumDays(int S, int N, int M) {
        // Condition 1: If daily requirement exceeds maximum daily purchase capacity
        if (M > N) {
            return -1;
        }

        // Total food needed for S days
        int totalFoodNeeded = S * M;

        // Number of Sundays where shop is closed
        int sundays = S / 7;
        int buyingDays = S - sundays;

        // Maximum food that can possibly be purchased on open days
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Feasibility check: Can all available open days supply the total food needed?
        if (buyingDays * N < totalFoodNeeded) {
            return -1;
        }

        // Minimum days needed = ceil(totalFoodNeeded / N)
        int minDays = (totalFoodNeeded + N - 1) / N;

        return minDays;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: S = 10, N = 16, M = 2 -> Expected: 2
    cout << "Test 1 (S=10, N=16, M=2): " << solver.minimumDays(10, 16, 2) 
         << " (Expected: 2)\n";

    // Test Case 2: S = 10, N = 9, M = 8 -> Expected: -1 (starves on Day 7)
    cout << "Test 2 (S=10, N=9, M=8):  " << solver.minimumDays(10, 9, 8) 
         << " (Expected: -1)\n";

    // Test Case 3: S = 6, N = 10, M = 2 -> Expected: 2
    cout << "Test 3 (S=6, N=10, M=2):   " << solver.minimumDays(6, 10, 2) 
         << " (Expected: 2)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Closed-form integer arithmetic: O(1) constant time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Ceiling division for integers: `ceil(A / B) = (A + B - 1) / B`.
 * 2. Available purchasing days in S days with Sunday closures = `S - S/7`.
 */
