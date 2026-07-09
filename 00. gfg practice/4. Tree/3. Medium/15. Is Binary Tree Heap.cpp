/*
    Problem Name: Is Binary Tree Heap
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, determine whether it satisfies the properties
    of a MAX-HEAP. A binary tree is a max-heap if and only if:
    1. COMPLETENESS: Every level (except possibly the last) is completely filled,
       and nodes at the last level are as far LEFT as possible.
    2. MAX-HEAP PROPERTY: Every node's value >= values of ALL its children.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once.
    Space Complexity: O(N), for the recursion stack in the worst case (skewed tree).

    Love Babbar Style Approach:
    The KEY insight — use the ARRAY INDEX TRICK for complete binary tree validation!

    Think of a binary tree stored in an array (0-indexed):
        - Root lives at index 0.
        - For any node at index i:
            Left child  --> index (2*i + 1)
            Right child --> index (2*i + 2)

    A binary tree is COMPLETE if and only if: for every node at index i → i < totalNodes.
    WHY? In a complete binary tree with N nodes, all indices from 0 to N-1 are occupied,
    with no GAPS. If a node exists at index >= N, it means there's a gap somewhere
    (a node that should be filled but isn't) → NOT a complete tree!

    So our recursive function does TWO things at once:
    - Step 1 (Completeness Check): If index >= totalNodes, return FALSE immediately.
    - Step 2 (Max-Heap Check): Verify that both children's values are <= parent's value.
    - Step 3: Recurse into left and right with their updated indices.

    We first count total nodes (O(N)) and then run the validation (O(N)).

    Dry Run:
    Tree: [97, 46, 37, 12, 3, 7, 31, 6, 9]  --> n = 9
              97  (i=0)
             /  \
           46    37  (i=1, i=2)
          / \   / \
        12   3 7  31  (i=3, i=4, i=5, i=6)
       / \
      6   9  (i=7, i=8)

    isHeap(97, i=0, n=9):
      0 < 9 ✓ | left=46 ≤ 97 ✓ | right=37 ≤ 97 ✓
      isHeap(46, i=1, n=9):
        1 < 9 ✓ | left=12 ≤ 46 ✓ | right=3 ≤ 46 ✓
        isHeap(12, i=3, n=9):
          3 < 9 ✓ | left=6 ≤ 12 ✓ | right=9 ≤ 12 ✓
          isHeap(6,  i=7, n=9): 7 < 9 ✓, no children → TRUE
          isHeap(9,  i=8, n=9): 8 < 9 ✓, no children → TRUE
          return TRUE
        isHeap(3, i=4, n=9): 4 < 9 ✓, no children → TRUE
        return TRUE
      isHeap(37, i=2, n=9):
        2 < 9 ✓ | left=7 ≤ 37 ✓ | right=31 ≤ 37 ✓
        isHeap(7,  i=5, n=9): TRUE | isHeap(31, i=6, n=9): TRUE
        return TRUE
      return TRUE ✓

    Dry Run 2 (NOT a heap):
    Tree: [97, 46, 37, 12, 3, 7, 31, N, N, 2, 4]  --> n = 9 (only 9 non-null nodes)
          97
         /  \
       46    37
      / \   / \
     12   3 7  31
         / \
        2   4
    
    - Node(3) is at index 4. Its children should be at indices 9 and 10.
    - But n = 9, so index 9 is already out of bounds (9 >= 9)!
    - isHeap(Node(2), i=9, n=9): 9 >= 9 → return FALSE! (Completeness violated!)
    - The tree is NOT complete — a node exists where it shouldn't. ✓
*/

#include <iostream>
#include <queue>

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
    // Helper 1: Count total number of nodes in the tree
    int countNodes(Node* root) {
        if (root == NULL) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Helper 2: Validate completeness + max-heap property simultaneously
    bool validate(Node* root, int index, int totalNodes) {
        // Base Case: NULL node is always valid
        if (root == NULL) return true;

        // COMPLETENESS CHECK: If this node's index >= total nodes, there's a gap!
        // This means a node exists at a position it shouldn't in a complete binary tree.
        if (index >= totalNodes) return false;

        // MAX-HEAP PROPERTY CHECK: Parent must be >= both children
        if (root->left  != NULL && root->left->data  > root->data) return false;
        if (root->right != NULL && root->right->data > root->data) return false;

        // Recurse into both subtrees with their correct array indices
        bool leftValid  = validate(root->left,  2 * index + 1, totalNodes);
        bool rightValid = validate(root->right, 2 * index + 2, totalNodes);

        return leftValid && rightValid;
    }

public:
    // GFG Signature
    bool isHeap(struct Node* tree) {
        // Step 1: Count total nodes (needed for the index-based completeness check)
        int n = countNodes(tree);

        // Step 2: Validate starting from root at index 0
        return validate(tree, 0, n);
    }
};

int main() {
    // Example 1: [97, 46, 37, 12, 3, 7, 31, 6, 9]
    //            97
    //           /  \
    //          46   37
    //         / \  / \
    //        12  3 7  31
    //       / \
    //      6   9
    // Expected: true

    Node* root1 = new Node(97);
    root1->left              = new Node(46);
    root1->right             = new Node(37);
    root1->left->left        = new Node(12);
    root1->left->right       = new Node(3);
    root1->right->left       = new Node(7);
    root1->right->right      = new Node(31);
    root1->left->left->left  = new Node(6);
    root1->left->left->right = new Node(9);

    Solution ob;
    // Output: true
    cout << "Is Max-Heap (Example 1): " << (ob.isHeap(root1) ? "true" : "false") << "\n";

    // Example 2: [97, 46, 37, 12, 3, 7, 31, N, N, 2, 4]
    //            97
    //           /  \
    //          46   37
    //         / \  / \
    //        12  3 7  31
    //           / \
    //          2   4
    // Expected: false (NOT complete — node 3 has children but node 12 doesn't)

    Node* root2 = new Node(97);
    root2->left              = new Node(46);
    root2->right             = new Node(37);
    root2->left->left        = new Node(12);
    root2->left->right       = new Node(3);
    root2->right->left       = new Node(7);
    root2->right->right      = new Node(31);
    root2->left->right->left  = new Node(2);
    root2->left->right->right = new Node(4);

    // Output: false
    cout << "Is Max-Heap (Example 2): " << (ob.isHeap(root2) ? "true" : "false") << "\n";

    return 0;
}
