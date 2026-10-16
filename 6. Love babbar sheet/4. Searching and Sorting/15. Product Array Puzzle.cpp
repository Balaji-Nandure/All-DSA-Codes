// Problem: Product Array Puzzle (Product of Array Except Self)
// Link (GFG): https://www.geeksforgeeks.org/problems/product-array-puzzle4525/1
// Article: https://www.geeksforgeeks.org/dsa/product-array-puzzle-set-2-o1-space/
// Difficulty: Easy / Medium
// Topic: Array, Prefix and Suffix Running Product, Division-Free Math

/*
Problem Statement:
Given an array `nums[]` of size n, construct a Product Array P (of same size n) 
such that P[i] is equal to the product of all the elements of nums EXCEPT nums[i].
Solve it in O(N) time WITHOUT USING THE DIVISION OPERATOR ('/').

Example 1:
Input: n = 5, nums = [10, 3, 5, 6, 2]
Output: [180, 600, 360, 300, 900]
Explanation: 
For i=0, P[0] = 3*5*6*2 = 180.
For i=1, P[1] = 10*5*6*2 = 600, etc.

Example 2:
Input: n = 2, nums = [12, 0]
Output: [0, 12]

Constraints:
- 1 <= n <= 10^5
- 0 <= nums[i] <= 200
- Elements can contain zeros.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Naive Division:
//   * Total product is calculated once, and `P[i] = totalProduct / nums[i]`.
//   * Flaws:
//       1. Division is explicitly prohibited by interview rules.
//       2. Division fails catastrophically with Divide-by-Zero errors if array has 0s!
// - In Division-Free Prefix-Suffix Running Products:
//   * `P[i]` is mathematically equal to:
//       `(Product of elements strictly to the left of i) * (Product of elements strictly to the right of i)`.
//   * We accumulate the left products into `P` in Pass 1, and fold the right products in Pass 2!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Dual-Pass Running Product in O(1) Auxiliary Space (Optimal & Chosen):
//   - Allocate `vector<long long> P(n, 1)`.
//   - Pass 1 (Left / Prefix Products):
//       * Maintain `long long prefix = 1`.
//       * For `i = 0` to `n - 1`:
//           `P[i] = prefix;` (stores product of all elements from 0 to i - 1)
//           `prefix *= nums[i];`
//   - Pass 2 (Right / Suffix Products):
//       * Maintain `long long suffix = 1`.
//       * For `i = n - 1` down to 0:
//           `P[i] *= suffix;` (multiplies left product by product of elements from i + 1 to n - 1)
//           `suffix *= nums[i];`
//   - Complexity: Strict O(N) time (2 linear passes), O(1) auxiliary space (reusing output vector)!
//   - Why this approach: Immune to division-by-zero exceptions and avoids extra memory.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<long long int> productExceptSelf(vector<long long int>& nums, int n) {
        vector<long long int> P(n, 1);

        // Pass 1: Compute prefix products for each index
        long long int prefix = 1;
        for (int i = 0; i < n; ++i) {
            P[i] = prefix;
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Accumulate prefix product for next elements
            prefix *= nums[i];
        }

        // Pass 2: Multiply by suffix products in reverse
        long long int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // At index i, P[i] already holds (prefix product). Multiplying by (suffix product)
            // yields the complete product of all elements except nums[i] without division!
            P[i] *= suffix;
            suffix *= nums[i];
        }

        return P;
    }
};

int main() {
    Solution sol;
    vector<long long int> nums1 = {10, 3, 5, 6, 2};
    vector<long long int> res1 = sol.productExceptSelf(nums1, nums1.size());
    cout << "Product array for nums1:\n";
    for (long long int x : res1) cout << x << " ";
    cout << "\n\n";

    vector<long long int> nums2 = {12, 0};
    vector<long long int> res2 = sol.productExceptSelf(nums2, nums2.size());
    cout << "Product array for nums2:\n";
    for (long long int x : res2) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), exactly 2 linear passes across the array.
- Space Complexity: O(1) auxiliary space (excluding the returned vector P of size N).

Key Takeaways:
- Splitting an exclusion query into `prefix * suffix` is the canonical technique 
  for division-free cumulative calculations.
*/
