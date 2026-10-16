#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Minimum removals from array to make max - min <= K
 * 
 * Given an array of N integers and an integer K, find the minimum number of elements 
 * that must be removed such that the difference between the maximum and minimum 
 * of the remaining elements is at most K:
 * max(remaining) - min(remaining) <= K.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "24. Chocolate Distribution Problem", we minimized (max - min) for a FIXED subset size M.
 * - Here, the difference bound K is FIXED, and we want to MINIMIZE the number of REMOVALS.
 * - Key Inversion: Minimizing removals is mathematically IDENTICAL to MAXIMIZING the size 
 *   of the valid remaining subset!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sorted Contiguous Sliding Window (or Interval DP):
 *   1. Lemma:
 *      In a sorted array, any subset that satisfies max - min <= K can be expanded to include 
 *      ALL intermediate elements without violating the constraint!
 *      Proof: If a[j] - a[i] <= K, then for any i <= k <= j, a[j] - a[k] <= K and a[k] - a[i] <= K.
 *      Therefore, the optimal remaining subset MUST be a contiguous subarray [i ... j]!
 *   
 *   2. Sliding Window (Two Pointers) in O(N log N) Time:
 *      - Sort array ascending.
 *      - Maintain left pointer i and right pointer j.
 *      - For each right pointer j:
 *        While a[j] - a[i] > K: advance left pointer i++.
 *        max_retained = max(max_retained, j - i + 1).
 *      - Answer = N - max_retained.
 * 
 *   3. Why this beats 2D DP:
 *      A 2D DP table solve(i, j) = min(1 + solve(i+1, j), 1 + solve(i, j-1)) takes O(N^2) time.
 *      The sliding window takes strictly O(N) time after sorting, reducing total complexity to O(N log N).
 */

class Solution {
public:
    int removals(vector<int>& arr, int k) {
        int n = arr.size();
        if (n <= 1) return 0;

        // Step 1: Sort array
        sort(arr.begin(), arr.end());

        int max_retained = 0;
        int i = 0;

        // Step 2: Two pointers sliding window to maximize retained window length
        for (int j = 0; j < n; j++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Shrink window from the left until the spread (a[j] - a[i]) satisfies <= k
            while (arr[j] - arr[i] > k) {
                i++;
            }

            // *** CRUCIAL LINE: Maximize the number of retained elements ***
            max_retained = max(max_retained, j - i + 1);
        }

        // Minimum removals = Total elements - Maximum retained elements
        return n - max_retained;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int k1 = 4;
    cout << "Min Removals 1: " << sol.removals(arr1, k1) << "\n";
    // Best window: [9, 10, 11, 12] has length 4 with diff 12 - 9 = 3 <= 4.
    // Total 9 - 4 = 5 removals. Expected: 5.

    vector<int> arr2 = {1, 5, 6, 2, 8};
    int k2 = 2;
    cout << "Min Removals 2: " << sol.removals(arr2, k2) << "\n";
    // Sorted: 1, 2, 5, 6, 8. Windows with diff <= 2: [1, 2] (len 2), [5, 6] (len 2).
    // Min removals = 5 - 2 = 3. Expected: 3.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting. The sliding window pass is strictly O(N).
 * - Space Complexity: O(1) auxiliary memory.
 */
