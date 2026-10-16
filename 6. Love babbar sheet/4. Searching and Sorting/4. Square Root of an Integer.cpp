// Problem: Square Root of an Integer (Floor Sqrt & Count Squares)
// Link (GFG): https://www.geeksforgeeks.org/problems/count-squares3649/1
// Article: https://www.geeksforgeeks.org/dsa/square-root-of-an-integer/
// Difficulty: Easy
// Topic: Searching, Binary Search on Answer, Integer Square Root

/*
Problem Statement:
Part 1 (Floor Square Root):
Given an integer n, find the square root of n. If n is not a perfect square, 
return floor(sqrt(n)).
You must not use any built-in math functions like `sqrt()` or `pow()`.

Part 2 (GFG Count Squares Problem):
Given a positive integer N, find the count of natural numbers (1, 2, 3...) 
whose squares are strictly less than N.

Example 1:
Input: n = 5
Output: 2
Explanation: 2*2 = 4 <= 5, whereas 3*3 = 9 > 5.

Example 2:
Input: n = 4
Output: 2

Example 3 (Count Squares):
Input: N = 9
Output: 2
Explanation: Squares strictly less than 9 are 1^2 = 1, 2^2 = 4 (Count = 2).

Constraints:
- 1 <= n <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In previous array searches:
//   * We searched an explicitly stored array in memory.
// - In Square Root:
//   * There is NO array stored in memory!
//   * We perform Binary Search on a VIRTUAL MONOTONIC SEARCH SPACE `[1 .. n]`.
//   * Because `f(x) = x * x` is strictly monotonically increasing for `x >= 0`, 
//     binary search applies seamlessly.
//   * Critical interview pitfall: `mid * mid` can easily overflow a 32-bit signed integer 
//     (up to 10^18 for n = 10^9). We must use `long long` or division `mid <= n / mid`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Answer Range [1 .. n] (Optimal & Chosen):
//   - Range: `low = 1`, `high = n`.
//   - Loop while `low <= high`:
//       * `mid = low + (high - low) / 2`.
//       * If `mid * mid <= n`:
//           `ans = mid;` (candidate floor root)
//           `low = mid + 1;` (search for a larger integer root)
//       * Else:
//           `high = mid - 1;` (mid is too large)
//   - Complexity: O(log N) iterations = at most 30 steps for N = 10^9.
//   - Space Complexity: O(1) auxiliary space.

#include <iostream>

using namespace std;

class Solution {
public:
    // Floor of square root of n in O(log n) time without library functions
    long long floorSqrt(long long n) {
        if (n == 0 || n == 1) return n;

        long long low = 1;
        long long high = n / 2; // Sqrt(n) <= n / 2 for all n >= 4
        long long ans = 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Use 64-bit long long to prevent 32-bit integer overflow when calculating mid * mid.
            // If mid * mid <= n, mid is a valid floor candidate; greedily search right for larger.
            if (mid * mid <= n) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }

    // GFG "Count Squares" Problem: Number of perfect squares strictly less than N
    int countSquares(int N) {
        if (N <= 1) return 0;
        // Count of numbers whose square is strictly less than N is floorSqrt(N - 1)
        return (int)floorSqrt(N - 1);
    }
};

int main() {
    Solution sol;
    cout << "floorSqrt(5): " << sol.floorSqrt(5) << "\n";
    cout << "floorSqrt(16): " << sol.floorSqrt(16) << "\n";
    cout << "floorSqrt(2147483647): " << sol.floorSqrt(2147483647) << "\n\n";

    cout << "countSquares strictly < 9: " << sol.countSquares(9) << "\n";
    cout << "countSquares strictly < 3: " << sol.countSquares(3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log N). Binary search halves the integer range at every step.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Binary Search on virtual value ranges (without any array) is one of the most powerful 
  tools in algorithmic computer science.
*/
