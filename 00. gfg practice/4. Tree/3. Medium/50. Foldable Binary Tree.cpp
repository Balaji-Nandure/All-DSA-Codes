/*
    Problem Name: Foldable Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    A binary tree is said to be foldable if its left and right subtrees are mirror images of each
    other in terms of structure only (values stored in the nodes are not considered).
    Given the root of a binary tree, check if the tree is foldable.
    Note: An empty tree is considered foldable.

    Examples:
    Input: root = [10, 7, 15, N, 9, 11, N]
    Output: true
    Explanation:
            10
           /  \
          7    15
           \   /
            9 11
    - Node 7 has right child 9 (left is NULL).
    - Node 15 has left child 11 (right is NULL).
    The left and right subtrees are structural mirror images of each other -> Foldable!

    Input: root = [10, 7, 15, 5, N, 11, N]
    Output: false
    Explanation:
            10
           /  \
          7    15
         /    /
        5    11
    - Node 7 has left child 5. Node 15 has left child 11.
    - Not structural mirror images (7's left should match 15's right) -> Not foldable!

    Constraints:
    0 <= n <= 10^5
    1 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. DFS visits each pair of nodes once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Structural Mirror Recursion:

    1. INTUITION:
       - A tree is foldable if its left child `root->left` and right child `root->right` are
         STRUCTURAL MIRRORS of each other.
       - Two subtrees `a` and `b` are structural mirrors if:
         1. Both `a` and `b` are NULL -> return `true`.
         2. One of `a` or `b` is NULL while the other is NOT -> return `false` (structure mismatch!).
         3. Recursively check:
            - `a->left` matches `b->right` (outer subtrees)
            - AND `a->right` matches `b->left` (inner subtrees)

    2. ALGORITHM:
       - `mirror(a, b)`:
         * `if (!a && !b) return true;`
         * `if (!a || !b) return false;`
         * `return mirror(a->left, b->right) && mirror(a->right, b->left);`
       - `IsFoldable(root)`:
         * `if (!root) return true;`
         * `return mirror(root->left, root->right);`

    Dry Run:
            10
           /  \
          7    15
           \   /
            9 11

    - IsFoldable(10) -> mirror(7, 15)
      - mirror(7->left (NULL), 15->right (NULL)) -> returns true
      - mirror(7->right (9), 15->left (11))
        - mirror(9->left (NULL), 11->right (NULL)) -> true
        - mirror(9->right (NULL), 11->left (NULL)) -> true
        - returns true
      - returns true && true = true.

    Output: true ✓
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
    // Helper function to check if subtrees a and b are structural mirror images
    bool mirror(Node* a, Node* b) {
        // Both nodes are NULL -> structurally identical
        if (!a && !b) return true;

        // One node is NULL while the other is not -> structural mismatch
        if (!a || !b) return false;

        // Check if a's left matches b's right AND a's right matches b's left
        return mirror(a->left, b->right) &&
               mirror(a->right, b->left);
    }

public:
    // GFG Signature
    bool IsFoldable(Node* root) {
        if (!root) return true;

        return mirror(root->left, root->right);
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            10
    //           /  \
    //          7    15
    //           \   /
    //            9 11
    // Expected Output: true
    Node* root1 = new Node(10);
    root1->left = new Node(7);
    root1->right = new Node(15);
    root1->left->right = new Node(9);
    root1->right->left = new Node(11);

    cout << "Example 1 IsFoldable: " << (ob.IsFoldable(root1) ? "true" : "false") << "\n";

    // Example 2:
    //            10
    //           /  \
    //          7    15
    //         /    /
    //        5    11
    // Expected Output: false
    Node* root2 = new Node(10);
    root2->left = new Node(7);
    root2->right = new Node(15);
    root2->left->left = new Node(5);
    root2->right->left = new Node(11);

    cout << "Example 2 IsFoldable: " << (ob.IsFoldable(root2) ? "true" : "false") << "\n";

    return 0;
}
