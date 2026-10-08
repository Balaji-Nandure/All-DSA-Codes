/*
    Problem Name: Remove Consecutive Similar Balls
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays `color[]` and `radius[]`, representing a sequence of balls:
    - `color[i]` is the color of the i-th ball.
    - `radius[i]` is the radius of the i-th ball.

    If two consecutive balls have the same color and radius, remove them both.
    Repeat this process until no more such pairs exist.
    Return the number of balls remaining after all possible removals.

    Examples:
    Input: color = [2, 3, 5], radius = [3, 3, 5]
    Output: 3
    Explanation: All 3 balls have different colors and radii. No pair is removed.

    Input: color = [2, 2, 5], radius = [3, 3, 5]
    Output: 1
    Explanation: The 1st and 2nd ball have identical color (2) and radius (3).
                 They cancel each other out and are removed.
                 Only the 3rd ball remains. Length = 1.

    Constraints:
    1 <= color.size(), radius.size() <= 10^5
    1 <= color[i], radius[i] <= 10^9

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space)

    Approach: Stack of Pairs / Vector Simulation (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. This is analogous to the classic "Remove Adjacent Duplicates" problem.
    2. When two consecutive elements match, removing them can cause their previous neighbors
       to become adjacent and potentially match.
    3. A Stack naturally handles recursive adjacent removals:
       - Maintain a stack storing the balls `pair<int, int>` representing `(color, radius)`.
       - For each ball `i` from `0` to `n - 1`:
         * If the stack is not empty and `st.top()` has the SAME color and radius as ball `i`:
           - A consecutive matching pair is formed! Pop `st.top()` (destroy both).
         * Otherwise:
           - Push the current ball `(color[i], radius[i])` onto the stack.
    4. At the end, the number of balls remaining is simply `st.size()`.
    5. Time Complexity: O(N) since each ball is pushed and popped at most once.
    6. Space Complexity: O(N) in the worst case where no balls are removed.

    DRY RUN:
    Example: color = [2, 2, 5], radius = [3, 3, 5]
    - i = 0: ball = (2, 3), st is empty -> push (2, 3) -> st = [(2, 3)]
    - i = 1: ball = (2, 3), st.top() == (2, 3) -> Match! Pop top -> st = []
    - i = 2: ball = (5, 5), st is empty -> push (5, 5) -> st = [(5, 5)]
    - Traversal ends. Return st.size() = 1.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

// ============================================================================
// Approach: Stack of Pairs (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    int findLength(vector<int>& color, vector<int>& radius) {
        int n = color.size();
        stack<pair<int, int>> st;

        for (int i = 0; i < n; i++) {
            // Check if top of stack matches the current ball in both color and radius
            if (!st.empty() && st.top().first == color[i] && st.top().second == radius[i]) {
                st.pop(); // Remove the matching pair
            } else {
                st.push({color[i], radius[i]}); // Keep current ball
            }
        }

        return st.size();
    }
};

// ============================================================================
// Approach 2: Vector used as Stack (O(N) Time, O(N) Space, cache-friendly)
// ============================================================================
class SolutionVectorStack {
public:
    int findLength(vector<int>& color, vector<int>& radius) {
        int n = color.size();
        vector<pair<int, int>> st;

        for (int i = 0; i < n; i++) {
            if (!st.empty() && st.back().first == color[i] && st.back().second == radius[i]) {
                st.pop_back();
            } else {
                st.push_back({color[i], radius[i]});
            }
        }

        return st.size();
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int findLength(vector<int>& color, vector<int>& radius) {
        SolutionStack solver;
        return solver.findLength(color, radius);
    }

    // Overload in case GFG tests with (n, color, radius)
    int findLength(int n, vector<int>& color, vector<int>& radius) {
        return findLength(color, radius);
    }
};
