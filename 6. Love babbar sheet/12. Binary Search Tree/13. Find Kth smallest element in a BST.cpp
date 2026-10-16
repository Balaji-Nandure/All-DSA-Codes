/**
 * Problem: Find Kth Smallest Element in a BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find Kth largest element in a BST", we used reverse inorder (Right -> Root -> Left).
 * - Here, we perform the exact symmetric dual: using standard forward Inorder (Left -> Root -> Right)
 *   to encounter elements in strictly ASCENDING order.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Forward Inorder Traversal with Early Termination:
 *   - The Inorder traversal of any BST visits nodes in strictly increasing sorted order.
 *   - Drill down to the minimum element (leftmost).
 *   - Count each visited node:
 *     - When `count == K`, the current node's value is unconditionally the Kth smallest element.
 *     - Record `ans = root->data` and short-circuit any further recursive exploration.
 * 
 * TIME COMPLEXITY:
 * - O(H + K): Traverses to leftmost node (O(H)), then traverses K nodes.
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

void kthSmallestUtil(Node* root, int k, int& count, int& ans) {
    if (!root || count >= k) return;

    // Recurse left (smaller elements)
    kthSmallestUtil(root->left, k, count, ans);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // In forward inorder, the Kth node visited is precisely the Kth smallest element in the BST!
    count++;
    if (count == k) {
        ans = root->data;
        return;
    }

    // Recurse right (larger elements)
    kthSmallestUtil(root->right, k, count, ans);
}

int kthSmallest(Node* root, int k) {
    int count = 0;
    int ans = -1;
    kthSmallestUtil(root, k, count, ans);
    return ans;
}

int main() {
    //        4
    //       / \
    //      2   9
    //     / \
    //    1   3
    // Ascending order: 1, 2, 3, 4, 9
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(9);
    root->left->left = new Node(1);
    root->left->right = new Node(3);

    std::cout << "1st smallest: " << kthSmallest(root, 1) << "\n"; // 1
    std::cout << "3rd smallest: " << kthSmallest(root, 3) << "\n"; // 3
    std::cout << "5th smallest: " << kthSmallest(root, 5) << "\n"; // 9

    return 0;
}
