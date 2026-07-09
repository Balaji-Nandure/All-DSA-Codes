/*
    Problem Name: Isomorphic Trees
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the roots of two binary trees, determine whether they are isomorphic.
    Two trees are isomorphic if one can be obtained from the other by a series of FLIPS
    (swapping left and right children of any number of nodes at any level).
    Two empty trees are isomorphic.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node is visited at most once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    Think of it like the "isIdentical" problem but with a TWIST — at every node,
    the children can be FLIPPED (swapped)!

    So at every node, there are exactly TWO ways the trees can still match:

    Case 1 — NO FLIP (children are in the SAME order):
        root1->left  matches root2->left   AND
        root1->right matches root2->right

    Case 2 — FLIP (children are SWAPPED):
        root1->left  matches root2->right  AND
        root1->right matches root2->left

    If EITHER case works → the trees are isomorphic at this node!

    Base Cases:
    - Both NULL → TRUE  (both ended at the same time — perfect!)
    - One NULL  → FALSE (structure can't match, no amount of flipping helps)
    - Values differ → FALSE (data mismatch, flipping doesn't change values)

    Dry Run:
    T1:       1            T2:       1
             / \                   / \
            2   3                 3   2       ← flipped at node 1!
           / \   \               /   / \
          4   5   6             6   4   5     ← flipped at node 3!
             / \               / \
            7   8             8   7           ← flipped at node 5!

    isIso(1, 1): values match (1==1)
      Case 1 (no flip): isIso(2,3) AND isIso(3,2)?
        isIso(2,3): values 2≠3 → FALSE
      Case 1 fails.
      Case 2 (flip): isIso(2,2) AND isIso(3,3)?
        isIso(2,2): values match (2==2)
          Case 1: isIso(4,4) AND isIso(5,5)?
            isIso(4,4): values match, both leaves → TRUE
            isIso(5,5): values match
              Case 1: isIso(7,7) AND isIso(8,8) → TRUE AND TRUE → TRUE!
            → TRUE
          Case 1 works → TRUE!
        isIso(3,3): values match (3==3)
          Case 1: isIso(NULL,6) → FALSE
          Case 2: isIso(NULL,NULL)=TRUE AND isIso(6,6)=TRUE → TRUE!
        → TRUE
      Case 2 works → TRUE ✓

    Dry Run 2:
    T1:     1        T2:     1
           / \              / \
          2   3            3   2
         /                        \
        4                          4

    isIso(1,1): values match
      Case 2 (flip): isIso(2,2) AND isIso(3,3)?
        isIso(2,2): values match
          Case 1: isIso(4,NULL) → FALSE
          Case 2: isIso(4,NULL) → FALSE (still NULL vs 4, can't fix!)
        → FALSE
      Case 1: isIso(2,3) → values 2≠3 → FALSE
    → FALSE ✓
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
    bool isIsomorphic(Node* root1, Node* root2) {
        // Base Case 1: Both are NULL — perfectly matched!
        if (root1 == NULL && root2 == NULL) {
            return true;
        }

        // Base Case 2: One is NULL, the other isn't — structure can't match
        if (root1 == NULL || root2 == NULL) {
            return false;
        }

        // Base Case 3: Values don't match — flipping can't fix a data mismatch!
        if (root1->data != root2->data) {
            return false;
        }

        // TWO POSSIBILITIES — check if EITHER works:

        // Case 1: NO FLIP — children are in the same order
        bool noFlip = isIsomorphic(root1->left, root2->left) &&
                      isIsomorphic(root1->right, root2->right);

        // Case 2: FLIP — children are swapped at this node
        bool flipped = isIsomorphic(root1->left, root2->right) &&
                       isIsomorphic(root1->right, root2->left);

        // If EITHER arrangement works, the trees are isomorphic at this node!
        return noFlip || flipped;
    }
};

int main() {
    // Example 1:
    // T1:       1           T2:       1
    //          / \                  / \
    //         2   3                3   2
    //        / \   \              /   / \
    //       4   5   6            6   4   5
    //          / \               / \
    //         7   8             8   7
    // Expected: true (flips at nodes 1, 3, and 5)

    Node* r1 = new Node(1);
    r1->left              = new Node(2);
    r1->right             = new Node(3);
    r1->left->left        = new Node(4);
    r1->left->right       = new Node(5);
    r1->right->right      = new Node(6);
    r1->left->right->left = new Node(7);
    r1->left->right->right = new Node(8);

    Node* r2 = new Node(1);
    r2->left              = new Node(3);
    r2->right             = new Node(2);
    r2->left->left        = new Node(6);
    r2->right->left       = new Node(4);
    r2->right->right      = new Node(5);
    r2->right->right->left  = new Node(8);
    r2->right->right->right = new Node(7);

    Solution ob;
    // Output: true
    cout << "Isomorphic (Example 1): " << (ob.isIsomorphic(r1, r2) ? "true" : "false") << "\n";

    // Example 2:
    // T1:   1      T2:   1
    //      / \          / \
    //     2   3        3   2
    //    /                  \
    //   4                    4
    // Expected: false

    Node* r3 = new Node(1);
    r3->left       = new Node(2);
    r3->right      = new Node(3);
    r3->left->left = new Node(4);

    Node* r4 = new Node(1);
    r4->left        = new Node(3);
    r4->right       = new Node(2);
    r4->right->right = new Node(4);

    // Output: false
    cout << "Isomorphic (Example 2): " << (ob.isIsomorphic(r3, r4) ? "true" : "false") << "\n";

    // Example 3:
    // T1:   1      T2:   1
    //      / \          / \
    //     2   3        3   2
    //    /                    \
    //   4                      4
    // Expected: true (flip at node 1 swaps 2↔3, then flip at node 2 moves 4 to right)
    // Wait — actually: after flip at 1: T1 becomes 1(3,2(4)). T2 is 1(3,2(N,4)).
    // T1's node 2 has left=4, T2's node 2 has right=4. Flip at node 2 → match! → TRUE

    Node* r5 = new Node(1);
    r5->left       = new Node(2);
    r5->right      = new Node(3);
    r5->left->left = new Node(4);

    Node* r6 = new Node(1);
    r6->left         = new Node(3);
    r6->right        = new Node(2);
    r6->right->right = new Node(4);

    // Output: true
    cout << "Isomorphic (Example 3): " << (ob.isIsomorphic(r5, r6) ? "true" : "false") << "\n";

    return 0;
}
