/**
 * Problem: Count BST nodes that lie in a given range [low, high]
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A standard tree count inspects every node regardless of values (O(N)).
 * - Here, we exploit BST branching to aggressively PRUNE entire subtrees that fall completely outside
 *   the `[low, high]` interval, running proportional only to the nodes inside the range plus the tree height.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Pruned BST Search:
 *   - Base Case: Null node returns 0.
 *   - Case 1: `root->data` is within `[low, high]`:
 *     - Count 1 for current node.
 *     - Both left and right subtrees may contain valid nodes:
 *       `1 + getCount(root->left) + getCount(root->right)`.
 *   - Case 2: `root->data < low`:
 *     - Current node is too small. Moreover, by BST invariant, EVERY node in its left subtree is even smaller!
 *     - Prune left subtree completely; recurse ONLY on `root->right`.
 *   - Case 3: `root->data > high`:
 *     - Current node is too large. By BST invariant, EVERY node in its right subtree is even larger!
 *     - Prune right subtree completely; recurse ONLY on `root->left`.
 * 
 * TIME COMPLEXITY:
 * - O(H + K): Where H is tree height and K is the number of nodes lying in the range.
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

int getCount(Node* root, int l, int h) {
    if (!root) return 0;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Prune left subtree if root < l; prune right subtree if root > h; recurse both only when in range.
    if (root->data >= l && root->data <= h) {
        return 1 + getCount(root->left, l, h) + getCount(root->right, l, h);
    } else if (root->data < l) {
        return getCount(root->right, l, h); // Left is guaranteed < l
    } else {
        return getCount(root->left, l, h);  // Right is guaranteed > h
    }
}

int main() {
    //          10
    //        /    \
    //       5      50
    //      /      /  \
    //     1      40  100
    // Range [5, 45]: nodes 5, 10, 40 -> Count = 3
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(50);
    root->left->left = new Node(1);
    root->right->left = new Node(40);
    root->right->right = new Node(100);

    int l = 5, h = 45;
    std::cout << "Count of nodes in [" << l << ", " << h << "]: " 
              << getCount(root, l, h) << "\n"; // 3

    return 0;
}
