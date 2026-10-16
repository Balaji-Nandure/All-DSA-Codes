/**
 * ============================================================================
 * Problem: Fractional Knapsack Problem
 * Category: Greedy
 * 
 * Problem Statement:
 * Given weights and values of N items, we need to put these items in a knapsack
 * of capacity W to achieve the maximum total value.
 * Unlike 0/1 Knapsack, in Fractional Knapsack we can break items into arbitrary
 * fractional parts to maximize the total value.
 * 
 * Example 1:
 * Input:
 *   N = 3, W = 50
 *   values[]  = {60, 100, 120}
 *   weights[] = {10, 20, 30}
 * Output: 240.00
 * Explanation:
 *   Item 1: ratio = 60/10 = 6.0  -> take all (wt: 10, val: 60, remaining W: 40)
 *   Item 2: ratio = 100/20 = 5.0 -> take all (wt: 20, val: 100, remaining W: 20)
 *   Item 3: ratio = 120/30 = 4.0 -> take 20/30 fraction (wt: 20, val: 80, remaining W: 0)
 *   Total value = 60 + 100 + 80 = 240.00.
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= W <= 10^5
 * 1 <= values[i], weights[i] <= 10^4
 * Must run in O(N log N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Fractional Knapsack vs 0/1 Knapsack (DP):
 *    - In 0/1 Knapsack, items are atomic (take all or none). Greedy ratio choice
 *      fails because high-ratio items may leave wasted empty space that cannot be filled.
 *    - In Fractional Knapsack, fractional divisibility allows completely packing
 *      the knapsack without leaving any wasted capacity.
 *    - This guarantees that picking items greedily in descending order of value density
 *      (value / weight) is globally optimal.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy by Value-to-Weight Ratio O(N log N) Time, O(1) Space:
 *   - Step 1: Calculate the unit density `ratio = (double)value / weight` for each item.
 *   - Step 2: Sort items in descending order of ratio:
 *       `a.value * b.weight > b.value * a.weight` (avoids floating point division precision issues).
 *   - Step 3: Iterate through sorted items:
 *       - If `item.weight <= remainingCapacity`:
 *           Take full item:
 *           `totalValue += item.value;`
 *           `remainingCapacity -= item.weight;`
 *       - Else:
 *           Take fraction `(remainingCapacity / item.weight)`:
 *           `totalValue += item.value * ((double)remainingCapacity / item.weight);`
 *           `break;` (knapsack is completely filled).
 *   - Return `totalValue`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    int value;
    int weight;
};

class Solution {
public:
    /**
     * Solves the Fractional Knapsack Problem.
     * @param w Capacity of the knapsack.
     * @param arr Array of Item structs {value, weight}.
     * @param n Number of items.
     * @return Maximum value achievable.
     */
    double fractionalKnapsack(int w, Item arr[], int n) {
        // Step 1: Sort items in descending order of value/weight ratio
        // Using cross-multiplication (a.val * b.wt > b.val * a.wt) prevents floating-point inaccuracies
        sort(arr, arr + n, [](const Item& a, const Item& b) {
            double r1 = (double)a.value / a.weight;
            double r2 = (double)b.value / b.weight;
            return r1 > r2;
        });

        double totalValue = 0.0;
        int remainingCapacity = w;

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Greedily consume the item with the highest remaining value-to-weight density:
            // Take the whole item if it fits, otherwise take the exact fractional slice needed.
            if (arr[i].weight <= remainingCapacity) {
                totalValue += arr[i].value;
                remainingCapacity -= arr[i].weight;
            } else {
                totalValue += ((double)arr[i].value / arr[i].weight) * remainingCapacity;
                remainingCapacity = 0;
                break; // Knapsack is completely full
            }
        }

        return totalValue;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // N = 3, W = 50
    // values[] = {60, 100, 120}, weights[] = {10, 20, 30}
    Item arr[] = {
        {60, 10},
        {100, 20},
        {120, 30}
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    int W = 50;

    cout << fixed << setprecision(2);
    double maxVal = solver.fractionalKnapsack(W, arr, n);
    cout << "Max Value in Knapsack = " << maxVal << " (Expected: 240.00)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting items by value/weight ratio: O(N log N).
 *   - Linear greedy packing loop: O(N).
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond input storage.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Fractional knapsack is greedy-solvable because fractions prevent capacity waste.
 * 2. 0/1 knapsack is NP-complete / requires Dynamic Programming because items cannot be split.
 */
