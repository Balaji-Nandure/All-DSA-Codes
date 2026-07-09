/*
    Problem Name: Count BST nodes that lie in a given range
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a BST and a range [l, h] (inclusive), count the number of nodes whose
    values lie within this range.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. In the worst case we visit all
                     nodes, but BST pruning makes it much faster in practice.
    Space Complexity: O(H), where H is the height of the BST, for the recursion stack.

    Love Babbar Style Approach:
    We exploit the BST ORDERING to smartly PRUNE entire subtrees!

    At every node, there are 3 possible situations:

    Case 1 — node->data < l (node is TOO SMALL):
        The node itself AND its entire left subtree are all < l (because BST!).
        SKIP the left subtree entirely → only recurse RIGHT.

    Case 2 — node->data > h (node is TOO BIG):
        The node itself AND its entire right subtree are all > h (because BST!).
        SKIP the right subtree entirely → only recurse LEFT.

    Case 3 — l <= node->data <= h (node is IN RANGE!):
        Count this node (+1) and recurse into BOTH sides — there might be more
        valid nodes on either side!

    This is like a smart DFS that cuts off entire branches when they can't
    possibly contribute — way better than visiting every node blindly!

    Dry Run:
    BST:        10
               /  \
              5    50
             /    /  \
            1    40   100
    l = 5, h = 45

    - Node(10): 5 ≤ 10 ≤ 45? YES → count = 1, recurse BOTH
        - Node(5): 5 ≤ 5 ≤ 45? YES → count = 2, recurse BOTH
            - Node(1): 1 < 5 (TOO SMALL) → skip left, recurse RIGHT (NULL)
              → returns 0
            - Right of 5 = NULL → returns 0
          → returns 1 + 0 + 0 = 1
        - Node(50): 50 > 45 (TOO BIG) → skip right, recurse LEFT only
            - Node(40): 5 ≤ 40 ≤ 45? YES → count++, recurse BOTH (both NULL)
              → returns 1
          → returns 0 + 1 = 1
      → returns 1 + 1 + 1 = 3
    - Answer: 3 ✓ (nodes 5, 10, 40)

    Dry Run 2:
    Same BST, l = 10, h = 100

    - Node(10): IN RANGE → count=1, recurse BOTH
        - Node(5): 5 < 10 → TOO SMALL → skip left, recurse RIGHT (NULL) → 0
        - Node(50): IN RANGE → count++, recurse BOTH
            - Node(40): IN RANGE → count++ → 1
            - Node(100): IN RANGE → count++ → 1
          → 1 + 1 + 1 = 3
      → 1 + 0 + 3 = 4
    - Answer: 4 ✓ (nodes 10, 50, 40, 100)
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
    int getCount(Node* root, int l, int h) {
        // Base Case: Fell off the tree — 0 nodes to count
        if (root == NULL) return 0;

        // Case 1: Node is TOO SMALL (below range)
        // Entire left subtree is even smaller → skip it, only go RIGHT
        if (root->data < l) {
            return getCount(root->right, l, h);
        }

        // Case 2: Node is TOO BIG (above range)
        // Entire right subtree is even bigger → skip it, only go LEFT
        if (root->data > h) {
            return getCount(root->left, l, h);
        }

        // Case 3: Node is IN RANGE! Count it (+1) and search BOTH sides
        return 1 + getCount(root->left, l, h) + getCount(root->right, l, h);
    }
};

int main() {
    // Example 1:
    //         10
    //        /  \
    //       5    50
    //      /    /  \
    //     1    40   100
    // l = 5, h = 45  -->  Expected: 3 (nodes 5, 10, 40)

    Node* root1 = new Node(10);
    root1->left         = new Node(5);
    root1->right        = new Node(50);
    root1->left->left   = new Node(1);
    root1->right->left  = new Node(40);
    root1->right->right = new Node(100);

    Solution ob;
    // Output: 3
    cout << "Count in range [5, 45] (Example 1): " << ob.getCount(root1, 5, 45) << "\n";

    // Example 2: Same tree, l = 10, h = 100  -->  Expected: 4 (nodes 10, 40, 50, 100)
    // Output: 4
    cout << "Count in range [10, 100] (Example 2): " << ob.getCount(root1, 10, 100) << "\n";

    // Example 3:
    //     1
    //    / \
    //   2   3
    // l = 23, h = 95  -->  Expected: 0 (no nodes in range)

    Node* root2 = new Node(1);
    root2->left  = new Node(2);
    root2->right = new Node(3);

    // Output: 0
    cout << "Count in range [23, 95] (Example 3): " << ob.getCount(root2, 23, 95) << "\n";

    return 0;
}
