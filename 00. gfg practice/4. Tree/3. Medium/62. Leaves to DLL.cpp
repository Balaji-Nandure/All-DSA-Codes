/*
    Problem Name: Leaves to DLL
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree, extract all its leaf nodes to form a Doubly Linked List (DLL) starting
    from the leftmost leaf.
    - Modify the original tree in-place by removing the extracted leaf nodes from the tree.
    - Use node's `left` pointer as `prev` and `right` pointer as `next` in the DLL.
    - Return the head pointer of the constructed Doubly Linked List.

    Note:
    - Leaves must be extracted in left-to-right order (Inorder).
    - Only original leaf nodes are extracted.

    Examples:
    Input:
              1
            /   \
           2     3
          / \     \
         4   5     6

    Output:
    Modified Tree (without original leaves):
              1
            /   \
           2     3

    Doubly Linked List: 4 <-> 5 <-> 6

    Constraints:
    1 <= number of nodes in tree <= 10^4
    1 <= data of nodes <= 10^4

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes in the tree.
    Space Complexity: O(H), where H is the height of the tree for recursion call stack.

    Love Babbar Style Approach:
    Inorder Tree Traversal + Leaf Extraction with Pass-by-Reference Pointers:

    1. INTUITION:
       - To extract leaf nodes in left-to-right order, we perform an Inorder DFS traversal (Left -> Root -> Right).
       - When visiting node `root`:
         * If `root` is an ORIGINAL LEAF node (`!root->left && !root->right`):
           - If `head == NULL` (first leaf): set `head = root` and `prev = root`.
           - Else: link `prev->right = root`, `root->left = prev`, and update `prev = root`.
           - Return `NULL` to its parent node so the parent detaches this leaf node from the tree!
         * If `root` is an INTERNAL node:
           - Recursively process `root->left = solve(root->left, head, prev)`.
           - Recursively process `root->right = solve(root->right, head, prev)`.
           - Return `root` to keep the internal node in the tree.
       - Pass `head` and `prev` pointers by reference (`Node*& head`, `Node*& prev`) to eliminate global/class state.

    2. ALGORITHM:
       - `solve(root, head, prev)`:
         * `if (root == NULL) return NULL;`
         * `if (!root->left && !root->right)`:
           - `if (head == NULL) { head = root; prev = root; }`
           - `else { prev->right = root; root->left = prev; prev = root; }`
           - `return NULL;`
         * `root->left = solve(root->left, head, prev);`
         * `root->right = solve(root->right, head, prev);`
         * `return root;`

    Dry Run:
            1
          /   \
         2     3
        / \     \
       4   5     6

    - solve(4) -> leaf! head = 4, prev = 4. Returns NULL -> 2->left = NULL.
    - solve(5) -> leaf! prev(4)->right = 5, 5->left = 4, prev = 5. Returns NULL -> 2->right = NULL.
    - solve(6) -> leaf! prev(5)->right = 6, 6->left = 5, prev = 6. Returns NULL -> 3->right = NULL.

    DLL formed: 4 <-> 5 <-> 6 (head = 4)
    Modified tree: 1 -> (left: 2, right: 3) ✓
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
    Node* solve(Node* root, Node*& head, Node*& prev) {
        if (root == NULL) return NULL;

        // If current node is a leaf node, extract it into DLL and return NULL to detach from parent
        if (!root->left && !root->right) {
            if (head == NULL) {
                head = root;
                prev = root;
            } else {
                prev->right = root;
                root->left = prev;
                prev = root;
            }
            return NULL; // Detach leaf from tree
        }

        // Recurse left and right subtrees
        root->left = solve(root->left, head, prev);
        root->right = solve(root->right, head, prev);

        return root;
    }

public:
    // GFG Signature
    Node* convertToDLL(Node* root) {
        Node* head = NULL;
        Node* prev = NULL;

        solve(root, head, prev);

        return head;
    }
};

// Helper function to print DLL from left to right and right to left
void printDLL(Node* head) {
    if (!head) {
        cout << "Empty DLL\n";
        return;
    }

    Node* curr = head;
    Node* tail = NULL;

    cout << "Forward: ";
    while (curr) {
        cout << curr->data << " ";
        tail = curr;
        curr = curr->right;
    }
    cout << "\n";

    cout << "Backward: ";
    while (tail) {
        cout << tail->data << " ";
        tail = tail->left;
    }
    cout << "\n";
}

// Helper function to print Inorder traversal of modified tree
void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        / \     \
    //       4   5     6
    // Expected DLL: 4 <-> 5 <-> 6
    // Expected Modified Tree Inorder: 2 1 3
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->right = new Node(6);

    Node* head1 = ob.convertToDLL(root1);

    cout << "Example 1 DLL:\n";
    printDLL(head1);

    cout << "Example 1 Modified Tree Inorder: ";
    printInorder(root1);
    cout << "\n";

    return 0;
}
