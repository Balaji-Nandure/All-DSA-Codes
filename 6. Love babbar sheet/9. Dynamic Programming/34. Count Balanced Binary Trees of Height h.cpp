#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Count Balanced Binary Trees of Height h (BBT Counter)
 * 
 * Given a height h, find the total count of structurally balanced binary trees of height h.
 * A binary tree is balanced if at every node, the height difference between its left 
 * and right subtrees is at most 1: |height(left) - height(right)| <= 1.
 * Return the result modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "5. Catalan Number", we counted BSTs with N nodes (BST search property).
 * - Here, we count structurally BALANCED binary trees with a FIXED HEIGHT h (AVL property).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Linear Dynamic Programming with Height Invariants:
 *   For a tree to have exact height h:
 *   The root node is at level 1.
 *   At least one of its subtrees MUST have height (h - 1).
 *   By the balance condition |h(left) - h(right)| <= 1, the other subtree can only have 
 *   height either (h - 1) or (h - 2).
 *   
 *   Three mutually exclusive structural configurations:
 *   1. Both subtrees have height (h - 1):
 *      Ways = dp[h - 1] * dp[h - 1]
 *   
 *   2. Left subtree has height (h - 1) and Right subtree has height (h - 2):
 *      Ways = dp[h - 1] * dp[h - 2]
 *   
 *   3. Left subtree has height (h - 2) and Right subtree has height (h - 1):
 *      Ways = dp[h - 2] * dp[h - 1]
 *   
 *   Recurrence Relation:
 *     dp[h] = dp[h - 1] * dp[h - 1] + 2 * dp[h - 1] * dp[h - 2]
 *           = dp[h - 1] * (dp[h - 1] + 2 * dp[h - 2])  (modulo 10^9 + 7)
 *   
 *   Base Cases:
 *     dp[0] = 1 (empty tree, height 0)
 *     dp[1] = 1 (single node tree, height 1)
 *   
 *   Space Optimization:
 *     Because dp[h] depends only on the previous two heights (h - 1 and h - 2),
 *     we can maintain two rolling variables for strictly O(1) space!
 */

class Solution {
    const int MOD = 1e9 + 7;
public:
    long long int countBT(int h) {
        if (h == 0 || h == 1) return 1;

        long long prev2 = 1; // dp[0]
        long long prev1 = 1; // dp[1]
        long long curr = 0;

        for (int i = 2; i <= h; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // dp[i] = dp[i-1] * (dp[i-1] + 2 * dp[i-2]) % MOD
            long long term1 = (prev1 * prev1) % MOD;
            long long term2 = (2LL * prev1 * prev2) % MOD;
            curr = (term1 + term2) % MOD;

            // Rolling state update
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

int main() {
    Solution sol;
    cout << "BBTs of height 1: " << sol.countBT(1) << "\n"; // Expected: 1
    cout << "BBTs of height 2: " << sol.countBT(2) << "\n"; // Expected: 3 (1*1 + 2*1*1 = 3)
    cout << "BBTs of height 3: " << sol.countBT(3) << "\n"; // Expected: 15 (3*3 + 2*3*1 = 9 + 6 = 15)
    cout << "BBTs of height 4: " << sol.countBT(4) << "\n"; // Expected: 315

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(H) single linear loop up to height H.
 * - Space Complexity: O(1) auxiliary space using rolling variables.
 */
