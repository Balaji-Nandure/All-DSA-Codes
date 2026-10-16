/**
 * Problem: Maximum Sum of Nodes in Binary Tree such that no two are adjacent (House Robber III)
 * Category: Binary Trees / Dynamic Programming on Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Largest Independent Set Problem" in the DP category, we maximized the COUNT of non-adjacent nodes.
 * - Here, each node carries an arbitrary integer WEIGHT, requiring Tree Dynamic Programming with dual states.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Tree DP with Dual State Pair `{include, exclude}`:
 *   - At each node `curr`, return `std::pair<int, int>`:
 *     - `first`: Maximum sum attainable if `curr` IS included in the subset.
 *     - `second`: Maximum sum attainable if `curr` is EXCLUDED from the subset.
 *   - Transitions:
 *     1. If `curr` is INCLUDED:
 *        - Neither `curr->left` nor `curr->right` can be included!
 *        - `include = curr->data + left.exclude + right.exclude`.
 *     2. If `curr` is EXCLUDED:
 *        - Its children may independently be either included or excluded—whichever yields greater profit!
 *        - `exclude = max(left.include, left.exclude) + max(right.include, right.exclude)`.
 *   - Overall answer = `max(root.include, root.exclude)`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Solved in a single bottom-up post-order pass.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <algorithm>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct Result {
    int include;
    int exclude;
};

Result getMaxSumHelper(Node* root) {
    if (!root) return {0, 0};

    Result left = getMaxSumHelper(root->left);
    Result right = getMaxSumHelper(root->right);

    Result curr;
    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Including current node forbids direct children (forces their exclude state);
    // Excluding current node allows greedily picking the max state of each child.
    curr.include = root->data + left.exclude + right.exclude;
    curr.exclude = std::max(left.include, left.exclude) + std::max(right.include, right.exclude);

    return curr;
}

int getMaxSum(Node* root) {
    Result res = getMaxSumHelper(root);
    return std::max(res.include, res.exclude);
}

int main() {
    //        11
    //       /  \
    //      1    2
    // Optimal: Pick 11 (root) -> sum = 11.
    // Or pick children 1 + 2 = 3.
    // Max = 11.
    Node* root = new Node(11);
    root->left = new Node(1);
    root->right = new Node(2);

    std::cout << "Max sum of non-adjacent nodes: " << getMaxSum(root) << "\n"; // 11

    return 0;
}
