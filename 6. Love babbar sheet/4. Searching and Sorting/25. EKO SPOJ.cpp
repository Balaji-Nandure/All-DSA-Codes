/**
 * ============================================================================
 * Problem: EKO - Woodcutting Sawmill (SPOJ EKO)
 * Category: Searching and Sorting
 * 
 * Problem Statement:
 * Lumberjack Mirko needs to chop down M metres of wood. It is an easy job for him
 * since he has a nifty new woodcutting machine that can take down forests like 
 * wildfire. However, Mirko is only allowed to cut a single row of trees.
 * 
 * The machine works as follows: Mirko sets a height parameter H (in metres). 
 * The machine raises a giant sawblade to that height and cuts off all parts of
 * the trees that are higher than H (of course, trees not higher than H remain 
 * intact). Mirko then takes the parts that were cut off.
 * 
 * For example, if the tree heights are 20, 15, 10, and 17 metres, and Mirko raises
 * the sawblade to 15 metres, the remaining tree heights will be 15, 15, 10, and 15
 * metres, and Mirko will take 5 metres from the first tree and 2 metres from the
 * fourth tree (7 metres in total).
 * 
 * Mirko is ecologically minded, so he doesn't want to cut off more wood than
 * necessary. That's why he wants to set his sawblade as high as possible.
 * Calculate the maximum integer height of the sawblade that still allows him to 
 * cut off at least M metres of wood.
 * 
 * Constraints:
 * 1 <= N <= 1,000,000 (number of trees)
 * 1 <= M <= 2,000,000,000 (metres of wood needed)
 * 1 <= height[i] <= 1,000,000,000
 * The sum of all heights will exceed M, ensuring a solution always exists.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Monotonic Predicate over Sawblade Height:
 *    - In Aggressive Cows (Problem 23) and Book Allocation (Problem 24), we had
 *      to maximize the minimum distance or minimize the maximum pages.
 *    - Here, the wood yield f(H) is monotonically non-increasing as blade height H
 *      increases: higher H -> less wood collected.
 * 2. Range of Answer is [0, max(tree_height)]:
 *    - Setting H = 0 cuts every tree completely to ground level.
 *    - Setting H = max(tree_height) cuts 0 meters of wood.
 *    - Since heights reach up to 10^9 and N up to 10^6, accumulated wood can reach
 *      10^15, strictly requiring 64-bit integers (`long long`) to prevent overflow.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Brute Force O(max(H) * N):
 *    - Testing each possible saw height from max(H) down to 0 takes 10^9 * 10^6 =
 *      10^15 operations. Unusable (Time Limit Exceeded).
 * 2. Binary Search on Answer Space O(N log(max(H))):
 *    - Since wood collected decreases strictly monotonically with H, we can
 *      binary search over the search space low = 0, high = max(height).
 *    - Mid is our candidate blade height.
 *    - In O(N) time, compute total wood collected:
 *        wood = sum(max(0LL, tree[i] - mid)) for each tree.
 *    - If wood >= M: Mid is valid! Mirko wants to set H as high as possible, so
 *      record mid as candidate answer and search higher half (low = mid + 1).
 *    - If wood < M: Not enough wood. Saw is too high! Must lower saw (high = mid - 1).
 *    - Total iterations: log2(10^9) ≈ 30 iterations. 30 * 10^6 ≈ 3 * 10^7 operations,
 *      which comfortably runs within 0.3 seconds!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    /**
     * Helper predicate: Checks if setting blade height to 'H' yields at least 'M' wood.
     */
    bool isValidHeight(const vector<long long>& trees, long long H, long long M) {
        long long collectedWood = 0;
        for (long long tree : trees) {
            if (tree > H) {
                collectedWood += (tree - H);
                // Early exit optimization: avoid unnecessary loop execution if already enough wood
                if (collectedWood >= M) return true;
            }
        }
        return collectedWood >= M;
    }

public:
    /**
     * Finds the maximum sawblade height to obtain at least M meters of wood.
     * @param trees Vector containing heights of all trees.
     * @param M Amount of wood needed.
     * @return Maximum height H.
     */
    long long getMaxSawHeight(const vector<long long>& trees, long long M) {
        if (trees.empty()) return 0;

        long long low = 0;
        long long high = 0;
        for (long long h : trees) {
            high = max(high, h);
        }

        long long ans = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic check: If height 'mid' yields >= M wood, Mirko can test higher saw positions
            // to minimize ecological damage, shifting search to [mid + 1, high].
            if (isValidHeight(trees, mid, M)) {
                ans = mid;         // Record possible optimal height
                low = mid + 1;     // Try for a higher blade height
            } else {
                high = mid - 1;    // Wood is insufficient; lower the blade
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Standard SPOJ example
    // Trees = {20, 15, 10, 17}, Needed = 7
    // Height 15 -> (20-15) + (17-15) = 5 + 2 = 7 meters. Exactly satisfied!
    vector<long long> trees1 = {20, 15, 10, 17};
    long long M1 = 7;
    cout << "Test 1: Max Height = " << solver.getMaxSawHeight(trees1, M1) << " (Expected: 15)\n";

    // Test Case 2: Large scale heights
    // Trees = {4, 42, 40, 26, 46}, Needed = 20
    vector<long long> trees2 = {4, 42, 40, 26, 46};
    long long M2 = 20;
    cout << "Test 2: Max Height = " << solver.getMaxSawHeight(trees2, M2) << " (Expected: 36)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Search space: [0, max(H)]. Max value is 10^9.
 *   - Binary search iterations: log2(10^9) ≈ 30.
 *   - In each iteration, we scan N trees: O(N).
 *   - Overall Time: O(N * log(max(H))).
 *   - For N = 10^6, ~3 * 10^7 operations -> executes in < 0.2s.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond input storage. No recursion, no auxiliary arrays.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. When the function f(x) is monotonic, always prioritize Binary Search on Answer
 *    over sorting or complex greedy heuristics.
 * 2. Tree height sum easily exceeds 2^31 - 1; always accumulate wood in `long long`.
 * 3. Notice the direction: Mirko wants MAXIMIZE H, so when f(mid) >= M is true,
 *    we move to the right (`low = mid + 1`).
 */
