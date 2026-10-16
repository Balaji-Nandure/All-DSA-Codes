// Problem: Array Subset of Another Array
// Link (Article): https://www.geeksforgeeks.org/dsa/find-whether-an-array-is-subset-of-another-array-set-1/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/array-subset-of-another-array2317/1
// Difficulty: Basic / Easy
// Topic: Array, Hash Table, Two Pointers, Multiset

/*
Problem Statement:
Given two arrays `a[]` of size `n` and `b[]` of size `m`.
Determine whether `b[]` is a subset of `a[]`. Both arrays can contain duplicate elements.
For `b[]` to be a subset of `a[]`, every element in `b[]` must appear in `a[]` with at least 
the same frequency (multiplicity).
Return "Yes" if `b[]` is a subset of `a[]`, otherwise return "No".

Example 1:
Input: a = [11, 7, 1, 13, 21, 3, 7, 3], b = [11, 3, 7, 1, 7]
Output: "Yes"
Explanation: Each of the elements {11, 3, 7, 1, 7} are present in a[] with equal or higher frequency.

Example 2:
Input: a = [1, 2, 3, 4, 4, 5, 6], b = [1, 2, 4, 4, 4]
Output: "No"
Explanation: b[] has three 4s, but a[] has only two 4s.

Example 3:
Input: a = [10, 5, 2, 23, 19], b = [19, 5, 3]
Output: "No"
Explanation: 3 is not present in a[].

Constraints:
- 1 <= a.size(), b.size() <= 10^5
- 1 <= a[i], b[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 6 (Union/Intersection): We found elements common to both arrays.
// - In Problem 27:
//   * A SUBSET is a directed containment check (`b ⊆ a`).
//   * Crucially, duplicates matter (Multi-set containment):
//     If `b` has two 7s, `a` MUST have at least two 7s, not just one!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Frequency Hash Map (OPTIMAL & CHOSEN)
//   - Build a frequency map of elements in array `a`: `freq[x]++`.
//   - For each element in array `b`:
//     * If `freq[x] <= 0` (either missing or exhausted): `b` cannot be a subset -> return "No".
//     * Else: Decrement `freq[x]--` to consume one occurrence.
//   - If all elements of `b` are successfully matched, return "Yes".
//   - Complexity: O(N + M) time, O(N) space.
//
// Approach 2: Sorting + Two Pointers (O(1) Space Alternative)
//   - Sort both `a` and `b`.
//   - March pointer `i` through `a` and pointer `j` through `b`.
//   - Complexity: O(N log N + M log M) time, O(1) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Frequency Hash Map (O(N + M) Time, O(N) Space - Preferred)
    // -------------------------------------------------------------------------
    string isSubset(vector<int>& a, vector<int>& b) {
        unordered_map<int, int> freq;

        // Step 1: Count element occurrences in the parent array `a`
        for (int x : a) {
            freq[x]++;
        }

        // Step 2: Validate and consume elements for the subset candidate `b`
        for (int x : b) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if element is present AND has remaining unconsumed count.
            // If x was never present or all copies in a[] have already been used,
            // b[] cannot be a valid multiset subset!
            if (freq.find(x) == freq.end() || freq[x] == 0) {
                return "No";
            }
            // Consume one instance from the available pool
            freq[x]--;
        }

        return "Yes";
    }

    // -------------------------------------------------------------------------
    // Method 2: Two Pointers with Sorting (O(N log N + M log M) Time, O(1) Space)
    // -------------------------------------------------------------------------
    string isSubsetSorted(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int i = 0, j = 0;
        int n = a.size(), m = b.size();

        while (i < n && j < m) {
            if (a[i] == b[j]) {
                i++;
                j++; // Match found, advance both
            } else if (a[i] < b[j]) {
                i++; // a[i] is smaller, keep searching in a
            } else {
                return "No"; // a[i] > b[j] means b[j] is missing in sorted a
            }
        }

        return (j == m) ? "Yes" : "No";
    }
};

/*
Time Complexity:
- Method 1 (Hash Map): O(N + M) — linear passes over both arrays.
- Method 2 (Sorting): O(N log N + M log M) for sorting, O(N + M) for two-pointer march.

Space Complexity:
- Method 1: O(N) Auxiliary Space for frequency table of array `a`.
- Method 2: O(1) Auxiliary Space (in-place).

Key Insights:
1. Multiplicity (Duplicate) Requirement:
   - Sets (`std::set` or `unordered_set`) discard duplicate values and would produce a FALSE POSITIVE
     for `a = [1, 2, 4, 4]` and `b = [1, 4, 4, 4]`!
   - Frequency map (`unordered_map<int, int>`) or multiset is mandatory.
*/
