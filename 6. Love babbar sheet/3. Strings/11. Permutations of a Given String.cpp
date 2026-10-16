// Problem: Print All Permutations of a Given String
// Link (GFG): https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1
// Article: https://www.geeksforgeeks.org/dsa/write-a-c-program-to-print-all-permutations-of-a-given-string/
// Difficulty: Medium
// Topic: String, Recursion & Backtracking, Lexicographical Permutation

/*
Problem Statement:
Given a string S. Find all unique permutations of the string in lexicographically 
sorted order.
The string may contain duplicate characters.

Example 1:
Input: S = "ABC"
Output: ["ABC", "ACB", "BAC", "BCA", "CAB", "CBA"]

Example 2:
Input: S = "ABA"
Output: ["AAB", "ABA", "BAA"]
Explanation: Only 3 distinct permutations exist because 'A' is repeated.

Constraints:
- 1 <= S.length() <= 9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 10 (Print All Subsequences):
//   * A subsequence deletes elements while keeping the relative order of survivors.
//   * Total possibilities = 2^N.
// - In Problem 11 (Print All Permutations):
//   * Every character is RETAINED, but their POSITIONS / ORDER are re-arranged.
//   * Total possibilities = N! (or N! / (c1! * c2! ...) when duplicate characters exist).
//   * Crucial interview hazard: Duplicate characters (like in "ABA") can cause duplicate 
//     permutations if not deduplicated at each recursion level!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: In-Place Swap Backtracking with Local Level Hash Set
//   - At recursion level `idx`, swap `s[idx]` with `s[i]` for `i` from `idx` to `n - 1`.
//   - Maintain an `unordered_set<char> seenAtThisLevel`.
//   - If `seenAtThisLevel.count(s[i])`: skip (prevents branch duplication for repeated characters).
//   - Complexity: O(N! * N), O(N) recursion stack.
//
// Approach 2: Lexicographical Generation (Iterative Next Permutation - Optimal & Clean)
//   - Step 1: Sort `s` to get the smallest lexicographical permutation.
//   - Step 2: Push `s` to result, then apply `next_permutation` (Narayana Pandita's algorithm 
//     from Arrays Problem 15) in a loop until no higher permutation exists.
//   - Automatically handles duplicate characters cleanly and outputs in exact lexicographical 
//     order without any auxiliary sorting or sets!

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
private:
    // Helper for Approach 1: Swap Backtracking with local duplicate pruning
    void permuteBacktrack(string& s, int idx, vector<string>& result) {
        if (idx == (int)s.length()) {
            result.push_back(s);
            return;
        }

        unordered_set<char> seen;

        for (int i = idx; i < (int)s.length(); ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If character s[i] has already been placed at index `idx` in a prior branch of this
            // level, swapping it again would create identical duplicate permutations! Skip it!
            if (seen.find(s[i]) != seen.end()) {
                continue;
            }
            seen.insert(s[i]);

            swap(s[idx], s[i]);                     // Place character at idx
            permuteBacktrack(s, idx + 1, result);  // Recurse for remaining positions
            swap(s[idx], s[i]);                     // Backtrack (restore original)
        }
    }

public:
    // Method 1: Swap Backtracking (Standard Interview Template)
    vector<string> findPermutationBacktrack(string s) {
        vector<string> result;
        permuteBacktrack(s, 0, result);
        sort(result.begin(), result.end()); // Ensure lexicographical output
        return result;
    }

    // Method 2: Iterative Lexicographical Generation (Production Optimal)
    vector<string> findPermutationIterative(string s) {
        vector<string> result;
        sort(s.begin(), s.end()); // Start with lexicographically first permutation

        // do-while captures the initial sorted permutation as well
        do {
            result.push_back(s);
        } while (next_permutation(s.begin(), s.end()));

        return result;
    }
};

int main() {
    Solution sol;
    string s = "ABA";

    cout << "Unique Permutations of \"" << s << "\" (Backtracking):\n";
    vector<string> res1 = sol.findPermutationBacktrack(s);
    for (const string& str : res1) cout << "\"" << str << "\" ";
    cout << "\n\n";

    cout << "Unique Permutations of \"" << s << "\" (Iterative next_permutation):\n";
    vector<string> res2 = sol.findPermutationIterative(s);
    for (const string& str : res2) cout << "\"" << str << "\" ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N! * N) where N is length of string.
  * For distinct characters: N! permutations, each of length N.
  * For N = 9, 9! = 362,880 operations (well within typical 1 second time limits).
- Space Complexity: O(N) recursion stack depth (or O(1) auxiliary space for iterative).

Key Takeaways:
- Local level pruning with `seen.insert(s[i])` is the gold standard for duplicate handling in in-place swap permutations.
*/
