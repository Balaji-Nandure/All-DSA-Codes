#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Problem: Maximum sum of absolute difference of an array
 * 
 * Given an array, rearrange the elements such that the sum of absolute differences 
 * of consecutive elements |a[0] - a[1]| + |a[1] - a[2]| + ... + |a[n-1] - a[0]| is maximized.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "17. Maximize arr[i]*i", we paired elements with monotonic index weights (Rearrangement inequality).
 * - Here, the metric is consecutive absolute differences |a[i] - a[i+1]|. 
 * - To maximize |x - y|, x and y should be as far apart as possible: one should be from the large half 
 *   and one from the small half of the sorted array.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sort the array: arr[0] <= arr[1] <= ... <= arr[n-1].
 * - Interleave the smallest and largest elements:
 *   New arrangement: [arr[0], arr[n-1], arr[1], arr[n-2], arr[2], arr[n-3], ...]
 * - Mathematical Proof:
 *   In circular sum: sum = |arr[0] - arr[n-1]| + |arr[n-1] - arr[1]| + |arr[1] - arr[n-2]| + ...
 *   Notice every element in the upper half (arr[n/2] ... arr[n-1]) is strictly greater than its two neighbors,
 *   so it contributes +2 * arr[i] to the total sum.
 *   Every element in the lower half (arr[0] ... arr[n/2 - 1]) is strictly smaller than its two neighbors,
 *   so it contributes -2 * arr[i] to the total sum.
 *   Sum = 2 * sum(upper half) - 2 * sum(lower half).
 * - This maximizes the algebraic expansion of the absolute value sum.
 */

class Solution {
public:
    long long maxAbsDiffSum(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        // Step 1: Sort the array
        sort(arr.begin(), arr.end());

        // Step 2: Interleave elements from both ends
        vector<int> rearranged;
        int i = 0, j = n - 1;
        while (i <= j) {
            if (i == j) {
                rearranged.push_back(arr[i]);
                break;
            }
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Alternate smallest and largest to ensure maximum pairwise disparity
            rearranged.push_back(arr[i++]);
            rearranged.push_back(arr[j--]);
        }

        // Step 3: Compute circular adjacent difference sum
        long long total_diff = 0;
        for (int k = 0; k < n; k++) {
            // *** CRUCIAL LINE: Circular adjacent absolute differences ***
            total_diff += abs(rearranged[k] - rearranged[(k + 1) % n]);
        }

        return total_diff;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 2, 4, 8};
    cout << "Max sum 1: " << sol.maxAbsDiffSum(arr1) << "\n";
    // Sorted: 1, 2, 4, 8
    // Interleaved: 1, 8, 2, 4
    // Circular diffs: |1-8| + |8-2| + |2-4| + |4-1| = 7 + 6 + 2 + 3 = 18

    vector<int> arr2 = {10, 12, 15};
    cout << "Max sum 2: " << sol.maxAbsDiffSum(arr2) << "\n";
    // Sorted: 10, 12, 15 -> Interleaved: 10, 15, 12 -> |10-15| + |15-12| + |12-10| = 5 + 3 + 2 = 10

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) for sorting the array.
 * - Space Complexity: O(N) for the rearranged vector (can be reduced to O(1) by direct algebraic formula).
 */
