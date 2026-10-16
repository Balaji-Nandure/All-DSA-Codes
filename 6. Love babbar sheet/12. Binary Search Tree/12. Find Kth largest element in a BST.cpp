/**
 * Problem: Find Kth Largest Element in a BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find Kth max and min element of an array", we used quickselect or max/min heaps.
 * - In a BST, the total ordering allows visiting elements in strictly DESCENDING order
 *   by simply traversing in REVERSE Inorder (Right -> Root -> Left), stopping the instant
 *   the Kth element is reached.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Reverse Inorder Traversal with Early Exit:
 *   - Normal Inorder: Left -> Root -> Right yields ASCENDING order (1st = smallest).
 *   - Reverse Inorder: Right -> Root -> Left yields DESCENDING order (1st = largest).
 *   - By traversing Right -> Root -> Left:
 *     - Count each node visited.
 *     - When `count == K`, the current node is the exact Kth largest element!
 *     - Store result and immediately terminate remaining recursion branches.
 * 
 * TIME COMPLEXITY:
 * - O(H + K): Traverses down to the largest element (O(H)), then visits K nodes.
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

void kthLargestUtil(Node* root, int k, int& count, int& ans) {
    if (!root || count >= k) return;

    // Recurse on right subtree first (larger elements)
    kthLargestUtil(root->right, k, count, ans);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // In reverse inorder, the Kth node visited is precisely the Kth largest element in the tree!
    count++;
    if (count == k) {
        ans = root->data;
        return;
    }

    // Recurse on left subtree (smaller elements)
    kthLargestUtil(root->left, k, count, ans);
}

int kthLargest(Node* root, int k) {
    int count = 0;
    int ans = -1;
    kthLargestUtil(root, k, count, ans);
    return ans;
}

int main() {
    //        4
    //       / \
    //      2   9
    //         / \
    //        7  10
    // Descending order: 10, 9, 7, 4, 2
    Node* root = new Node(4);
    root->left = new Node(2);
    root->right = new Node(9);
    root->right->left = new Node(7);
    root->right->right = new Node(10);

    std::cout << "1st largest: " << kthLargest(root, 1) << "\n"; // 10
    std::cout << "3rd largest: " << kthLargest(root, 3) << "\n"; // 7
    std::cout << "5th largest: " << kthLargest(root, 5) << "\n"; // 2

    return 0;
}
