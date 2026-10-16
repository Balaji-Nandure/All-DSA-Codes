// Problem: Find the Repeating and the Missing Number
// Link (GFG): https://www.geeksforgeeks.org/problems/find-missing-and-repeating2512/1
// Article: https://www.geeksforgeeks.org/dsa/find-a-repeating-and-a-missing-number/
// Difficulty: Medium
// Topic: Searching, Math (Sum & Sum of Squares), Bit Manipulation (XOR), In-Place Negation

/*
Problem Statement:
Given an unsorted array of size N of positive integers in the range [1, N].
One number 'B' occurs twice (repeating) and one number 'A' from the set {1, 2, ... N} 
is missing. Find these two numbers. Return `{repeating, missing}`.

Example 1:
Input: N = 2, arr = [2, 2]
Output: Repeating = 2, Missing = 1

Example 2:
Input: N = 3, arr = [1, 3, 3]
Output: Repeating = 3, Missing = 2

Constraints:
- 2 <= N <= 10^5
- 1 <= arr[i] <= N
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 11 (Find Duplicate Number in N+1 Integers):
//   * We only needed to find the duplicate number (Floyd's Tortoise and Hare).
// - In Problem 7 (Find Repeating AND Missing):
//   * Array length is exactly N (not N+1).
//   * We have TWO unknowns simultaneously: Repeating (B) and Missing (A).
//   * The key challenge is finding BOTH in O(N) time using strictly O(1) extra memory 
//     without 32-bit overflow!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Math (Sum and Sum of Squares) - Non-Mutating O(1) Space
//   - Let S = sum of first N natural numbers = N * (N + 1) / 2.
//   - Let S2 = sum of squares of first N natural numbers = N * (N + 1) * (2N + 1) / 6.
//   - Let arrSum = sum(arr[i]), arrSum2 = sum(arr[i]^2).
//   - Equation 1: `arrSum - S = B - A` -> `diff = B - A`.
//   - Equation 2: `arrSum2 - S2 = B^2 - A^2 = (B - A) * (B + A)`.
//   - Therefore: `sumBA = (B^2 - A^2) / (B - A) = B + A`.
//   - Solving the linear system:
//       `B = (diff + sumBA) / 2` (Repeating)
//       `A = sumBA - B`          (Missing)
//   - Complexity: O(N) time, O(1) space, read-only!
//
// Approach 2: Bit Manipulation (XOR Partitioning) - Overflow-Proof
//   - XOR all elements in array with all numbers 1 to N:
//       `xorVal = (arr[0] ^ ... ^ arr[N-1]) ^ (1 ^ 2 ^ ... ^ N) = A ^ B`.
//   - Find the rightmost set bit in `xorVal`: `setBit = xorVal & (-xorVal)`.
//   - Partition elements and numbers 1..N into two buckets based on `setBit`.
//   - Resulting two values will be A and B! Single pass verifies which is repeating.

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    // Approach 1: Mathematical Equations (Read-only, O(1) Space)
    vector<int> findTwoElementMath(vector<int>& arr) {
        long long n = arr.size();

        long long expectedSum = n * (n + 1) / 2;
        long long expectedSqSum = n * (n + 1) * (2 * n + 1) / 6;

        long long actualSum = 0;
        long long actualSqSum = 0;

        for (long long x : arr) {
            actualSum += x;
            actualSqSum += (x * x);
        }

        // diff = B - A (Repeating - Missing)
        long long diff = actualSum - expectedSum;

        // sqDiff = B^2 - A^2 = (B - A) * (B + A)
        long long sqDiff = actualSqSum - expectedSqSum;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Algebraic reduction: (B^2 - A^2) / (B - A) gives (B + A) in O(1)!
        long long sumBA = sqDiff / diff;

        long long repeating = (diff + sumBA) / 2;
        long long missing = sumBA - repeating;

        return {(int)repeating, (int)missing};
    }

    // Approach 2: XOR Partitioning (Immune to integer overflow)
    vector<int> findTwoElementXOR(vector<int>& arr) {
        int n = arr.size();
        int xorAll = 0;

        // XOR all array elements and all numbers from 1 to N
        for (int i = 0; i < n; ++i) {
            xorAll ^= arr[i];
            xorAll ^= (i + 1);
        }

        // xorAll now equals (Repeating ^ Missing)
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Isolate the rightmost set bit of xorAll to separate Repeating and Missing into different buckets
        int setBit = xorAll & (-xorAll);

        int bucket1 = 0, bucket2 = 0;

        for (int i = 0; i < n; ++i) {
            if (arr[i] & setBit) bucket1 ^= arr[i];
            else bucket2 ^= arr[i];

            if ((i + 1) & setBit) bucket1 ^= (i + 1);
            else bucket2 ^= (i + 1);
        }

        // Disambiguate which bucket is Repeating and which is Missing
        int countBucket1 = 0;
        for (int x : arr) {
            if (x == bucket1) countBucket1++;
        }

        if (countBucket1 == 2) {
            return {bucket1, bucket2}; // bucket1 is repeating, bucket2 is missing
        } else {
            return {bucket2, bucket1}; // bucket2 is repeating, bucket1 is missing
        }
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 3, 3};
    vector<int> res1 = sol.findTwoElementMath(arr1);
    cout << "Math Method: Repeating = " << res1[0] << ", Missing = " << res1[1] << "\n";

    vector<int> arr2 = {2, 2};
    vector<int> res2 = sol.findTwoElementXOR(arr2);
    cout << "XOR Method:  Repeating = " << res2[0] << ", Missing = " << res2[1] << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) linear time (single pass over array of size N).
- Space Complexity: O(1) auxiliary space (no hash maps, sets, or array mutations).

Key Takeaways:
- Both Math (Sum & Sum of Squares) and XOR partitioning achieve true O(1) space.
- XOR is preferred when numbers can be up to 10^9 to avoid 64-bit square overflow.
*/
