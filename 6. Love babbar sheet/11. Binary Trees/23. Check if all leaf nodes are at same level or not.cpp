/**
 * Problem: Check if all leaf nodes are at same level or not
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Height of a tree", we found the MAXIMUM depth among all leaves.
 * - Here, we must verify that the depth of ALL leaves is UNANIMOUSLY IDENTICAL.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Single-Pass Depth Consistency Check:
 *   - Maintain a tracker `leafLevel = -1`.
 *   - Traverse tree via DFS (or BFS):
 *     - If current node is a leaf:
 *       - If `leafLevel == -1` (first leaf encountered), record `leafLevel = currentLevel`.
 *       - Otherwise, compare `currentLevel == leafLevel`. If unequal, return false immediately!
 *     - Recurse on left and right children with `currentLevel + 1`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses each node at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool checkUtil(Node* root, int level, int& leafLevel) {
    if (!root) return true;

    // Check if current node is a leaf
    if (!root->left && !root->right) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Set expected level upon visiting the first leaf; any subsequent leaf must match it exactly.
        if (leafLevel == -1) {
            leafLevel = level;
            return true;
        }
        return (level == leafLevel);
    }

    // Must hold true for both subtrees
    return checkUtil(root->left, level + 1, leafLevel) &&
           checkUtil(root->right, level + 1, leafLevel);
}

bool checkLeavesAtSameLevel(Node* root) {
    int leafLevel = -1;
    return checkUtil(root, 0, leafLevel);
}

int main() {
    // All leaves at level 2:
    //       12
    //      /  \
    //     5    7
    //    /      \
    //   3        1
    Node* root1 = new Node(12);
    root1->left = new Node(5);
    root1->right = new Node(7);
    root1->left->left = new Node(3);
    root1->right->right = new Node(1);

    std::cout << "Tree 1 leaves at same level: " 
              << (checkLeavesAtSameLevel(root1) ? "Yes" : "No") << "\n"; // Yes

    // Leaf at level 1 and level 2:
    Node* root2 = new Node(12);
    root2->left = new Node(5);
    root2->right = new Node(7);
    root2->left->left = new Node(3); // Leaves are 3 (level 2) and 7 (level 1)

    std::cout << "Tree 2 leaves at same level: " 
              << (checkLeavesAtSameLevel(root2) ? "Yes" : "No") << "\n"; // No

    return 0;
}
