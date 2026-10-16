#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Problem: Maximize sum of consecutive differences in a circular array (Swap and Maximize)
 * 
 * Given an array of n elements, find the maximum possible sum of absolute differences 
 * of adjacent elements in a circular configuration:
 * sum = |a[0] - a[1]| + |a[1] - a[2]| + ... + |a[n-2] - a[n-1]| + |a[n-1] - a[0]|
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is the canonical "Swap and Maximize" problem from GFG.
 * - In problem 18, we constructed the interleaved array explicitly using extra space O(N).
 * - Here, we derive the closed-form mathematical expression to achieve O(1) auxiliary space:
 *   sum = 2 * sum(arr[n - 1 - i] - arr[i]) for i from 0 to n/2 - 1.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Mathematical Proof for O(1) Space:
 *   When the array is sorted: a[0] <= a[1] <= ... <= a[n-1].
 *   The optimal circular arrangement alternates low and high values:
 *   Sequence: a[0], a[n-1], a[1], a[n-2], a[2], a[n-3], ...
 *   Notice:
 *     |a[0] - a[n-1]| = a[n-1] - a[0]
 *     |a[n-1] - a[1]| = a[n-1] - a[1]
 *     |a[1] - a[n-2]| = a[n-2] - a[1]
 *     |a[n-2] - a[2]| = a[n-2] - a[2]
 *   Every element in the upper half appears twice with a POSITIVE sign (+).
 *   Every element in the lower half appears twice with a NEGATIVE sign (-).
 *   Therefore, the total sum is identically:
 *     Total = 2 * sum_{i=0}^{n/2 - 1} (arr[n - 1 - i] - arr[i])
 *   This formula holds whether n is even or odd (the middle element in odd n cancels out).
 */

class Solution {
public:
    long long swapAndMaximize(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        // Step 1: Sort array in non-decreasing order
        sort(arr.begin(), arr.end());

        // Step 2: Directly accumulate using the closed-form formula in O(1) extra space
        long long max_sum = 0;

        for (int i = 0; i < n / 2; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Each high element arr[n-1-i] contributes +2, each low element arr[i] contributes -2
            max_sum += 2LL * (arr[n - 1 - i] - arr[i]);
        }

        return max_sum;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {4, 2, 1, 8};
    cout << "Max circular sum 1: " << sol.swapAndMaximize(arr1) << "\n"; // Expected: 18

    vector<int> arr2 = {10, 12};
    cout << "Max circular sum 2: " << sol.swapAndMaximize(arr2) << "\n"; // Expected: 4

    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "Max circular sum 3: " << sol.swapAndMaximize(arr3) << "\n"; // Expected: 2*(5-1) + 2*(4-2) = 8 + 4 = 12

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting. The loop is O(N).
 * - Space Complexity: O(1) auxiliary space (no temporary vector needed).
 */
