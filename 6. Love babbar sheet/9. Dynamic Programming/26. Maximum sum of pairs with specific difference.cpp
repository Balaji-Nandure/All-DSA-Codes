#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum sum of pairs with specific difference
 * 
 * Given an array of integers arr[] and a number K, pair elements such that 
 * the absolute difference between any paired elements is strictly less than K:
 * |x - y| < K.
 * Each element can participate in at most one pair.
 * Find the maximum possible sum of all such pairs.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "20. Min sum of absolute difference of pairs" where all elements were forced to pair,
 *   here pairing is OPTIONAL, and only pairs satisfying |x - y| < K are allowed.
 * - We want to MAXIMIZE the total sum of elements in the selected disjoint pairs.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy from Largest Down (or 1D DP):
 *   1. Sort array in ascending order: arr[0] <= arr[1] <= ... <= arr[N-1].
 *   2. To maximize sum, we must greedily attempt to pair the LARGEST numbers first.
 *   3. Iterate from right to left (i = N - 1 down to 1):
 *      Check adjacent difference: arr[i] - arr[i - 1].
 *      - If arr[i] - arr[i - 1] < K:
 *        Pair them immediately!
 *        total_sum += arr[i] + arr[i - 1].
 *        Skip both elements: i -= 2.
 *        Why is this greedy choice optimal?
 *        Because arr[i] is the largest available number. Pairing it with arr[i-1] uses the 
 *        smallest possible gap (arr[i] - arr[i-1] <= arr[i] - arr[i-2]). If arr[i] can pair 
 *        with arr[i-1], pairing it gives the largest possible contribution (arr[i] + arr[i-1]).
 *      - If arr[i] - arr[i - 1] >= K:
 *        Since array is sorted, for any j < i - 1: arr[i] - arr[j] >= arr[i] - arr[i - 1] >= K.
 *        Thus, arr[i] CANNOT pair with ANY remaining number.
 *        Discard arr[i] and continue: i -= 1.
 */

class Solution {
public:
    int maxSumPairWithDifferenceLessThanK(int arr[], int N, int K) {
        // Step 1: Sort array ascending
        sort(arr, arr + N);

        int max_sum = 0;
        int i = N - 1;

        // Step 2: Greedily pair from right to left (largest values first)
        while (i > 0) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if adjacent sorted elements satisfy the difference threshold
            if (arr[i] - arr[i - 1] < K) {
                // Pair them and consume both
                max_sum += arr[i] + arr[i - 1];
                i -= 2;
            } else {
                // arr[i] cannot pair with any smaller number; discard it
                i -= 1;
            }
        }

        return max_sum;
    }
};

int main() {
    Solution sol;
    int arr1[] = {3, 5, 10, 15, 17, 12, 9};
    int N1 = sizeof(arr1) / sizeof(arr1[0]);
    int K1 = 4;
    cout << "Max Pair Sum 1: " << sol.maxSumPairWithDifferenceLessThanK(arr1, N1, K1) << "\n";
    // Sorted: 3, 5, 9, 10, 12, 15, 17
    // Pairs: (15, 17) [diff 2 < 4, sum 32]
    //        (10, 12) [diff 2 < 4, sum 22]
    //        (3, 5)   [diff 2 < 4, sum 8]
    // Total sum = 32 + 22 + 8 = 62. Expected: 62.

    int arr2[] = {5, 15, 10, 300};
    int N2 = sizeof(arr2) / sizeof(arr2[0]);
    int K2 = 12;
    cout << "Max Pair Sum 2: " << sol.maxSumPairWithDifferenceLessThanK(arr2, N2, K2) << "\n";
    // Sorted: 5, 10, 15, 300 -> pair (10, 15) diff 5 < 12, sum 25. Expected: 25.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting the array. The backward pass is O(N).
 * - Space Complexity: O(1) auxiliary space beyond input array.
 */
