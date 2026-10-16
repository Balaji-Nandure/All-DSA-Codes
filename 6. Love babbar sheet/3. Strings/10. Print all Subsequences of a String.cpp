// Problem: Print all Subsequences of a String (Power Set)
// Link (GFG): https://www.geeksforgeeks.org/problems/power-set4302/1
// Article: https://www.geeksforgeeks.org/dsa/print-subsequences-string/
// Difficulty: Medium
// Topic: String, Recursion & Backtracking, Bit Manipulation (Power Set)

/*
Problem Statement:
Given a string s of length n, find all possible subsequences of the string.
A subsequence is a sequence that can be derived from the given string by deleting 
zero or more characters without changing the relative order of the remaining characters.
Usually, in problems like GFG Power Set, the non-empty subsequences are returned in 
lexicographically sorted order.

Example 1:
Input: s = "abc"
Output: ["a", "ab", "abc", "ac", "b", "bc", "c"]
Explanation: There are 2^3 - 1 = 7 non-empty subsequences.

Example 2:
Input: s = "aa"
Output: ["a", "a", "aa"]

Constraints:
- 1 <= s.length() <= 16 (Exponential 2^N output)
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 9 (Longest Repeating Subsequence):
//   * We only computed the MAXIMAL LENGTH of a particular repeating subsequence using DP.
// - In Problem 10 (Print All Subsequences):
//   * We must explicitly CONSTRUCT all 2^N possible combinations of characters!
//   * For each character, there is a binary decision:
//       1. INCLUDE it in the subsequence.
//       2. EXCLUDE it from the subsequence.
//   * This is the quintessential "Pick / Don't Pick" pattern of backtracking.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Bit Manipulation (Power Set Algorithm)
//   - For a string of length N, numbers from 0 to (2^N - 1) have binary representations 
//     where the j-th bit indicates whether `s[j]` is included.
//   - Mask loop: `for (int mask = 1; mask < (1 << n); ++mask)`.
//   - Complexity: O(N * 2^N) time, O(1) recursion space.
//   - Clean, iterative, zero recursion stack overhead.
//
// Approach 2: Recursive Backtracking (Pick & Don't Pick)
//   - Function `generate(idx, currentString)`:
//       1. Base case: `idx == n` -> push `currentString`.
//       2. Pick: `currentString.push_back(s[idx])`; `generate(idx + 1)`; `currentString.pop_back()`.
//       3. Don't Pick: `generate(idx + 1)`.
//   - Complexity: O(2^N) states, O(N) stack depth.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Recursive Backtracking Helper
    void generateSubsequences(const string& s, int idx, string& current, vector<string>& result) {
        if (idx == (int)s.length()) {
            if (!current.empty()) {
                result.push_back(current);
            }
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Choice 1: "PICK" the current character s[idx]
        current.push_back(s[idx]);
        generateSubsequences(s, idx + 1, current, result);

        // Backtrack (undo choice)
        current.pop_back();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Choice 2: "DON'T PICK" the current character s[idx]
        generateSubsequences(s, idx + 1, current, result);
    }

public:
    // Method 1: Recursive Backtracking
    vector<string> allSubsequencesRecursive(string s) {
        vector<string> result;
        string current = "";
        generateSubsequences(s, 0, current, result);
        sort(result.begin(), result.end()); // Sort lexicographically
        return result;
    }

    // Method 2: Bit Manipulation (Power Set)
    vector<string> allSubsequencesBitmask(const string& s) {
        int n = s.length();
        int totalSubsequences = (1 << n); // 2^n
        vector<string> result;
        result.reserve(totalSubsequences - 1);

        // Loop through all binary masks from 1 to 2^n - 1 (excluding 0 which is empty string)
        for (int mask = 1; mask < totalSubsequences; ++mask) {
            string sub = "";
            for (int j = 0; j < n; ++j) {
                // If the j-th bit of mask is set, include s[j]
                if (mask & (1 << j)) {
                    sub += s[j];
                }
            }
            result.push_back(sub);
        }

        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution sol;
    string s = "abc";

    cout << "Subsequences of \"" << s << "\" using Backtracking:\n";
    vector<string> res1 = sol.allSubsequencesRecursive(s);
    for (const string& str : res1) cout << "\"" << str << "\" ";
    cout << "\n\n";

    cout << "Subsequences of \"" << s << "\" using Bitmask:\n";
    vector<string> res2 = sol.allSubsequencesBitmask(s);
    for (const string& str : res2) cout << "\"" << str << "\" ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * 2^N) generation + O(2^N * log(2^N) * N) = O(N^2 * 2^N) for sorting.
  * For N = 16, 2^16 = 65,536 combinations, easily generated in milliseconds.
- Space Complexity: O(N) recursion stack depth (or O(1) auxiliary space for bit manipulation).

Key Takeaways:
- Subsequences naturally correspond to binary bits of numbers 0 to 2^N - 1.
- The "Pick vs Don't Pick" recursive skeleton is the foundational template for 0/1 Knapsack,
  Subset Sum, and combinatorial search.
*/
