// Problem: Rasta and Kheshtak (Largest Common Square Sub-matrix)
// Link (HackerEarth): https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/rasta-and-kheshtak/
// Difficulty: Hard
// Topic: Searching, Binary Search on Answer, 2D Rolling Hash, Rabin-Karp 2D

/*
Problem Statement:
Given two 2D integer matrices:
  Matrix A of dimensions n1 x m1
  Matrix B of dimensions n2 x m2
Find the MAXIMUM integer X such that there exists an X x X square sub-matrix in A 
that is IDENTICAL to some X x X square sub-matrix in B.

Example 1:
Input:
n1 = 3, m1 = 3
A = [[1, 2, 3],
     [4, 5, 6],
     [7, 8, 9]]
n2 = 2, m2 = 2
B = [[5, 6],
     [8, 9]]
Output: 2
Explanation: The 2x2 submatrix [[5, 6], [8, 9]] is present in both A and B.

Constraints:
- 1 <= n1, m1, n2, m2 <= 700
- 0 <= A[i][j], B[i][j] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D Longest Common Substring / Subsequence:
//   * Linear strings were compared along 1 dimension.
// - In Rasta and Kheshtak (2D Common Submatrix):
//   * Matching is 2-DIMENSIONAL (both rows and columns must match simultaneously).
//   * A brute-force search over all possible sub-matrix pairs takes O((N*M)^2 * X^2), completely unfeasible!
//   * Monotonicity Property: If there exists a common square sub-matrix of size X, 
//     then any sub-square of size < X inside it is also identical!
//   * Therefore, we can BINARY SEARCH on the square side length X in range `[0 .. min(n1, m1, n2, m2)]`!
//   * Verification of size X is done in O(N1*M1 + N2*M2) using 2D Rolling Hashing (2D Rabin-Karp).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Side Length + 2D Rolling Hash (Optimal & Chosen):
//   - Range: `low = 0`, `high = min({n1, m1, n2, m2})`.
//   - Predicate `hasCommonSquare(size)`:
//       1. Compute 2D polynomial rolling hash of all `size x size` submatrices of A:
//          First roll along rows with base p1, then roll along columns with base p2.
//       2. Store all hashes of A in an `unordered_set<long long>` (or sorted vector).
//       3. Compute 2D polynomial rolling hash for all `size x size` submatrices of B.
//       4. If any hash of B exists in A's set, return `true`!
//   - If true: `ans = mid; low = mid + 1;`
//   - Else: `high = mid - 1;`
//   - Complexity: O(log(min_dim) * (N1 * M1 + N2 * M2)) time, O(N1 * M1) space.

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
    const long long P1 = 313;
    const long long P2 = 1009;
    const long long MOD = 1000000007;

    // Helper: Computes 2D hashes of all `size x size` submatrices for a grid
    vector<long long> compute2DHashes(const vector<vector<int>>& mat, int R, int C, int size) {
        vector<long long> hashes;
        if (size <= 0) return hashes;

        // Step 1: Compute 1D row hashes of length `size` for each row
        vector<vector<long long>> rowHash(R, vector<long long>(C - size + 1, 0));
        long long p1_pow = 1;
        for (int i = 0; i < size - 1; ++i) {
            p1_pow = (p1_pow * P1) % MOD;
        }

        for (int i = 0; i < R; ++i) {
            long long h = 0;
            for (int j = 0; j < size; ++j) {
                h = (h * P1 + mat[i][j]) % MOD;
            }
            rowHash[i][0] = h;

            for (int j = 1; j <= C - size; ++j) {
                h = (P1 * (h - mat[i][j - 1] * p1_pow) + mat[i][j + size - 1]) % MOD;
                if (h < 0) h += MOD;
                rowHash[i][j] = h;
            }
        }

        // Step 2: Roll vertically along columns of rowHash using P2
        int newC = C - size + 1;
        long long p2_pow = 1;
        for (int i = 0; i < size - 1; ++i) {
            p2_pow = (p2_pow * P2) % MOD;
        }

        for (int j = 0; j < newC; ++j) {
            long long h = 0;
            for (int i = 0; i < size; ++i) {
                h = (h * P2 + rowHash[i][j]) % MOD;
            }
            hashes.push_back(h);

            for (int i = 1; i <= R - size; ++i) {
                h = (P2 * (h - rowHash[i - 1][j] * p2_pow) + rowHash[i + size - 1][j]) % MOD;
                if (h < 0) h += MOD;
                hashes.push_back(h);
            }
        }

        return hashes;
    }

    bool hasCommonSquare(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
        if (size == 0) return true;

        int n1 = A.size(), m1 = A[0].size();
        int n2 = B.size(), m2 = B[0].size();

        vector<long long> hashesA = compute2DHashes(A, n1, m1, size);
        vector<long long> hashesB = compute2DHashes(B, n2, m2, size);

        // Sort hashesA for O(log K) binary search lookup
        sort(hashesA.begin(), hashesA.end());

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Search if any 2D submatrix hash of B is present in the sorted hash list of A
        for (long long hb : hashesB) {
            if (binary_search(hashesA.begin(), hashesA.end(), hb)) {
                return true;
            }
        }

        return false;
    }

public:
    int maxCommonSquare(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n1 = A.size(), m1 = A[0].size();
        int n2 = B.size(), m2 = B[0].size();

        int low = 0;
        int high = min({n1, m1, n2, m2});
        int bestSize = 0;

        // Binary search on the square dimension
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (hasCommonSquare(A, B, mid)) {
                bestSize = mid;
                low = mid + 1; // Try to find a larger common square
            } else {
                high = mid - 1; // Square of size mid does not exist, search smaller
            }
        }

        return bestSize;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> B = {
        {5, 6},
        {8, 9}
    };

    cout << "Maximum size of common square submatrix: " 
         << sol.maxCommonSquare(A, B) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log(min_dim) * ((N1 * M1) log(N1 * M1) + (N2 * M2) log(N1 * M1))).
  * The binary search range is at most 700 -> log2(700) ≈ 10 iterations.
  * In each iteration, 2D rolling hash generates all sub-grids in linear O(N * M) time.
- Space Complexity: O(N1 * M1) auxiliary space to store hashes.

Key Takeaways:
- 2D Rolling Hash decomposes matrix comparison into two 1D polynomial hash passes:
  Horizontal rolling followed by vertical rolling.
*/
