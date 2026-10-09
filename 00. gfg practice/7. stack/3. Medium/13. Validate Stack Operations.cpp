/*
    Problem Name: Validate Stack Operations
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 946 (Validate Stack Sequences)

    Problem Statement:
    You have an empty stack and can perform push and pop operations in it.
    Given two arrays `a[]` and `b[]` of unique elements and both having the same length:
    - `a[]` represents the order in which elements are pushed into a stack.
    - `b[]` represents the order in which elements are expected to be popped from the stack.
    Determine whether the given push and pop sequences are valid.

    Note:
    - The stack is empty initially and must also be empty after performing all the operations.

    Examples:
    Input: a = [1, 2, 3], b = [2, 1, 3]
    Output: true
    Explanation:
    - Push 1: stack = [1]
    - Push 2: stack = [1, 2]
    - Pop 2 (matches b[0]): stack = [1]
    - Pop 1 (matches b[1]): stack = []
    - Push 3: stack = [3]
    - Pop 3 (matches b[2]): stack = []
    All elements pushed and popped properly, stack is empty. Result is true.

    Input: a = [1, 2, 3], b = [3, 1, 2]
    Output: false
    Explanation:
    - Push 1, 2, 3: stack = [1, 2, 3]
    - Pop 3 (matches b[0]): stack = [1, 2]
    - Next expected in b is 1, but top is 2. Cannot pop 1 because it's blocked by 2.
    Result is false.

    Constraints:
    1 <= a.size() <= 10^5
    0 <= a[i], b[i] <= 2 * 10^5
    b.size() == a.size()

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space)

    Approach: Greedy Stack Simulation (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. We can simulate the exact pushing and popping process using a real stack.
    2. Maintain an index pointer `j = 0` for array `b` (the expected pop sequence).
    3. For each element `x` in `a`:
       - Push `x` onto the stack.
       - While the stack is not empty and the top of the stack matches `b[j]`:
         * Pop the element from the stack (`st.pop()`).
         * Advance the pop pointer (`j++`).
         * If `j == b.size()`, stop popping.
    4. At the end:
       - If all elements in `b` were matched (`j == b.size()` or equivalently `st.empty()`),
         the sequence is valid (return `true`).
       - Otherwise, return `false`.
    5. Each element is pushed onto the stack exactly once and popped at most once:
       Total Time Complexity is strictly O(N).

    DRY RUN:
    Example: a = [1, 2, 3], b = [2, 1, 3]
    - x = 1: push(1) -> st = [1]. st.top() (1) != b[0] (2).
    - x = 2: push(2) -> st = [1, 2].
      * st.top() (2) == b[0] (2) -> pop(), j = 1, st = [1]
      * st.top() (1) == b[1] (1) -> pop(), j = 2, st = []
    - x = 3: push(3) -> st = [3].
      * st.top() (3) == b[2] (3) -> pop(), j = 3, st = []
    - End of loop: j = 3 == b.size() (3). Return true.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// ============================================================================
// Approach: Greedy Stack Simulation (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    bool validateStackSequences(vector<int>& a, vector<int>& b) {
        stack<int> st;
        int j = 0;

        for (int x : a) {
            st.push(x);

            // Greedily pop matching elements
            while (!st.empty() && j < b.size() && st.top() == b[j]) {
                st.pop();
                j++;

                if (j == b.size()) {
                    break;
                }
            }
        }

        return j == b.size();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    bool validateStackSequences(vector<int>& a, vector<int>& b) {
        SolutionStack solver;
        return solver.validateStackSequences(a, b);
    }

    // Alias in case problem uses validateStackOperations
    bool validateStackOperations(vector<int>& a, vector<int>& b) {
        return validateStackSequences(a, b);
    }
};
