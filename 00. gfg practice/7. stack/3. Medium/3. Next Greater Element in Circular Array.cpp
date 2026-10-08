/*
    Problem Name: Next Greater Element in Circular Array
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 503

    Problem Statement:
    Given a circular integer array `arr[]`, determine the next greater element (NGE) for each element.
    The next greater element of `arr[i]` is the first element greater than `arr[i]` when traversing circularly.
    If no such element exists, return -1 for that position.

    Examples:
    Input: arr = [1, 3, 2, 4]
    Output: [3, 4, 4, -1]
    Explanation: NGE for 1 is 3, for 3 is 4, for 2 is 4, for 4 does not exist (-1).

    Input: arr = [0, 2, 3, 1, 1]
    Output: [2, 3, -1, 2, 2]
    Explanation: NGE for 0 is 2, for 2 is 3, for 3 is -1, for 1 at index 3 is 2 (circularly), for 1 at index 4 is 2.

    Constraints:
    1 <= arr.size() <= 10^5
    0 <= arr[i] <= 10^6

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space)

    Approach 1: Brute Force Circular Search (O(N^2) Time, O(1) Space - Striver & Love Babbar)
    Approach 2: Monotonic Decreasing Stack with 2N Traversal (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Brute Force (Approach 1):
       - For each element at index `i`, circularly scan the next `N - 1` elements: `(i + 1) % N`, `(i + 2) % N`...
       - Return the first element strictly greater than `arr[i]`.
       - Time: O(N^2), Space: O(1).

    2. Optimal Monotonic Stack with 2N Traversal (Approach 2):
       - To simulate circularity, imagine traversing a duplicated array of length `2N`.
       - Traverse backwards from index `2N - 1` down to `0`:
         * Current element index is `i % N`.
         * Pop elements from the stack that are `<= arr[i % N]` (they can never be the NGE for preceding elements).
         * When `i < N` (the actual original array range):
           - If stack is not empty, `nge[i] = st.top()`.
           - If stack is empty, `nge[i] = -1`.
         * Push `arr[i % N]` onto the stack.
       - Each element is pushed and popped at most once.
       - Time: O(N), Auxiliary Space: O(N).

    DRY RUN:
    Example: arr = [1, 3, 2, 4], N = 4, 2N = 8
    - i = 7 (idx 3, val 4): st = [4]
    - i = 6 (idx 2, val 2): st = [4, 2]
    - i = 5 (idx 1, val 3): pop 2 -> st = [4, 3]
    - i = 4 (idx 0, val 1): st = [4, 3, 1]
    - i = 3 (idx 3, val 4): pop 1, 3, 4 -> st empty -> nge[3] = -1, push 4 -> st = [4]
    - i = 2 (idx 2, val 2): top is 4 -> nge[2] = 4, push 2 -> st = [4, 2]
    - i = 1 (idx 1, val 3): pop 2, top is 4 -> nge[1] = 4, push 3 -> st = [4, 3]
    - i = 0 (idx 0, val 1): top is 3 -> nge[0] = 3, push 1 -> st = [4, 3, 1]
    - Result: [3, 4, 4, -1].
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// ============================================================================
// Approach 1: Brute Force Circular Search (O(N^2) Time, O(1) Space)
// ============================================================================
class SolutionBruteForce {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> nge(n, -1);

        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                int nextIdx = (i + j) % n;
                if (arr[nextIdx] > arr[i]) {
                    nge[i] = arr[nextIdx];
                    break;
                }
            }
        }

        return nge;
    }
};

// ============================================================================
// Approach 2: Monoptitonic Decreasing Stack with 2N Traversal (Omal O(N) Time, O(N) Space)
// ============================================================================
class SolutionOptimal {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int n = arr.size();
        vector<int> nge(n, -1);
        stack<int> st;

        // Traverse from 2N - 1 down to 0 to handle circularity
        for (int i = 2 * n - 1; i >= 0; i--) {
            int currentVal = arr[i % n];

            // Pop elements smaller than or equal to currentVal
            while (!st.empty() && st.top() <= currentVal) {
                st.pop();
            }

            // Fill answer for actual array indices
            if (i < n) {
                if (!st.empty()) {
                    nge[i] = st.top();
                } else {
                    nge[i] = -1;
                }
            }

            // Push current element for preceding elements
            st.push(currentVal);
        }

        return nge;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        SolutionOptimal solver;
        return solver.nextLargerElement(arr);
    }
};
