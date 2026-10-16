#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Find the K-th Permutation Sequence of first N natural numbers
 * 
 * Given two integers N and K, find the K-th lexicographically smallest permutation 
 * sequence of numbers from 1 to N.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Print all permutations", we generated ALL permutations using Backtracking.
 * - Generating all permutations sequentially until reaching K takes O(K * N) time.
 * - When N = 9, K can be up to 362,880. Exhaustive backtracking is needlessly inefficient.
 * - Here, we can directly compute the EXACT K-th permutation in O(N^2) time using the 
 *   Factoradic (Factorial Number System) without exploring any other permutations!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Factorial Number System (Factoradic Mathematics):
 *   Consider N numbers: [1, 2, ..., N].
 *   If we fix the first digit, there are exactly (N - 1)! permutations that start with that digit.
 *   
 *   1. Adjust K to 0-based indexing: k = K - 1.
 *   2. Available numbers pool: numbers = [1, 2, 3, ..., N].
 *   3. At each position (from left to right):
 *      - Block size = (n - 1)!
 *      - The index of the next digit in `numbers` is:
 *        idx = k / (n - 1)!
 *      - Append numbers[idx] to result string.
 *      - Erase numbers[idx] from the candidate pool.
 *      - Update k for remaining positions:
 *        k = k % (n - 1)!
 *   4. Continue until all digits are determined.
 *   
 *   This mathematical leap cuts runtime from O(K * N) to strictly O(N^2) time!
 */

class Solution {
public:
    string getPermutation(int n, int k) {
        // Precompute factorials: fact[i] = i!
        vector<int> fact(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }

        // Available candidate numbers [1, 2, ..., n]
        vector<int> numbers;
        for (int i = 1; i <= n; i++) {
            numbers.push_back(i);
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Convert to 0-based indexing so that integer division directly yields pool indices
        k = k - 1;

        string result = "";

        for (int i = n; i >= 1; i--) {
            // Number of permutations for each choice of the current position
            int block_size = fact[i - 1];

            // Determine which number from the pool occupies this position
            int chosen_idx = k / block_size;
            result += to_string(numbers[chosen_idx]);

            // *** CRUCIAL LINE: Remove the used number and reduce k to remainder ***
            numbers.erase(numbers.begin() + chosen_idx);
            k %= block_size;
        }

        return result;
    }
};

int main() {
    Solution sol;
    int n1 = 3, k1 = 3;
    cout << "Permutation (" << n1 << ", " << k1 << "): " << sol.getPermutation(n1, k1) << "\n";
    // Permutations of [1, 2, 3]:
    // 1: 123
    // 2: 132
    // 3: 213 <-- 3rd permutation
    // 4: 231
    // 5: 312
    // 6: 321

    int n2 = 4, k2 = 9;
    cout << "Permutation (" << n2 << ", " << k2 << "): " << sol.getPermutation(n2, k2) << "\n";
    // Expected: "2314"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) because erasing an element from a vector takes O(N) across N positions.
 *   (Can be optimized to O(N log N) using a Fenwick tree/Binary Indexed Tree).
 * - Space Complexity: O(N) to store candidate numbers and precomputed factorials.
 */
