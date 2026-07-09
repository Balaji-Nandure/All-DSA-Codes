/*
    Problem Name: LCA in Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree with all unique values and two node values n1 and n2,
    find the Lowest Common Ancestor (LCA) of the two given nodes.
    Both node values are ALWAYS present in the Binary Tree.
    Note: LCA is the FIRST common ancestor of both nodes from the BOTTOM of the tree.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node at most once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.
                      In the worst case (skewed tree), H = N, so O(N).

    Love Babbar Style Approach:
    1. The KEY insight: we do a single recursive DFS and let the answers "bubble up" from below!
    2. Base Case #1: If root is NULL, return NULL — we've fallen off the tree, nothing found here.
    3. Base Case #2: If root->data == n1 OR root->data == n2, return root itself!
       WHY? Because we found one of our targets. Even if the other one is deeper in its subtree,
       THIS node is guaranteed to be the LCA (since both nodes are always present in the tree).
    4. Recurse into BOTH left and right subtrees to search for n1 and n2.
    5. MAGIC STEP — Check the results:
       - If BOTH left and right return non-NULL  --> n1 is on one side, n2 is on the other.
                                                    The CURRENT ROOT is the LCA! Return root.
       - If only LEFT is non-NULL                --> Both nodes live in the left subtree.
                                                    Return left (it's carrying the LCA up).
       - If only RIGHT is non-NULL               --> Both nodes live in the right subtree.
                                                    Return right (it's carrying the LCA up).
       - If BOTH are NULL                        --> Neither node found here. Return NULL.

    Dry Run:
    Tree:       1
               / \
              2   3
             / \ / \
            4  5 6  7
    n1 = 4, n2 = 5

    - lca(1, 4, 5)
        - left  = lca(2, 4, 5)
            - left  = lca(4, 4, 5) --> root->data == 4 --> return Node(4)
            - right = lca(5, 4, 5) --> root->data == 5 --> return Node(5)
            - Both left AND right are non-NULL --> Current root IS the LCA!
            - return Node(2)  <-- LCA bubbles up here!
        - right = lca(3, 4, 5)
            - left  = lca(6, 4, 5) --> NULL
            - right = lca(7, 4, 5) --> NULL
            - Both NULL --> return NULL
        - left=Node(2), right=NULL --> only left is non-NULL, return Node(2)
    - Final Answer: 2 ✓

    Example 2:
    Tree:       1
               / \
              2   3
             / \ / \
            4  5 6  7
                 \
                  8
    n1 = 7, n2 = 8

    - lca(3, 7, 8)
        - left  = lca(6, 7, 8)
            - left  = lca(8, 7, 8) --> root->data == 8 --> return Node(8)
            - Both children of 6 are NULL except the left which returned Node(8)
            - return Node(8)
        - right = lca(7, 7, 8) --> root->data == 7 --> return Node(7)
        - Both left=Node(8) AND right=Node(7) are non-NULL --> Current root IS the LCA!
        - return Node(3)
    - Final Answer: 3 ✓
*/

#include <iostream>
#include <vector>

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
    Node* lca(Node* root, int n1, int n2) {
        // Base Case #1: Fell off the tree — nothing found in this path
        if (root == NULL) {
            return NULL;
        }

        // Base Case #2: Found one of our targets! Return this node itself.
        // The other target (if it exists) MUST be somewhere in this node's subtree,
        // so this node is guaranteed to be the LCA.
        if (root->data == n1 || root->data == n2) {
            return root;
        }

        // 1. Recurse into both left and right subtrees to hunt for n1 and n2
        Node* leftResult  = lca(root->left,  n1, n2);
        Node* rightResult = lca(root->right, n1, n2);

        // 2. MAGIC CHECK: Both sides returned something non-NULL!
        //    This means n1 is on one side and n2 is on the other.
        //    The current root is the SPLIT POINT — it IS the LCA!
        if (leftResult != NULL && rightResult != NULL) {
            return root;
        }

        // 3. Only one side found something — both nodes live on that same side.
        //    Pass the answer (the LCA we already found) upward.
        return (leftResult != NULL) ? leftResult : rightResult;
    }
};

// Helper function to insert nodes level-order (for quick tree building in tests)
// Using a simple manual build for the examples below.

int main() {
    // Example 1:
    //         1
    //        / \
    //       2   3
    //      / \ / \
    //     4  5 6  7
    // n1 = 4, n2 = 5  --> Expected LCA: 2

    Node* root1 = new Node(1);
    root1->left          = new Node(2);
    root1->right         = new Node(3);
    root1->left->left    = new Node(4);
    root1->left->right   = new Node(5);
    root1->right->left   = new Node(6);
    root1->right->right  = new Node(7);

    Solution ob;
    Node* ans1 = ob.lca(root1, 4, 5);
    // Output: 2
    cout << "LCA(4, 5) = " << ans1->data << "\n";

    // Example 2:
    //         1
    //        / \
    //       2   3
    //      / \ / \
    //     4  5 6  7
    //         \
    //          8
    // n1 = 7, n2 = 8  --> Expected LCA: 3

    Node* root2 = new Node(1);
    root2->left              = new Node(2);
    root2->right             = new Node(3);
    root2->left->left        = new Node(4);
    root2->left->right       = new Node(5);
    root2->right->left       = new Node(6);
    root2->right->right      = new Node(7);
    root2->right->left->left = new Node(8);

    Node* ans2 = ob.lca(root2, 7, 8);
    // Output: 3
    cout << "LCA(7, 8) = " << ans2->data << "\n";

    return 0;
}
