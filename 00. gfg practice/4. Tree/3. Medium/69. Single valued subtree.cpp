/*
    Problem Name: Single valued subtree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, count the number of Single Valued Subtrees.
    A Single Valued Subtree is a subtree in which all nodes have the exact same data value.

    Examples:
    Input:
               5
             /   \
            1     5
           / \     \
          5   5     5

    Output: 4
    Explanation: The 4 single valued subtrees are:
    - 3 leaf nodes (5, 5, 5)
    - The right subtree rooted at 5 (with right child 5)

    Input:
               5
             /   \
            4     5
           / \     \
          4   4     5

    Output: 5
    Explanation: The 5 single valued subtrees are:
    - 3 leaf nodes (4, 4, 5)
    - Subtree rooted at 4 (with children 4, 4)
    - Subtree rooted at right child 5 (with right child 5)

    Constraints:
    1 <= n <= 10^5
    1 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Bottom-up postorder DFS visits each node once.
    Space Complexity: O(H), where H is the height of the tree for recursion call stack.

    Love Babbar Style Approach:
    Bottom-Up Postorder DFS (Boolean Validity Propagation):

    1. INTUITION:
       - A subtree rooted at node `root` is a Single Valued Subtree if and only if:
         1. Its left subtree is single-valued (`leftSingle == true`).
         2. Its right subtree is single-valued (`rightSingle == true`).
         3. If `root->left` exists, `root->left->data == root->data`.
         4. If `root->right` exists, `root->right->data == root->data`.
       - Using a bottom-up Postorder traversal (Left -> Right -> Root):
         * Check if left child forms a valid single-valued subtree.
         * Check if right child forms a valid single-valued subtree.
         * If both are valid and child node values match `root->data`, then `root` ALSO forms a single-valued subtree!
         * Increment `count++` and return `true` to parent node.
       - Pass `count` by reference (`int& count`) to avoid global or class-level state variables.

    2. ALGORITHM:
       - `isSingleValued(root, count)`:
         * Base Case: `if (root == NULL) return true;`
         * `bool leftSingle = isSingleValued(root->left, count);`
         * `bool rightSingle = isSingleValued(root->right, count);`
         * `if (!leftSingle || !rightSingle) return false;`
         * `if (root->left && root->left->data != root->data) return false;`
         * `if (root->right && root->right->data != root->data) return false;`
         * `count++;`
         * Return `true`.

    Dry Run:
               5
             /   \
            1     5
           / \     \
          5   5     5

    - leaf1(5): returns true, count = 1
    - leaf2(5): returns true, count = 2
    - node 1: left=5, right=5, root=1 (1 != 5) -> returns false. count = 2
    - leaf3(5): returns true, count = 3
    - node 5 (right child): right=5 -> returns true, count = 4
    - node 5 (root): left is not single-valued -> returns false.

    Result: 4 ✓
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
private:
    // Helper function to check if subtree is single-valued and count valid subtrees
    bool isSingleValued(Node* root, int& count) {
        if (root == NULL) return true;

        // Postorder DFS: check left and right subtrees
        bool leftSingle = isSingleValued(root->left, count);
        bool rightSingle = isSingleValued(root->right, count);

        // If either child's subtree is not single-valued, current subtree cannot be single-valued
        if (!leftSingle || !rightSingle) {
            return false;
        }

        // If left child exists and its data does not match root, invalid
        if (root->left && root->left->data != root->data) {
            return false;
        }

        // If right child exists and its data does not match root, invalid
        if (root->right && root->right->data != root->data) {
            return false;
        }

        // Current subtree is single-valued
        count++;
        return true;
    }

public:
    // GFG Signature
    int singlevalued(Node* root) {
        int count = 0;
        isSingleValued(root, count);
        return count;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            5
    //          /   \
    //         1     5
    //        / \     \
    //       5   5     5
    // Expected Output: 4
    Node* root1 = new Node(5);
    root1->left = new Node(1);
    root1->right = new Node(5);
    root1->left->left = new Node(5);
    root1->left->right = new Node(5);
    root1->right->right = new Node(5);

    cout << "Example 1 Single Valued Subtrees Count: " << ob.singlevalued(root1) << "\n";

    // Example 2:
    //            5
    //          /   \
    //         4     5
    //        / \     \
    //       4   4     5
    // Expected Output: 5
    Node* root2 = new Node(5);
    root2->left = new Node(4);
    root2->right = new Node(5);
    root2->left->left = new Node(4);
    root2->left->right = new Node(4);
    root2->right->right = new Node(5);

    cout << "Example 2 Single Valued Subtrees Count: " << ob.singlevalued(root2) << "\n";

    return 0;
}
