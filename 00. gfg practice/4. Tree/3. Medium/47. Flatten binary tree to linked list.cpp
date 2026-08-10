/*
    Problem Name: Flatten binary tree to linked list
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, flatten the tree into a "linked list" in-place:
    - The "linked list" uses the same Node structure where `right` child pointer points
      to the next node in the list and `left` child pointer is ALWAYS NULL.
    - The nodes must appear in the exact order of a PREORDER traversal of the binary tree.

    Examples:
    Input:
              1
            /   \
           2     5
          / \     \
         3   4     6

    Output: 1 -> 2 -> 3 -> 4 -> 5 -> 6 (all left = NULL)
    Explanation: Preorder traversal is 1, 2, 3, 4, 5, 6.

    Input:
            1
           / \
          3   4
             /
            2
             \
              5
    Output: 1 -> 3 -> 4 -> 2 -> 5 (all left = NULL)

    Constraints:
    1 <= number of nodes in binary tree <= 10^5
    1 <= data of nodes <= 10^5

    Expected Complexities:
    Time Complexity: O(N), each node is processed at most twice.
    Space Complexity: O(1) Auxiliary Space (Pure In-Place Morris Traversal!).

    Love Babbar Style Approach:
    Morris Traversal (In-Place Pointer Threading):

    1. INTUITION:
       - In Preorder traversal (Root -> Left -> Right):
         * The LEFT subtree must come directly after the Root.
         * The RIGHT subtree must come directly after the RIGHTMOST node of the Left subtree!
       - Therefore, for any node `curr` with a non-null `curr->left`:
         1. Find `prev` = rightmost node in `curr`'s left subtree.
         2. Attach `prev->right = curr->right` (stitch right subtree to end of left subtree).
         3. Shift `curr->right = curr->left` (make left child the new right child).
         4. Set `curr->left = NULL`.
         5. Move `curr = curr->right`.

    2. ALGORITHM:
       - `curr = root`
       - While (`curr != NULL`):
         * If `curr->left != NULL`:
           - `Node* prev = curr->left;`
           - While (`prev->right != NULL`): `prev = prev->right;`
           - `prev->right = curr->right;`
           - `curr->right = curr->left;`
           - `curr->left = NULL;`
         * `curr = curr->right;`

    Dry Run:
              1
            /   \
           2     5
          / \     \
         3   4     6

    - curr = 1: curr->left = 2.
      prev = 2 -> moves to 4 (rightmost of left subtree).
      Attach 4->right = 5.
      1->right = 2, 1->left = NULL.
    - curr = 2: curr->left = 3.
      prev = 3 (rightmost of left subtree).
      Attach 3->right = 4.
      2->right = 3, 2->left = NULL.
    - Resulting tree: 1 -> 2 -> 3 -> 4 -> 5 -> 6 (all left = NULL) ✓
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
    // GFG Signature - Morris Flattening O(1) Space
    void flatten(Node *root) {
        Node* curr = root;

        while (curr != NULL) {
            if (curr->left != NULL) {
                // Find the rightmost node of the left subtree
                Node* prev = curr->left;
                while (prev->right != NULL) {
                    prev = prev->right;
                }

                // Connect the rightmost node of left subtree to curr's right subtree
                prev->right = curr->right;

                // Move left subtree to right
                curr->right = curr->left;

                // Set left pointer to NULL
                curr->left = NULL;
            }

            // Move to next node along the right pointer
            curr = curr->right;
        }
    }
};

// Helper function to print flattened linked list via right pointers
void printFlattenedList(Node* root) {
    Node* curr = root;
    while (curr != NULL) {
        cout << curr->data << " ";
        if (curr->left != NULL) {
            cout << "(Error: Left not NULL!) ";
        }
        curr = curr->right;
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    //          1
    //        /   \
    //       2     5
    //      / \     \
    //     3   4     6
    // Expected Output: 1 2 3 4 5 6
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(5);
    root1->left->left = new Node(3);
    root1->left->right = new Node(4);
    root1->right->right = new Node(6);

    ob.flatten(root1);
    cout << "Example 1 Flattened List: ";
    printFlattenedList(root1);

    // Example 2:
    //        1
    //       / \
    //      3   4
    //         /
    //        2
    //         \
    //          5
    // Expected Output: 1 3 4 2 5
    Node* root2 = new Node(1);
    root2->left = new Node(3);
    root2->right = new Node(4);
    root2->right->left = new Node(2);
    root2->right->left->right = new Node(5);

    ob.flatten(root2);
    cout << "Example 2 Flattened List: ";
    printFlattenedList(root2);

    return 0;
}
