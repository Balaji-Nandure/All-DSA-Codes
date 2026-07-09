/*
    Problem Name: Check Subtree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two binary trees with roots root1 (tree T) and root2 (tree S), determine
    whether tree S is a subtree of tree T.
    S is a subtree of T if there exists a node in T such that the subtree rooted at
    that node is IDENTICAL to S (same structure AND same node values).

    Expected Complexities:
    Time Complexity: O(N * M), where N = nodes in T, M = nodes in S.
                     For every node in T (N nodes), we run isIdentical which costs O(M).
    Space Complexity: O(H_T), where H_T is the height of T, for the recursion stack.

    Love Babbar Style Approach:
    The trick is to BREAK this problem into two clean sub-problems:

    Sub-Problem 1 — isIdentical(tree1, tree2):
        Checks if two trees are EXACTLY the same (structure + values).
        - Both NULL?         --> TRUE  (both ended at the same time — perfect match!)
        - One NULL, other not? --> FALSE (structure mismatch — trees differ!)
        - Values differ?     --> FALSE
        - Otherwise, recursively check left subtrees AND right subtrees must BOTH match.

    Sub-Problem 2 — isSubTree(T, S):
        We traverse every node of T and ask: "Is S identical to the subtree rooted HERE?"
        - S is NULL?                    --> TRUE  (empty tree is always a subtree)
        - T is NULL?                    --> FALSE (T is exhausted, nothing left to match S)
        - isIdentical(T, S) is TRUE?    --> TRUE! We found our match — return immediately!
        - Otherwise, check the LEFT subtree of T OR the RIGHT subtree of T.
          (If S is found in EITHER side, we return true!)

    Dry Run:
    T:      1            S:    3
           / \                  \
          2   3                  4
             /
            4
    
    - isSubTree(1, 3)
        - isIdentical(1, 3)? --> values 1 ≠ 3 --> false
        - isSubTree(2, 3)?
            - isIdentical(2, 3)? --> values 2 ≠ 3 --> false
            - isSubTree(NULL, 3) --> false
            - isSubTree(NULL, 3) --> false
            - return false
        - isSubTree(3, 3)?  <-- we're now at node 3 of T!
            - isIdentical(3, 3)?
                - values 3 == 3 ✓
                - isIdentical(4, 4)? --> values 4 == 4, both children NULL → true ✓
                - isIdentical(NULL, NULL) → true ✓
                - return TRUE!
            - return TRUE!
        - return TRUE ✓

    Dry Run 2:
    T = S = [26, 10, N, 20, 30, 40, 60]  (both trees are IDENTICAL)
    - isSubTree(26, 26)
        - isIdentical(26, 26)?
            - Recursively every node matches perfectly
            - return TRUE!
        - return TRUE ✓
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
    // Helper: checks if two trees are EXACTLY identical (structure + values)
    bool isIdentical(Node* t1, Node* t2) {
        // Both NULL at the same time — perfectly matched!
        if (t1 == NULL && t2 == NULL) {
            return true;
        }

        // One is NULL and the other isn't — structure mismatch!
        if (t1 == NULL || t2 == NULL) {
            return false;
        }

        // Values differ — not identical
        if (t1->data != t2->data) {
            return false;
        }

        // Both left AND right subtrees must be identical
        return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right);
    }

public:
    // GFG Signature: returns true if S (root2) is a subtree of T (root1)
    bool isSubTree(Node* T, Node* S) {
        // Base Case: Empty tree S is always a subtree of any tree
        if (S == NULL) {
            return true;
        }

        // Base Case: T is exhausted but S still has nodes — impossible match
        if (T == NULL) {
            return false;
        }

        // CHECK: Is the subtree rooted at the CURRENT node of T identical to S?
        if (isIdentical(T, S)) {
            return true;  // Found our match — stop searching!
        }

        // Not found here — search in the LEFT subtree OR the RIGHT subtree of T
        return isSubTree(T->left, S) || isSubTree(T->right, S);
    }
};

int main() {
    // Example 1:
    //  T:       1          S:   3
    //          / \               \
    //         2   3               4
    //            /
    //           4
    // Expected Output: true

    Node* root1 = new Node(1);
    root1->left         = new Node(2);
    root1->right        = new Node(3);
    root1->right->left  = new Node(4);

    Node* root2 = new Node(3);
    root2->right = new Node(4);

    Solution ob;
    // Output: true
    cout << "Is Subtree (Example 1): " << (ob.isSubTree(root1, root2) ? "true" : "false") << "\n";

    // Example 2:
    //  T = S = [26, 10, N, 20, 30, 40, 60] (both trees identical)
    //  T:         26               S:        26
    //            /                           /
    //           10                          10
    //          /  \                        /  \
    //         20  30                      20  30
    //        / \                         / \
    //       40  60                      40  60
    // Expected Output: true

    Node* root3 = new Node(26);
    root3->left             = new Node(10);
    root3->left->left       = new Node(20);
    root3->left->right      = new Node(30);
    root3->left->left->left  = new Node(40);
    root3->left->left->right = new Node(60);

    Node* root4 = new Node(26);
    root4->left             = new Node(10);
    root4->left->left       = new Node(20);
    root4->left->right      = new Node(30);
    root4->left->left->left  = new Node(40);
    root4->left->left->right = new Node(60);

    // Output: true
    cout << "Is Subtree (Example 2): " << (ob.isSubTree(root3, root4) ? "true" : "false") << "\n";

    return 0;
}
