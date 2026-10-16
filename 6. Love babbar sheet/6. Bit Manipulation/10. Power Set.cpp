/**
 * ============================================================================
 * Problem: Power Set (Generating All Subsets via Bitmasking)
 * Category: Bit Manipulation / Combinatorics
 * 
 * Problem Statement:
 * Given a string S (or an array of N distinct elements), generate all possible 
 * subsequences (the Power Set).
 * Return all subsequences (often requested in lexicographically sorted order).
 * 
 * Example 1:
 * Input:  S = "abc"
 * Output: ["", "a", "ab", "abc", "ac", "b", "bc", "c"]
 * Total Subsets: 2^3 = 8
 * 
 * Example 2:
 * Input:  S = "aa"
 * Output: ["", "a", "a", "aa"]
 * 
 * Constraints:
 * 1 <= Length of string N <= 20
 * Total subsets = 2^N
 * Must run in O(N * 2^N) time and O(1) auxiliary space (excluding result vector).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Recursive Backtracking vs Combinatorial Bitmasking:
 *    - In Category 3 (Strings, Problem 10), we generated subsequences via
 *      recursive pick/don't-pick decisions, consuming O(N) stack frames.
 *    - In Bit Manipulation, the power set is modeled as a bijective mapping:
 *      every integer mask from 0 to (2^N - 1) corresponds directly to one unique subset!
 * 2. Hardware Integer as Set Representation:
 *    - The i-th bit of integer `mask` represents the inclusion (1) or exclusion (0)
 *      of element `S[i]`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Bitmasking Iteration O(N * 2^N) Time, O(1) Auxiliary Space:
 *   - Total subsets for string of length N = `total = 1 << N` (2^N).
 *   - For `mask` from 0 to `total - 1`:
 *       - Construct string `sub = ""`
 *       - For `i` from 0 to `N - 1`:
 *           - If `(mask & (1 << i)) != 0`:
 *               `sub += S[i];`
 *       - Append `sub` to result.
 *   - Sort result if lexicographical ordering is required.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Generates all subsequences of a string using bitmasking.
     * @param s Input string of length N.
     * @return Vector of all 2^N subsequences.
     */
    vector<string> AllPossibleStrings(string s) {
        int n = s.length();
        int totalSubsets = 1 << n; // 2^n total subsets
        vector<string> powerSet;
        powerSet.reserve(totalSubsets);

        // Iterate through all 2^n binary masks
        for (int mask = 0; mask < totalSubsets; ++mask) {
            string currentSub = "";

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Bijective Bitmask Mapping: The i-th bit of 'mask' acts as an inclusion flag;
            // if bit i is 1, character s[i] is included in the current subset.
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    currentSub += s[i];
                }
            }

            powerSet.push_back(currentSub);
        }

        // Sort lexicographically if required by problem specification
        sort(powerSet.begin(), powerSet.end());

        return powerSet;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: "abc" -> 8 subsets
    string s = "abc";
    vector<string> subsets = solver.AllPossibleStrings(s);

    cout << "Power Set of \"" << s << "\" (Total: " << subsets.size() << "):\n";
    for (const string& str : subsets) {
        cout << "\"" << str << "\" ";
    }
    cout << "\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Outer loop runs 2^N times.
 *   - Inner loop runs N times for each mask.
 *   - Lexicographical sorting of 2^N strings of average length N/2 takes:
 *     O(N * 2^N * log(2^N)) = O(N^2 * 2^N).
 *   - Generation Time: O(N * 2^N).
 *   - For N = 15: 15 * 32,768 ≈ 4.9 * 10^5 operations (< 5 ms).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond the storage required for the output vector.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. An N-bit integer can directly represent any subset of an N-element universe.
 * 2. Bitmask iteration is entirely non-recursive, avoiding stack overflow risks.
 */
