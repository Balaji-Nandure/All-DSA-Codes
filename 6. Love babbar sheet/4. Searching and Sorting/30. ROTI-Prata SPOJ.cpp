/**
 * ============================================================================
 * Problem: PRATA - Roti Prata (SPOJ PRATA)
 * Category: Searching and Sorting
 * 
 * Problem Statement:
 * The IEEE is organizing its annual party. An order has been placed for P pratas.
 * There are L cooks available, each with an associated rating/rank R (1 <= R <= 8).
 * 
 * A cook with rating R cooks:
 *   - 1st prata in 1 * R minutes,
 *   - 2nd prata in 2 * R minutes,
 *   - 3rd prata in 3 * R minutes,
 *   ...
 *   - k-th prata in k * R minutes.
 * 
 * Total time taken by a cook of rank R to prepare k pratas is:
 *   Time(k) = R * (1 + 2 + 3 + ... + k) = R * k * (k + 1) / 2.
 * 
 * All cooks work in parallel. What is the minimum time needed to fulfill 
 * the complete order of P pratas?
 * 
 * Constraints:
 * 1 <= P <= 1000 (Number of pratas ordered)
 * 1 <= L <= 50   (Number of cooks)
 * 1 <= R <= 8    (Rank of each cook)
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Non-linear (Quadratic) Productivity Growth:
 *    - In Painter's Partition (Problem 29), time was directly linear: time = length.
 *    - Here, the time required by a cook increases quadratically with the number
 *      of pratas cooked: T = R * k(k+1)/2.
 * 2. Inverting Quadratic Production within Binary Search:
 *    - Given a trial time limit T, we can calculate exactly how many pratas a cook
 *      of rank R can deliver by solving: k^2 + k - (2T / R) <= 0
 *      yielding k = floor((-1 + sqrt(1 + 8T/R)) / 2).
 *    - Alternatively, an incremental loop adds pratas until accumulated time > T.
 * 3. Monotonicity:
 *    - In more time T, every cook can make >= pratas.
 *    - Thus total pratas produced is strictly non-decreasing with respect to T.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Search Space [low, high]:
 *    - Minimum time: low = 0.
 *    - Maximum time: high = worst case where the highest rank cook (say R = 8)
 *      makes all P = 1000 pratas alone:
 *        T_max = 8 * 1000 * 1001 / 2 ≈ 4 * 10^6 minutes.
 * 2. Feasibility Check in O(L):
 *    - For a candidate time T:
 *        Total pratas = sum_{cook i} pratas_cooked(rank[i], T).
 *    - If Total >= P: time T is enough! Save T as answer and search [low, T - 1].
 *    - Else: time T is insufficient! Search [T + 1, high].
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
private:
    /**
     * Calculates the number of pratas a cook with rank R can make in time T.
     * Derived from: R * k * (k + 1) / 2 <= T  ==>  k^2 + k - 2T/R <= 0
     * By quadratic formula: k = (-1 + sqrt(1 + 8 * T / R)) / 2
     */
    long long pratasCooked(long long R, long long T) {
        long long discriminant = 1 + (8 * T) / R;
        long long k = (-1 + (long long)sqrt(discriminant)) / 2;
        return k;
    }

    /**
     * Checks if all cooks working together can make at least P pratas in time T.
     */
    bool isPossible(const vector<int>& ranks, int P, long long T) {
        long long totalPratas = 0;
        for (int r : ranks) {
            totalPratas += pratasCooked(r, T);
            // Early exit if quota already fulfilled
            if (totalPratas >= P) return true;
        }
        return totalPratas >= P;
    }

public:
    /**
     * Computes the minimum time needed to make P pratas with given cooks.
     * @param P Number of pratas required.
     * @param ranks Vector containing rank of each cook.
     * @return Minimum minutes required.
     */
    long long minTimeToMakePratas(int P, const vector<int>& ranks) {
        if (P <= 0) return 0;

        long long low = 0;
        // Upper bound: slowest cook (max rank) cooking all P pratas alone
        int maxRank = *max_element(ranks.begin(), ranks.end());
        long long high = (long long)maxRank * P * (P + 1) / 2;

        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic property: If cooks can deliver >= P pratas within 'mid' minutes,
            // we greedily lower the time ceiling to check if an even faster schedule is possible.
            if (isPossible(ranks, P, mid)) {
                ans = mid;
                high = mid - 1; // Try to achieve in less time
            } else {
                low = mid + 1;  // Not enough pratas baked, grant more time
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: P = 10 pratas, 4 cooks with ranks {1, 2, 3, 4}
    // Expected: 12 minutes
    // In 12 mins:
    // Cook 1 (R=1): makes 4 pratas (1+2+3+4 = 10 mins <= 12)
    // Cook 2 (R=2): makes 3 pratas (2+4+6 = 12 mins <= 12)
    // Cook 3 (R=3): makes 2 pratas (3+6 = 9 mins <= 12)
    // Cook 4 (R=4): makes 1 prata  (4 mins <= 12)
    // Total = 4 + 3 + 2 + 1 = 10 pratas in 12 mins!
    vector<int> ranks1 = {1, 2, 3, 4};
    cout << "Test 1: Min Time = " << solver.minTimeToMakePratas(10, ranks1) << " (Expected: 12)\n";

    // Test Case 2: P = 8, 1 cook with rank {1}
    // Time for 8 pratas: 1 * 8 * 9 / 2 = 36 mins
    vector<int> ranks2 = {1};
    cout << "Test 2: Min Time = " << solver.minTimeToMakePratas(8, ranks2) << " (Expected: 36)\n";

    // Test Case 3: P = 8, 8 cooks of rank 1
    // Each cook can make 1 prata in 1 min -> total 8 pratas in 1 min!
    vector<int> ranks3 = {1, 1, 1, 1, 1, 1, 1, 1};
    cout << "Test 3: Min Time = " << solver.minTimeToMakePratas(8, ranks3) << " (Expected: 1)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Search range: [0, max(R) * P * (P + 1) / 2] ≈ [0, 4 * 10^6].
 *   - Binary search iterations: log2(4 * 10^6) ≈ 22.
 *   - Feasibility check: O(L) using O(1) closed-form quadratic square root.
 *   - Total Time Complexity: O(L * log(max(R) * P^2)).
 *   - For L = 50, operations = 22 * 50 = 1,100 operations. Completes in microseconds (< 0.1 ms).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1). Zero heap allocations.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Arithmetic series T = R * k*(k+1)/2 can be inverted in O(1) via the quadratic formula.
 * 2. Binary search on answer turns an otherwise difficult multi-agent scheduling
 *    problem into independent, easily computable single-cook quota queries.
 */
