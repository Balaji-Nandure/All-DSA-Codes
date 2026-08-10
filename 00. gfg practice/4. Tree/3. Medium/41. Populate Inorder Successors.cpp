/*
    Problem Name: Populate Inorder Successors
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree, complete the function to populate the next pointer for all nodes.
    The next pointer for every node should point to the Inorder successor of the node.
    You do not have to return or print anything. Just make changes in the root node given to you.

    Examples:
    Input:
           10
           /  \
          8   12
         /
        3
    Output: 3->8 8->10 10->12 12->-1
    Explanation: Inorder traversal is 3, 8, 10, 12.
    3's next is 8, 8's next is 10, 10's next is 12, 12's next is NULL.

    Input:
           1
          /
         2
       /
      3
    Output: 3->2 2->1 1->-1
    Explanation: Inorder traversal is 3, 2, 1.

    Constraints:
    1 <= no. of nodes <= 10^5
    1 <= data of node <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node is visited once during Inorder traversal.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Inorder Traversal with Previous Pointer (`prev` Tracking):

    1. INTUITION:
       - Inorder traversal (Left -> Root -> Right) visits nodes in strictly INCREASING order of their
         inorder sequence.
       - As we visit current node `curr` during Inorder traversal:
         * The node visited JUST BEFORE `curr` was `prev`.
         * Therefore, `curr` is the INORDER SUCCESSOR of `prev`!
         * We simply link: `if (prev) prev->next = curr;`
         * Then update `prev = curr` for the next node in line.

    2. ALGORITHM:
       - Maintain `prev` pointer initialized to `NULL` (passed by reference `Node*& prev`).
       - `solve(root, prev)`:
         * Base Case: `if (root == NULL)` return.
         * Traverse left subtree: `solve(root->left, prev)`.
         * Process current node:
           - `if (prev != NULL) prev->next = root;`
           - `prev = root;`
         * Traverse right subtree: `solve(root->right, prev)`.

    Dry Run:
           10
           /  \
          8   12
         /
        3

    Inorder sequence: [3, 8, 10, 12]

    - Visit 3 : prev = NULL -> prev becomes 3
    - Visit 8 : prev = 3 -> 3->next = 8. prev becomes 8
    - Visit 10: prev = 8 -> 8->next = 10. prev becomes 10
    - Visit 12: prev = 10 -> 10->next = 12. prev becomes 12
    - Traversal ends. 12->next remains NULL (-1).

    Resulting links: 3->8, 8->10, 10->12, 12->NULL ✓
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node with next pointer.
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next;

    Node(int val) {
        data = val;
        left = right = next = NULL;
    }
};

class Solution {
private:
    void solve(Node* root, Node*& prev) {
        if (root == NULL) return;

        // Traverse left subtree
        solve(root->left, prev);

        // Link previous node's next pointer to current node
        if (prev != NULL) {
            prev->next = root;
        }

        // Update prev pointer to current node
        prev = root;

        // Traverse right subtree
        solve(root->right, prev);
    }

public:
    // GFG Signature
    void populateNext(Node *root) {
        Node* prev = NULL;
        solve(root, prev);
    }
};

// Helper function to print nodes linked via next pointers
void printInorderNext(Node* root) {
    // Find left-most node (first node in Inorder)
    Node* curr = root;
    while (curr && curr->left) {
        curr = curr->left;
    }

    // Traverse via next pointers
    while (curr) {
        cout << curr->data << "->";
        if (curr->next) {
            cout << curr->next->data << " ";
        } else {
            cout << "-1 ";
        }
        curr = curr->next;
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    //       10
    //       /  \
    //      8   12
    //     /
    //    3
    // Expected: 3->8 8->10 10->12 12->-1
    Node* root1 = new Node(10);
    root1->left = new Node(8);
    root1->right = new Node(12);
    root1->left->left = new Node(3);

    ob.populateNext(root1);

    cout << "Example 1 Next Links: ";
    printInorderNext(root1);

    // Example 2:
    //       1
    //      /
    //     2
    //   /
    //  3
    // Expected: 3->2 2->1 1->-1
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->left->left = new Node(3);

    ob.populateNext(root2);

    cout << "Example 2 Next Links: ";
    printInorderNext(root2);

    return 0;
}
