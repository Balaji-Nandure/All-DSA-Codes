// Problem: Find the Union and Intersection of Two Arrays
// Link (Article): https://www.geeksforgeeks.org/dsa/find-union-and-intersection-of-two-unsorted-arrays/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/union-of-two-arrays3538/1
// Difficulty: Easy
// Topic: Array, Two Pointers, Hash Set, Sorting

/*
Problem Statement:
Given two arrays `a[]` and `b[]` of size `n` and `m` respectively:
1. Find the Union of the two arrays (the collection of all distinct elements from both arrays).
2. Find the Intersection of the two arrays (the collection of elements common to both arrays).

Example 1:
Input: a = [1, 2, 3, 4, 5], b = [1, 2, 3]
Output: 
- Union Count = 5 (Elements: {1, 2, 3, 4, 5})
- Intersection Elements = [1, 2, 3]

Example 2:
Input: a = [85, 25, 1, 32, 54, 6], b = [85, 2]
Output: 
- Union Count = 7 (Elements: {1, 2, 6, 25, 32, 54, 85})
- Intersection Elements = [85]

Constraints:
- 1 <= n, m <= 10^5
- 0 <= a[i], b[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - Problems 1 to 5 dealt with a SINGLE array.
// - Problem 6 introduces MERGING TWO ARRAYS simultaneously:
//   * Two pointers move across two independent sequences (i for array `a`, j for array `b`).
//   * We must handle DUPLICATES across both the same array and between different arrays.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Case A: When Arrays are SORTED (Optimal Two Pointers)
//   - Pointer `i` traverses `a`, pointer `j` traverses `b`:
//     * If `a[i] < b[j]`: `a[i]` is smaller, include in Union (if not duplicate), i++.
//     * If `b[j] < a[i]`: `b[j]` is smaller, include in Union (if not duplicate), j++.
//     * If `a[i] == b[j]`: Include in both Union and Intersection (if not duplicate), i++, j++.
//   - Time Complexity: O(N + M) single pass!
//   - Space Complexity: O(1) auxiliary space (excluding returned result).
//   - Why this: Merging two sorted streams is optimal and eliminates all hashing overhead.
//
// Case B: When Arrays are UNSORTED (Hash Set)
//   - Insert all elements from both arrays into an `unordered_set`.
//   - Number of elements in the set is the size of the Union.
//   - Time Complexity: O(N + M) average.
//   - Space Complexity: O(N + M) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Two Pointers for Sorted Arrays (O(N + M) Time, O(1) Extra Space)
    // -------------------------------------------------------------------------
    vector<int> findUnionSorted(const vector<int>& a, const vector<int>& b) {
        int n = a.size(), m = b.size();
        int i = 0, j = 0;
        vector<int> unionRes;

        while (i < n && j < m) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // To prevent duplicate additions in the union array, we check:
            // if unionRes is non-empty AND its last element equals the current candidate,
            // we simply advance the pointer WITHOUT adding a duplicate!
            if (a[i] <= b[j]) {
                if (unionRes.empty() || unionRes.back() != a[i]) {
                    unionRes.push_back(a[i]);
                }
                // If both are equal, advance both to avoid redundant duplicate checks
                if (a[i] == b[j]) j++;
                i++;
            } else {
                if (unionRes.empty() || unionRes.back() != b[j]) {
                    unionRes.push_back(b[j]);
                }
                j++;
            }
        }

        // Exhaust remaining elements from array `a`
        while (i < n) {
            if (unionRes.empty() || unionRes.back() != a[i]) {
                unionRes.push_back(a[i]);
            }
            i++;
        }

        // Exhaust remaining elements from array `b`
        while (j < m) {
            if (unionRes.empty() || unionRes.back() != b[j]) {
                unionRes.push_back(b[j]);
            }
            j++;
        }

        return unionRes;
    }

    // -------------------------------------------------------------------------
    // Method 2: Two Pointers for Intersection of Sorted Arrays (O(N + M) Time)
    // -------------------------------------------------------------------------
    vector<int> findIntersectionSorted(const vector<int>& a, const vector<int>& b) {
        int n = a.size(), m = b.size();
        int i = 0, j = 0;
        vector<int> interRes;

        while (i < n && j < m) {
            if (a[i] < b[j]) {
                i++;
            } else if (b[j] < a[i]) {
                j++;
            } else {
                // Elements match: add to intersection if not already added
                if (interRes.empty() || interRes.back() != a[i]) {
                    interRes.push_back(a[i]);
                }
                i++;
                j++;
            }
        }

        return interRes;
    }

    // -------------------------------------------------------------------------
    // Method 3: Hash Set Method for Unsorted Arrays (GFG Practice: return count)
    // -------------------------------------------------------------------------
    int doUnionUnsorted(vector<int>& a, vector<int>& b) {
        unordered_set<int> st;
        for (int x : a) st.insert(x);
        for (int x : b) st.insert(x);
        return st.size(); // Total distinct elements
    }
};

/*
Time Complexity:
- Sorted (Two Pointers): O(N + M) — each element of `a` and `b` inspected at most once.
- Unsorted (Hash Set): O(N + M) average time for hash insertions.

Space Complexity:
- Sorted (Two Pointers): O(1) Auxiliary Space (ignoring the output container).
- Unsorted (Hash Set): O(N + M) Auxiliary Space in worst case when all elements are distinct.

Key Insights:
1. Merge-Step Parallel:
   - The two-pointer traversal on sorted arrays is identical to the Merge step of Merge Sort.
2. Clean De-duplication:
   - `unionRes.empty() || unionRes.back() != candidate` is the cleanest idiom in C++ 
     to filter consecutive duplicates on the fly without using an extra `std::set`.
*/
