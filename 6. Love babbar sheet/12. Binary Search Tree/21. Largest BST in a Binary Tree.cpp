/**
 * Problem: Largest BST in a Binary Tree
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - "Check if a tree is a BST" only returned a true/false flag for the ENTIRE tree.
 * - Here, the global tree might NOT be a BST, but contains embedded valid BST subtrees.
 * - We must find the MAXIMUM SIZE (number of nodes) among all valid BST subtrees in strictly O(N) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bottom-Up Post-Order Struct Return:
 *   - At each node, return a struct `Info`:
 *     - `isBST`: Boolean indicating if subtree rooted here is a valid BST.
 *     - `size`: Size of largest BST in this subtree.
 *     - `minVal`: Minimum value in this subtree.
 *     - `maxVal`: Maximum value in this subtree.
 *   - Base Case (null): `{isBST = true, size = 0, minVal = +INF, maxVal = -INF}`.
 *   - Current node is a valid BST IF AND ONLY IF:
 *     `left.isBST && right.isBST && root->data > left.maxVal && root->data < right.minVal`.
 *   - If valid:
 *     - `size = 1 + left.size + right.size`.
 *     - `minVal = min(root->data, left.minVal)`.
 *     - `maxVal = max(root->data, right.maxVal)`.
 *   - If NOT valid:
 *     - `isBST = false`.
 *     - `size = max(left.size, right.size)` (propagate the best size found in either branch).
 * 
 * TIME COMPLEXITY:
 * - O(N): Evaluates each node in a single bottom-up post-order pass.
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth bounded by tree height.
 */

#include <iostream>
#include <algorithm>
#include <climits>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

struct Info {
    bool isBST;
    int size;
    int minVal;
    int maxVal;
};

Info largestBSTUtil(Node* root) {
    // Base Case
    if (!root) {
        return {true, 0, INT_MAX, INT_MIN};
    }

    Info left = largestBSTUtil(root->left);
    Info right = largestBSTUtil(root->right);

    Info curr;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Valid BST requires left and right to be BSTs, root > maximum of left, and root < minimum of right.
    if (left.isBST && right.isBST && root->data > left.maxVal && root->data < right.minVal) {
        curr.isBST = true;
        curr.size = 1 + left.size + right.size;
        curr.minVal = std::min(root->data, left.minVal);
        curr.maxVal = std::max(root->data, right.maxVal);
    } else {
        curr.isBST = false;
        curr.size = std::max(left.size, right.size);
        curr.minVal = INT_MIN;
        curr.maxVal = INT_MAX;
    }

    return curr;
}

int largestBst(Node* root) {
    return largestBSTUtil(root).size;
}

int main() {
    // Binary Tree:
    //          50
    //        /    \
    //       30     60
    //      /  \   /  \
    //     5   20 45  70
    //               /  \
    //              65  80
    // Subtree 60->45, 70 is NOT BST (45 < 50 is fine, but 45 < 60 is right subtree).
    // Subtree 70->65, 80 is a valid BST of size 3.
    // Subtree 30->5, 20 is NOT BST (20 < 30 on right!).
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(60);
    root->left->left = new Node(5);
    root->left->right = new Node(20);
    root->right->left = new Node(45);
    root->right->right = new Node(70);
    root->right->right->left = new Node(65);
    root->right->right->right = new Node(80);

    std::cout << "Size of largest BST: " << largestBst(root) << "\n"; // 4 (subtrees rooted at 60->... or 5)

    return 0;
}
