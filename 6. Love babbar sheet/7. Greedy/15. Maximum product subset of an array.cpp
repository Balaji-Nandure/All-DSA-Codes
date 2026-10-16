#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Maximum product subset of an array
 * 
 * Given an array of integers, find the maximum product of a non-empty subset of the array.
 * Return the result modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "Maximum Subarray Product" (Kadane variant), this is a SUBSET problem, NOT a contiguous subarray problem.
 * - In a subset, order and contiguity do not matter: we can freely pick any subset of elements.
 * - Negative numbers multiply in pairs to form positive products.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Analysis of Signs:
 *   1. All positive numbers strictly increase the product (if > 1) or maintain it (if 1). Always include all positive numbers.
 *   2. An even number of negative numbers multiply to form a positive product. Always include them in pairs.
 *   3. If the count of negative numbers is odd:
 *      One negative number must be discarded to make the count even. To maximize the remaining product,
 *      we must drop the negative number with the smallest absolute value (i.e., the largest negative value, closest to 0).
 *   4. Edge cases with zeros:
 *      - If array contains only zeros -> answer is 0.
 *      - If array contains exactly one negative number and all other numbers are zero -> maximum product is 0 (picking {0} > {-x}).
 *      - If array contains only 1 element (even if negative) -> must pick it since subset must be non-empty.
 */

class Solution {
    const long long MOD = 1e9 + 7;
public:
    long long findMaxProduct(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];

        int count_neg = 0, count_zero = 0;
        int max_neg = INT_MIN; // Largest negative (closest to 0, e.g. -1 > -5)
        long long prod = 1;
        bool has_pos = false;

        for (int x : arr) {
            if (x == 0) {
                count_zero++;
                continue;
            }
            if (x < 0) {
                count_neg++;
                max_neg = max(max_neg, x);
            } else {
                has_pos = true;
            }
            // Temporarily multiply all non-zero elements
            prod = (prod * abs(x)) % MOD;
        }

        // Edge case 1: All elements are zeros
        if (count_zero == n) return 0;

        // Edge case 2: Exactly one negative and remaining all zeros (no positive numbers)
        // Picking {0} gives product 0, which is strictly greater than negative number
        if (count_neg == 1 && count_zero + count_neg == n) return 0;

        // Reset product to compute accurately
        prod = 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If count of negative numbers is odd, we must omit the negative number with the smallest absolute value (max_neg)
        bool excluded_max_neg = false;

        for (int x : arr) {
            if (x == 0) continue;
            
            // If negative count is odd, drop exactly one instance of max_neg
            if (x < 0 && (count_neg % 2 != 0) && x == max_neg && !excluded_max_neg) {
                excluded_max_neg = true;
                continue; // *** CRUCIAL LINE: Exclude the negative element closest to 0 ***
            }

            prod = (prod * (x < 0 ? -x : x)) % MOD;
        }

        return prod;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {-1, -1, -2, 4, 3};
    cout << "Max product 1: " << sol.findMaxProduct(arr1) << "\n"; // Expected: (-1 * -2) * 4 * 3 = 24 (-1 excluded)

    vector<int> arr2 = {-1, 0};
    cout << "Max product 2: " << sol.findMaxProduct(arr2) << "\n"; // Expected: 0

    vector<int> arr3 = {0, 0, 0};
    cout << "Max product 3: " << sol.findMaxProduct(arr3) << "\n"; // Expected: 0

    vector<int> arr4 = {-5};
    cout << "Max product 4: " << sol.findMaxProduct(arr4) << "\n"; // Expected: -5

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single pass to count signs and find max negative, followed by O(N) product pass.
 * - Space Complexity: O(1) auxiliary memory.
 */
