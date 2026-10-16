/**
 * Problem: Lowest Common Ancestor (LCA) in a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems looked for ancestors sequentially upwards from a single leaf.
 * - LCA identifies the DEEPEST shared junction point where two distinct nodes n1 and n2 diverge into separate subtrees.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order Convergence:
 *   - Base Cases:
 *     - If `root == nullptr`, return nullptr.
 *     - If `root->data == n1 || root->data == n2`: Return `root` (found one of the targets).
 *   - Recursive Step:
 *     - Explore both left and right subtrees:
 *       `leftLCA = lca(root->left, n1, n2)`
 *       `rightLCA = lca(root->right, n1, n2)`
 *   - Resolution:
 *     - If BOTH `leftLCA` and `rightLCA` return non-null, `n1` lies in one subtree and `n2` lies in the other;
 *       therefore, `root` is strictly their Lowest Common Ancestor!
 *     - If only one subtree returns non-null, propagate that non-null ancestor upwards.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses the tree once.
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

Node* lca(Node* root, int n1, int n2) {
    // Base Case
    if (!root) return nullptr;

    // If current node matches either n1 or n2, return it
    if (root->data == n1 || root->data == n2) {
        return root;
    }

    // Look for keys in left and right subtrees
    Node* leftLCA = lca(root->left, n1, n2);
    Node* rightLCA = lca(root->right, n1, n2);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // If one target lies in left subtree and other in right subtree, current node is the Lowest Common Ancestor!
    if (leftLCA && rightLCA) {
        return root;
    }

    // Otherwise return whichever subtree found a target node
    return leftLCA ? leftLCA : rightLCA;
}

int main() {
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    Node* ans = lca(root, 4, 5);
    std::cout << "LCA of 4 and 5: " << (ans ? ans->data : -1) << "\n"; // 2

    ans = lca(root, 4, 3);
    std::cout << "LCA of 4 and 3: " << (ans ? ans->data : -1) << "\n"; // 1

    return 0;
}
