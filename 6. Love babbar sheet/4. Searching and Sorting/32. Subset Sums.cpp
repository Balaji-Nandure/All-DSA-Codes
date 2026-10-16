/**
 * ============================================================================
 * Problem: Subset Sums (SPOJ SUBSUMS / Meet-in-the-Middle)
 * Category: Searching and Sorting / Divide and Conquer
 * 
 * Problem Statement:
 * Given a sequence of N integers and two integers A and B.
 * Count how many subsets of this sequence have a sum of elements lying in the 
 * closed interval [A, B] (i.e., A <= sum <= B).
 * 
 * Note: The empty subset is considered valid and its sum is 0.
 * 
 * Constraints:
 * 1 <= N <= 34
 * -10^7 <= elements <= 10^7
 * -10^9 <= A <= B <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Meet-in-the-Middle Paradigm:
 *    - N = 34 is too large for pure brute force: 2^34 ≈ 1.7 * 10^10 operations (TLE).
 *    - DP table fails because elements can be negative, and sum range spans billions.
 *    - But 34/2 = 17 is small: 2^17 = 131,072 operations (instantaneous).
 *    - We bisect the search space into two halves of size 17, compute all subset sums
 *      for both halves, and stitch them together using Binary Search.
 * 2. Range Query via Binary Search:
 *    - If a subset from the left half has sum S1, we need a subset sum S2 from the
 *      right half such that:
 *        A <= S1 + S2 <= B  ===>  (A - S1) <= S2 <= (B - S1)
 *    - By sorting the right half sums, the count of valid S2 can be found in O(log(2^(N/2)))
 *      via `upper_bound` and `lower_bound`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Partition Array:
 *    - Left half: arr[0 ... N/2 - 1] (size <= 17).
 *    - Right half: arr[N/2 ... N - 1] (size <= 17).
 * 2. Generate Subset Sums:
 *    - Generate all 2^(N/2) subset sums for left half -> store in vector `leftSums`.
 *    - Generate all 2^(N - N/2) subset sums for right half -> store in vector `rightSums`.
 * 3. Sort & Query:
 *    - Sort `rightSums` in non-decreasing order.
 *    - For each sum `s1` in `leftSums`:
 *        Find the number of elements in `rightSums` in range [A - s1, B - s1]:
 *        count += upper_bound(rightSums, B - s1) - lower_bound(rightSums, A - s1).
 *    - Total Time: O(2^(N/2) * log(2^(N/2))) ≈ O(N * 2^(N/2)), which for N=34
 *      is ~2.5 * 10^6 ops, executing in < 0.05 seconds!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    /**
     * Recursively generates all subset sums of a given subvector.
     */
    void generateSubsetSums(const vector<long long>& arr, int index, int end, 
                            long long currentSum, vector<long long>& subsetSums) {
        if (index == end) {
            subsetSums.push_back(currentSum);
            return;
        }

        // Choice 1: Exclude arr[index]
        generateSubsetSums(arr, index + 1, end, currentSum, subsetSums);

        // Choice 2: Include arr[index]
        generateSubsetSums(arr, index + 1, end, currentSum + arr[index], subsetSums);
    }

public:
    /**
     * Computes the number of subsets whose sum falls within [A, B].
     * @param arr Input array of integers.
     * @param A Lower bound of subset sum.
     * @param B Upper bound of subset sum.
     * @return Total count of valid subsets.
     */
    long long countSubsetsInRange(const vector<long long>& arr, long long A, long long B) {
        int n = arr.size();
        if (n == 0) {
            return (A <= 0 && 0 <= B) ? 1 : 0;
        }

        int mid = n / 2;

        // Step 1: Generate all subset sums of left half [0 ... mid - 1]
        vector<long long> leftSums;
        leftSums.reserve(1 << mid);
        generateSubsetSums(arr, 0, mid, 0, leftSums);

        // Step 2: Generate all subset sums of right half [mid ... n - 1]
        vector<long long> rightSums;
        rightSums.reserve(1 << (n - mid));
        generateSubsetSums(arr, mid, n, 0, rightSums);

        // Step 3: Sort the right subset sums for binary search
        sort(rightSums.begin(), rightSums.end());

        long long totalCount = 0;

        // Step 4: For each sum in left half, binary search valid matching range in right half
        for (long long s1 : leftSums) {
            long long targetLow = A - s1;
            long long targetHigh = B - s1;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Using upper_bound and lower_bound on the sorted right half transforms
            // an exponential 2^34 lookup into an O(log(2^(N/2))) range query for each s1.
            auto lowIt = lower_bound(rightSums.begin(), rightSums.end(), targetLow);
            auto highIt = upper_bound(rightSums.begin(), rightSums.end(), targetHigh);

            totalCount += (highIt - lowIt);
        }

        return totalCount;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Standard SPOJ example
    // Array: {1, -2, 3}, Range: [-1, 2]
    // Subsets:
    // {} -> sum 0 (in range)
    // {1} -> sum 1 (in range)
    // {-2} -> sum -2 (not in range)
    // {3} -> sum 3 (not in range)
    // {1, -2} -> sum -1 (in range)
    // {1, 3} -> sum 4 (not in range)
    // {-2, 3} -> sum 1 (in range)
    // {1, -2, 3} -> sum 2 (in range)
    // Total valid subsets = 5!
    vector<long long> arr1 = {1, -2, 3};
    cout << "Test 1: Count = " << solver.countSubsetsInRange(arr1, -1, 2) << " (Expected: 5)\n";

    // Test Case 2: Array: {5, -3, 2, 8}, Range: [2, 10]
    vector<long long> arr2 = {5, -3, 2, 8};
    cout << "Test 2: Count = " << solver.countSubsetsInRange(arr2, 2, 10) << " (Expected: 11)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Generating left sums: O(2^(N/2)).
 *   - Generating right sums: O(2^(N - N/2)).
 *   - Sorting right sums: O(2^(N - N/2) * log(2^(N - N/2))) = O((N/2) * 2^(N/2)).
 *   - Querying: 2^(N/2) iterations, each doing binary search in O(N/2).
 *   - Total Time Complexity: O(N * 2^(N/2)).
 *   - For N = 34: 17 * 2^17 ≈ 2.2 * 10^6 operations (executed in under 0.05 seconds).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(2^(N/2)) to store the subset sums.
 *   - For N = 34, 2^17 doubles/long longs ≈ 1 MB memory, exceptionally light.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Meet-in-the-Middle is the definitive algorithmic tool whenever N is in the
 *    range [30, 45] where 2^N is infeasible but 2^(N/2) easily fits in cache.
 * 2. Combining subset sum generation with binary search (lower_bound/upper_bound)
 *    converts an impossible 10^10 problem into a trivial 10^6 computation.
 */
