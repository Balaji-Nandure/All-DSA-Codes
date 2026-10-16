// Problem: Maximum Product Subarray
// Link (LeetCode 152): https://leetcode.com/problems/maximum-product-subarray/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/maximum-product-subarray3604/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-product-subarray-set-3/
// Difficulty: Medium
// Topic: Array, Dynamic Programming, Kadane's Multiplicative Variant

/*
Problem Statement:
Given an integer array `nums`, find a contiguous non-empty subarray within the array that has 
the largest product, and return that product.

Example 1:
Input: nums = [2, 3, -2, 4]
Output: 6
Explanation: Subarray [2, 3] has the largest product 6.

Example 2:
Input: nums = [-2, 0, -1]
Output: 0
Explanation: The result cannot be 2, because [-2, -1] is not a contiguous subarray.

Example 3 (Two Negatives Flip):
Input: nums = [-2, 3, -4]
Output: 24
Explanation: Entire array [-2, 3, -4] has product (-2) * 3 * (-4) = 24!

Constraints:
- 1 <= nums.length <= 10^5
- -10 <= nums[i] <= 10
- The product of any prefix or suffix fits within a 64-bit integer.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane's Sum): Adding a negative number ALWAYS decreases the sum.
// - In Problem 23 (Maximum Product Subarray):
//   * Multiplying by a negative number can turn a tiny negative number into a MASSIVE POSITIVE number!
//   * Negative * Negative = Positive!
//   * Therefore, the MINIMUM (most negative) product seen so far is just as valuable as the maximum,
//     because the next negative number can flip it into the global maximum!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Modified Multiplicative Kadane (OPTIMAL & CHOSEN)
//   - Maintain both:
//     * `maxProd`: Maximum product ending at current index.
//     * `minProd`: Minimum (most negative) product ending at current index.
//   - When we encounter a negative number `x < 0`:
//     * Multiplying by a negative flips signs: the maximum becomes minimum, and minimum becomes maximum!
//     * Hence: `swap(maxProd, minProd)` BEFORE calculation!
//   - At each step:
//     * `maxProd = max((long long)x, maxProd * x)`
//     * `minProd = min((long long)x, minProd * x)`
//   - Update `globalMax = max(globalMax, maxProd)`.
//   - Complexity: Exactly O(N) time in 1 pass, O(1) space!
//
// Approach 2: Prefix and Suffix Scan
//   - Calculate product from left-to-right (reset to 1 on 0) and right-to-left.
//   - Maximum product is the peak of prefix and suffix products.
//   - Also O(N) time and O(1) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Modified Multiplicative Kadane (O(N) Time, O(1) Space)
    // -------------------------------------------------------------------------
    long long maxProduct(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        long long maxProd = nums[0];
        long long minProd = nums[0];
        long long globalMax = nums[0];

        for (int i = 1; i < n; i++) {
            long long x = nums[i];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When multiplying by a negative number, the largest positive becomes the smallest negative,
            // and the smallest negative becomes the largest positive!
            // Swapping maxProd and minProd accounts for this sign inversion instantly!
            if (x < 0) {
                swap(maxProd, minProd);
            }

            // Either start a new subarray at x, or extend the previous product
            maxProd = max(x, maxProd * x);
            minProd = min(x, minProd * x);

            globalMax = max(globalMax, maxProd);
        }

        return globalMax;
    }

    // -------------------------------------------------------------------------
    // Method 2: Dual Prefix-Suffix Scan (Alternative Clean Intuition)
    // -------------------------------------------------------------------------
    long long maxProductPrefixSuffix(vector<int>& nums) {
        int n = nums.size();
        long long prefix = 1, suffix = 1;
        long long maxAns = LLONG_MIN;

        for (int i = 0; i < n; i++) {
            if (prefix == 0) prefix = 1; // Reset product on encountering 0
            if (suffix == 0) suffix = 1;

            prefix *= nums[i];
            suffix *= nums[n - 1 - i];

            maxAns = max({maxAns, prefix, suffix});
        }

        return maxAns;
    }
};

/*
Time Complexity: O(N)
- Exactly one linear pass through the array. O(1) constant work at each element: O(N).

Space Complexity: O(1) Auxiliary Space
- Uses only 3 scalar variables (`maxProd`, `minProd`, `globalMax`).

Key Insights:
1. The Swap Trick:
   - `if (x < 0) swap(maxProd, minProd)` eliminates complex 3-way `max(x, max*x, min*x)` branching.
2. Zeros in Product:
   - When `x == 0`, `maxProd = max(0, 0) = 0`, naturally resetting the running product
     at the next index because `max(x_next, 0 * x_next) = x_next`.
*/
