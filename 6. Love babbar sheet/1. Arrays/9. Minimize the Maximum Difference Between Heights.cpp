// Problem: Minimize the Heights II (Minimize the Maximum Difference Between Heights)
// Link (Article): https://www.geeksforgeeks.org/dsa/minimize-the-maximum-difference-between-the-heights/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/minimize-the-heights3351/1
// Difficulty: Medium
// Topic: Array, Greedy, Sorting

/*
Problem Statement:
Given an array `arr[]` denoting heights of `n` towers and a positive integer `k`. 
For each tower, you must either increase or decrease its height by `k` exactly once:
    `arr[i] = arr[i] + k`  OR  `arr[i] = arr[i] - k`

Find the minimum possible difference between the height of the shortest and tallest towers 
after you have modified each tower.
Note: A tower's modified height CANNOT be negative. If `arr[i] - k < 0`, that decrease is invalid.

Example 1:
Input: k = 2, arr = [1, 5, 8, 10]
Output: 5
Explanation: The modified array can be [1+2, 5-2, 8-2, 10-2] = [3, 3, 6, 8].
Minimum height is 3, maximum height is 8. Difference = 8 - 3 = 5.

Example 2:
Input: k = 3, arr = [3, 9, 12, 16, 20]
Output: 11
Explanation: Modified array can be [3+3, 9+3, 12-3, 16-3, 20-3] = [6, 12, 9, 13, 17].
Difference = 17 - 6 = 11.

Constraints:
- 1 <= k <= 10^7
- 1 <= n <= 10^5
- 1 <= arr[i] <= 10^7
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane): Local optimization where negative values were reset.
// - In Problem 9 (Minimize Heights):
//   * A global constraint optimization where EVERY element must make a binary decision (+k or -k).
//   * Greedily, smaller elements should be increased (+k) and larger elements decreased (-k).
//   * Sorting first exposes the split point `i` where we transition from adding `k` to subtracting `k`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// 1. Why Sort the Array First?
//    - If we have sorted heights: `arr[0] <= arr[1] <= ... <= arr[n - 1]`.
//    - Naturally, to minimize (max - min), we want smaller heights to grow (+k) 
//      and larger heights to shrink (-k).
// 2. The Partition Concept:
//    - There must exist some partition point `i` such that:
//      * Elements from index `0` to `i` are INCREASED by k (`arr[j] + k`).
//      * Elements from index `i + 1` to `n - 1` are DECREASED by k (`arr[j] - k`).
// 3. For any chosen split point `i`:
//    - The new candidate minimum height can only be: `min(arr[0] + k, arr[i + 1] - k)`.
//    - The new candidate maximum height can only be: `max(arr[i] + k, arr[n - 1] - k)`.
//    - Candidate difference = `candidateMax - candidateMin`.
//    - We iterate all possible split points `i` from 0 to n - 2 and take the global minimum!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getMinDiff(vector<int>& arr, int k) {
        int n = arr.size();
        if (n <= 1) return 0;

        // Step 1: Sort heights to establish monotonic order
        sort(arr.begin(), arr.end());

        // Initial answer: either all towers increased by k or all decreased by k
        int ans = arr[n - 1] - arr[0];

        // Step 2: Iterate through all possible partition points
        for (int i = 0; i < n - 1; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Problem constraint: Modified tower height CANNOT be negative.
            // If arr[i + 1] - k < 0, this tower cannot be decreased by k.
            // Since array is sorted, we cannot split here -> continue to next split!
            if (arr[i + 1] - k < 0) continue;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Left subarray [0 ... i] was increased by k: its smallest is arr[0] + k.
            // Right subarray [i+1 ... n-1] was decreased by k: its smallest is arr[i+1] - k.
            // The global minimum after this split MUST be one of these two!
            int minHeight = min(arr[0] + k, arr[i + 1] - k);

            // Left subarray was increased by k: its largest is arr[i] + k.
            // Right subarray was decreased by k: its largest is arr[n-1] - k.
            // The global maximum after this split MUST be one of these two!
            int maxHeight = max(arr[i] + k, arr[n - 1] - k);

            ans = min(ans, maxHeight - minHeight);
        }

        return ans;
    }
};

/*
Time Complexity: O(N log N)
- Sorting the array of size N takes O(N log N).
- Linear scan through the array takes O(N).
- Overall Time Complexity: O(N log N).

Space Complexity: O(1) Auxiliary Space
- In-place sorting and scalar variables only.

Key Insights:
1. Why Only Boundary Values Matter:
   - For any contiguous range [0 ... i] where all elements get +k, the minimum is always at 0
     and the maximum is always at i.
   - For [i + 1 ... n - 1] where all elements get -k, the minimum is always at i + 1
     and the maximum is always at n - 1.
   - Intermediate elements can NEVER be the global minimum or maximum, eliminating the need 
     to inspect every single element after modification!
*/
