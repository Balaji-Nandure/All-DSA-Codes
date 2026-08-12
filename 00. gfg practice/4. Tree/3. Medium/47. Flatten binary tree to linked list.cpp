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

    Constraints:
    1 <= number of nodes in binary tree <= 10^5
    1 <= data of nodes <= 10^5

    ----------------------------------------------------------------------------------------
    APPROACH 1: Reverse Preorder Recursion (Right -> Left -> Root) [O(N) Time, O(H) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - Preorder is [Root -> Left -> Right].
    - If we traverse in REVERSE Preorder [Right -> Left -> Root]:
      * By the time we process `root`, the `Right` subtree and `Left` subtree have ALREADY
        been flattened into a linked list!
      * We maintain a `prev` pointer passed BY REFERENCE (`Node*& prev`) to track the head of
        the already flattened list without using global/class state.
      * We link `root->right = prev`, set `root->left = NULL`, and update `prev = root`.

    ----------------------------------------------------------------------------------------
    APPROACH 2: Morris Traversal (In-Place Pointer Threading) [O(N) Time, O(1) Space]
    ----------------------------------------------------------------------------------------
    INTUITION:
    - For any node `root` with a non-null `root->left`:
      1. Find `cur` = rightmost node in `root`'s left subtree.
      2. Attach `cur->right = root->right` (stitch right subtree to end of left subtree).
      3. Shift `root->right = root->left` (make left child the new right child).
      4. Set `root->left = NULL`.
      5. Advance `root = root->right`.

    Dry Run (Recursive Approach):
              1
            /   \
           2     5
          / \     \
         3   4     6

    - flatten(6): prev = 6
    - flatten(5): 5->right = 6, 5->left = NULL, prev = 5
    - flatten(4): 4->right = 5, 4->left = NULL, prev = 4
    - flatten(3): 3->right = 4, 3->left = NULL, prev = 3
    - flatten(2): 2->right = 3, 2->left = NULL, prev = 2
    - flatten(1): 1->right = 2, 1->left = NULL, prev = 1
    Resulting list: 1 -> 2 -> 3 -> 4 -> 5 -> 6 ✓
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

// =========================================================================
// APPROACH 1: Recursive Reverse Preorder (Pass-by-Reference prev pointer)
// =========================================================================
class SolutionRecursive {
private:
    void solve(Node* root, Node*& prev) {
        if (root == NULL) return;

        // Step 1: Recursively process RIGHT subtree first
        solve(root->right, prev);

        // Step 2: Recursively process LEFT subtree second
        solve(root->left, prev);

        // Step 3: Attach current node to head of flattened list
        root->right = prev;
        root->left = NULL;

        // Step 4: Update prev pointer to current root
        prev = root;
    }

public:
    void flatten(Node* root) {
        Node* prev = NULL; // Local variable passed by reference
        solve(root, prev);
    }
};

// =========================================================================
// APPROACH 2: Morris Traversal Iterative (O(1) Auxiliary Space)
// =========================================================================
class SolutionMorris {
public:
    void flatten(Node* root) {
        while (root) {
            if (root->left) {
                Node* cur = root->left;

                while (cur->right)
                    cur = cur->right;

                cur->right = root->right;
                root->right = root->left;
                root->left = NULL;
            }

            root = root->right;
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
    // Test Approach 1: Recursive Reverse Preorder
    {
        Node* root1 = new Node(1);
        root1->left = new Node(2);
        root1->right = new Node(5);
        root1->left->left = new Node(3);
        root1->left->right = new Node(4);
        root1->right->right = new Node(6);

        SolutionRecursive ob1;
        ob1.flatten(root1);
        cout << "Recursive Solution Output: ";
        printFlattenedList(root1); // Expected: 1 2 3 4 5 6
    }

    // Test Approach 2: Iterative Morris Traversal
    {
        Node* root2 = new Node(1);
        root2->left = new Node(2);
        root2->right = new Node(5);
        root2->left->left = new Node(3);
        root2->left->right = new Node(4);
        root2->right->right = new Node(6);

        SolutionMorris ob2;
        ob2.flatten(root2);
        cout << "Morris Iterative Output : ";
        printFlattenedList(root2); // Expected: 1 2 3 4 5 6
    }

    return 0;
}
