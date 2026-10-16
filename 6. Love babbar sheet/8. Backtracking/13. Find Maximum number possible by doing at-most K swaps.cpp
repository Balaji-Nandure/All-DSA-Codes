#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Find Maximum number possible by doing at-most K swaps
 * 
 * Given a positive integer represented as a string and an integer K,
 * find the lexicographically maximum number that can be formed by 
 * performing AT MOST K swaps of any two digits.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike problems where we rearrange all elements freely (greedy sorting),
 *   here each swap costs 1 unit from our limited budget of K swaps.
 * - Why a purely greedy swap fails:
 *   If there are multiple occurrences of the maximum digit in the suffix, swapping with 
 *   different instances changes which digits are displaced to the right, fundamentally 
 *   altering what can be formed in subsequent swaps!
 *   Therefore, we must branch on ALL instances of the maximum digit using Backtracking.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Suffix Maximum Pruning:
 *   1. Track the global maximum string found so far: `max_str`.
 *   2. Base cases:
 *      - If k == 0 or idx == str.length(): terminate recursion branch.
 *   3. Suffix Scan:
 *      Find the maximum character in the suffix str[idx + 1 ... n - 1]:
 *      Let max_char = max(str[j]) for j > idx.
 *   4. Decision Branching:
 *      - If max_char > str[idx]:
 *        We should swap str[idx] with max_char to place the largest possible digit at this high-value position.
 *        Loop through all positions j from idx + 1 to n - 1 where str[j] == max_char:
 *          swap(str[idx], str[j]);
 *          if str > max_str: max_str = str;
 *          backtrack(str, k - 1, idx + 1); // Consumed 1 swap
 *          swap(str[idx], str[j]);          // *** BACKTRACK ***
 *      - If max_char <= str[idx]:
 *        Current digit is already optimal for this position; advance to idx + 1 without consuming a swap:
 *        backtrack(str, k, idx + 1).
 */

class Solution {
    void backtrack(string& str, int k, int idx, string& max_str) {
        // Base case: Swap budget exhausted or reached end of string
        if (k == 0 || idx == (int)str.length() - 1) {
            return;
        }

        int n = str.length();
        char max_char = str[idx];

        // Find the maximum character in the suffix
        for (int j = idx + 1; j < n; j++) {
            if (str[j] > max_char) {
                max_char = str[j];
            }
        }

        // If a strictly larger digit exists in suffix, try swapping with all its occurrences
        if (max_char != str[idx]) {
            k--; // Will perform a swap in this step

            for (int j = idx + 1; j < n; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Only swap with positions that hold the maximum suffix character
                if (str[j] == max_char) {
                    swap(str[idx], str[j]); // Apply swap

                    if (str > max_str) {
                        max_str = str; // Update global best
                    }

                    // Recurse to next index with remaining k - 1 swaps
                    backtrack(str, k, idx + 1, max_str);

                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Backtrack: Undo swap to allow other candidate placements
                    swap(str[idx], str[j]);
                }
            }
        } else {
            // No larger digit exists in suffix; advance to next position without burning a swap
            backtrack(str, k, idx + 1, max_str);
        }
    }

public:
    string findMaximumNum(string str, int k) {
        string max_str = str;
        backtrack(str, k, 0, max_str);
        return max_str;
    }
};

int main() {
    Solution sol;
    string s1 = "1234567";
    int k1 = 4;
    cout << "Max with " << k1 << " swaps: " << sol.findMaximumNum(s1, k1) << "\n"; // Expected: 7654321

    string s2 = "3435335";
    int k2 = 3;
    cout << "Max with " << k2 << " swaps: " << sol.findMaximumNum(s2, k2) << "\n"; // Expected: 5543333

    string s3 = "1034";
    int k3 = 2;
    cout << "Max with " << k3 << " swaps: " << sol.findMaximumNum(s3, k3) << "\n"; // Expected: 4301

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^K) in the worst case where duplicate max characters branch.
 *   Suffix maximum filtering limits branching strictly to identical max digits, pruning suboptimal swaps.
 * - Space Complexity: O(N) recursion stack depth.
 */
