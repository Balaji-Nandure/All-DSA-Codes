/*
    Problem Name: Delete Nodes Greater than K
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a Binary Search Tree (BST) and an integer k, delete all nodes whose values
    are greater than or equal to k and return the root of the modified BST.

    Examples:
    Input: root[] = [4, 1, 9], k = 2
    Output: [1]
    Explanation: Nodes 4 and 9 are >= 2, so they are deleted. Only 1 remains.

    Input: root[] = [8, 3, 10, 1, 6, 9, 12], k = 10
    Output: [1, 3, 6, 8, 9] (Inorder of remaining BST)
    Explanation: Nodes 10 and 12 are >= 10, so they are deleted.
    Remaining nodes: 1, 3, 6, 8, 9.

    Constraints:
    1 <= root.size() <= 10^3
    1 <= root[i] <= 10^3
    1 <= k <= 10^3

    Expected Complexities:
    Time Complexity: O(H), where H is height of BST. We only traverse paths necessary for pruning.
    Space Complexity: O(H), for recursion call stack.

    Love Babbar Style Approach:
    BST Property Pruning (Recursive Pruning):

    1. INTUITION:
       - Leveraging the Binary Search Tree property (left < root < right):
         * Case 1: `root->data >= k`
           - Since all nodes in `root->right` are even larger (`>= root->data >= k`), `root` AND its
             entire right subtree MUST BE DELETED!
           - Nodes smaller than `k` can ONLY exist in `root->left`.
           - Therefore, we discard `root` and return `deleteNode(root->left, k)` directly to the parent.
         * Case 2: `root->data < k`
           - `root` and its entire left subtree (`root->left`) are strictly `< k`, so they are KEPT.
           - Nodes `>= k` can ONLY exist in `root->right`.
           - Therefore, we update `root->right = deleteNode(root->right, k)` and return `root`.

    2. ALGORITHM:
       - `deleteNode(root, k)`:
         * Base Case: `if (root == NULL) return NULL;`
         * `if (root->data >= k)`:
           - Return `deleteNode(root->left, k);`
         * `else`:
           - `root->right = deleteNode(root->right, k);`
           - Return `root;`

    Dry Run:
            8
          /   \
         3     10
        / \   /  \
       1   6 9   12
    k = 10

    - deleteNode(8, 10): 8 < 10 -> 8->right = deleteNode(10, 10). Return 8.
    - deleteNode(10, 10): 10 >= 10 -> prune 10 & 12! Return deleteNode(9, 10).
    - deleteNode(9, 10): 9 < 10 -> 9->right = deleteNode(NULL, 10). Return 9.

    Reconnected: 8->right = 9.
    Resulting BST Inorder: 1 3 6 8 9 ✓
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    // GFG Signature
    Node* deleteNode(Node* root, int k) {
        if (root == NULL) return NULL;

        // If root data >= k, prune root and its right subtree, search left subtree
        if (root->data >= k) {
            return deleteNode(root->left, k);
        }

        // If root data < k, root and left subtree are safe, filter right subtree
        root->right = deleteNode(root->right, k);
        return root;
    }
};

// Helper function to print Inorder traversal of BST
void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    Solution ob;

    // Example 1:
    //      4
    //     / \
    //    1   9
    // k = 2  --> Expected Output: 1
    Node* root1 = new Node(4);
    root1->left = new Node(1);
    root1->right = new Node(9);

    root1 = ob.deleteNode(root1, 2);
    cout << "Example 1 Modified BST Inorder: ";
    printInorder(root1);
    cout << "\n";

    // Example 2:
    //            8
    //          /   \
    //         3     10
    //        / \   /  \
    //       1   6 9   12
    // k = 10  --> Expected Output: 1 3 6 8 9
    Node* root2 = new Node(8);
    root2->left = new Node(3);
    root2->right = new Node(10);
    root2->left->left = new Node(1);
    root2->left->right = new Node(6);
    root2->right->left = new Node(9);
    root2->right->right = new Node(12);

    root2 = ob.deleteNode(root2, 10);
    cout << "Example 2 Modified BST Inorder: ";
    printInorder(root2);
    cout << "\n";

    return 0;
}
