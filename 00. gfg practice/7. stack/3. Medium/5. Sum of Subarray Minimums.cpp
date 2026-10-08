/*
    Problem Name: Sum of Subarray Minimums
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 907

    Problem Statement:
    Given an array `arr[]` of positive integers, find the total sum of the minimum elements of every possible subarray.
    Note: It is guaranteed that the total sum will fit within a 32-bit unsigned integer.

    Examples:
    Input: arr = [10, 20]
    Output: 40
    Explanation: Subarrays are [10], [20], [10, 20].
                 Minimums are 10, 20, 10.
                 Sum = 10 + 20 + 10 = 40.

    Input: arr = [1, 2, 3, 4]
    Output: 20
    Explanation: Subarrays are:
                 [1] (min 1), [2] (min 2), [3] (min 3), [4] (min 4),
                 [1, 2] (min 1), [2, 3] (min 2), [3, 4] (min 3),
                 [1, 2, 3] (min 1), [2, 3, 4] (min 2),
                 [1, 2, 3, 4] (min 1).
                 Sum = 1 + 2 + 3 + 4 + 1 + 2 + 3 + 1 + 2 + 1 = 20.

    Constraints:
    1 <= arr.size() <= 3 * 10^4
    1 <= arr[i] <= 10^3

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N)

    Approach 1: Brute Force All Subarrays (O(N^2) Time, O(1) Space)
    Approach 2: Monotonic Stack (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Brute Force (Approach 1):
       - Generate each subarray `arr[i...j]` with nested loops, tracking the running minimum.
       - Add the running minimum to the total sum.
       - Time: O(N^2), Space: O(1). TLE for N = 3 * 10^4.

    2. Contribution Technique with Monotonic Stack (Approach 2):
       - Instead of asking "What is the minimum of each subarray?", we ask:
         "In how many subarrays is `arr[i]` the minimum element?"
       - For each element `arr[i]`:
         * Find the distance to the Previous Smaller Element (PSE): `left[i]`
         * Find the distance to the Next Smaller Element (NSE): `right[i]`
         * Number of subarrays where `arr[i]` is minimum = `left[i] * right[i]`.
         * Contribution of `arr[i]` to total sum = `arr[i] * left[i] * right[i]`.
       - Handling Duplicates:
         * To avoid double-counting subarrays with duplicate minimums, we use strict `<` for one side
           and non-strict `<=` for the other:
           - Left: strictly smaller (`arr[st.top()] > arr[i]` pops elements)
           - Right: smaller or equal (`arr[st.top()] >= arr[i]` pops elements)
       - Total Time: O(N) because each index is pushed and popped at most once.
       - Auxiliary Space: O(N) for `left`, `right`, and `stack`.

    DRY RUN:
    Example: arr = [10, 20], n = 2
    - Left boundary (PSE):
      * i = 0 (val 10): st is empty -> left[0] = 0 + 1 = 1, st = [0]
      * i = 1 (val 20): arr[st.top()] = 10 <= 20, st not popped -> left[1] = 1 - 0 = 1, st = [0, 1]
    - Right boundary (NSE):
      * i = 1 (val 20): st is empty -> right[1] = 2 - 1 = 1, st = [1]
      * i = 0 (val 10): arr[st.top()] = 20 >= 10 -> pop 1 -> st empty -> right[0] = 2 - 0 = 2, st = [0]
    - Contributions:
      * i = 0: 10 * left[0] * right[0] = 10 * 1 * 2 = 20
      * i = 1: 20 * left[1] * right[1] = 20 * 1 * 1 = 20
      * Total = 20 + 20 = 40.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// ============================================================================
// Approach 1: Brute Force All Subarrays (O(N^2) Time, O(1) Space)
// ============================================================================
class SolutionBruteForce {
public:
    unsigned long long sumSubMins(vector<int>& arr) {
        int n = arr.size();
        unsigned long long ans = 0;

        for (int i = 0; i < n; i++) {
            int currentMin = arr[i];
            for (int j = i; j < n; j++) {
                currentMin = min(currentMin, arr[j]);
                ans += currentMin;
            }
        }

        return ans;
    }
};

// ============================================================================
// Approach 2: Monotonic Stack (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionOptimal {
public:
    unsigned long long sumSubMins(vector<int>& arr) {
        int n = arr.size();

        vector<int> left(n);
        vector<int> right(n);
        stack<int> st;

        // Step 1: Find distance to Previous Smaller Element (PSE)
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] > arr[i]) {
                st.pop();
            }

            if (st.empty()) {
                left[i] = i + 1; // All elements to the left are greater
            } else {
                left[i] = i - st.top();
            }

            st.push(i);
        }

        // Clear stack for next pass
        while (!st.empty()) {
            st.pop();
        }

        // Step 2: Find distance to Next Smaller or Equal Element (NSE)
        // Using '>=' here handles duplicates cleanly to avoid double counting
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }

            if (st.empty()) {
                right[i] = n - i; // All elements to the right are greater
            } else {
                right[i] = st.top() - i;
            }

            st.push(i);
        }

        // Step 3: Calculate contribution of each element
        unsigned long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (unsigned long long)arr[i] * left[i] * right[i];
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    unsigned long long sumSubMins(vector<int>& arr) {
        SolutionOptimal solver;
        return solver.sumSubMins(arr);
    }
};
