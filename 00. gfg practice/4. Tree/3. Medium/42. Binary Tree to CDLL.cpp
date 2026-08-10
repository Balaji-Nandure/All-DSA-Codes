/*
    Problem Name: Binary Tree to CDLL (Circular Doubly Linked List)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, convert it to a Circular Doubly Linked List (CDLL) in-place.
    - The `left` pointer acts as `previous` pointer in CDLL.
    - The `right` pointer acts as `next` pointer in CDLL.
    - Order of nodes in CDLL must match the Inorder traversal of the Binary Tree.
    - Head of CDLL must be the first node in Inorder traversal (leftmost node).
    - It must be CIRCULAR: `head->left = tail (last node)` and `tail->right = head`.

    Examples:
    Input: root = [1, 3, 2]
    Output: 3 <-> 1 <-> 2 (Circular: 2->right = 3, 3->left = 2)
    Explanation: Inorder traversal of tree is [3, 1, 2].

    Input: root = [10, 20, 30, 40, 60]
    Output: 40 <-> 20 <-> 60 <-> 10 <-> 30

    Constraints:
    1 <= number of nodes <= 10^3
    0 <= data of a node <= 10^4

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Inorder traversal visits each node once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion call stack.

    Love Babbar Style Approach:
    Inorder Traversal + Pointer Rewiring (`head` & `prev` Tracking):

    1. INTUITION:
       - An Inorder traversal (Left -> Root -> Right) visits nodes in the exact order required
         for the CDLL.
       - As we traverse:
         * The VERY FIRST node visited becomes `head`.
         * For every subsequent node `cur`:
           - Connect `prev->right = cur` and `cur->left = prev`.
           - Update `prev = cur`.
       - After completing the full Inorder traversal, `prev` points to the LAST node (`tail`).
       - Make it CIRCULAR by linking: `head->left = prev` and `prev->right = head`.

    2. ALGORITHM:
       - Helper `solve(cur, head, prev)`:
         * `if (!cur) return;`
         * Recurse left: `solve(cur->left, head, prev);`
         * If `!head`, set `head = cur`.
         * If `prev != NULL`:
           - `prev->right = cur;`
           - `cur->left = prev;`
         * Update `prev = cur;`
         * Recurse right: `solve(cur->right, head, prev);`
       - In `bTreeToClist(root)`:
         * `if (!root) return NULL;`
         * Call `solve(root, head, prev);`
         * `head->left = prev;`
         * `prev->right = head;`
         * Return `head`.

    Dry Run:
          1
        /   \
       3     2

    Inorder sequence: 3, 1, 2

    - Visit 3: head = 3, prev = 3
    - Visit 1: prev = 3 -> 3->right = 1, 1->left = 3. prev becomes 1
    - Visit 2: prev = 1 -> 1->right = 2, 2->left = 1. prev becomes 2 (tail)
    - Make Circular: 3->left = 2, 2->right = 3.

    Resulting CDLL: 3 <-> 1 <-> 2 (Circular ✓)
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
    void solve(Node* cur, Node*& head, Node*& prev) {
        if (!cur) return;

        // Traverse left subtree
        solve(cur->left, head, prev);

        // Set head if processing the first node in Inorder
        if (!head) {
            head = cur;
        }

        // Connect previous node with current node in doubly linked list format
        if (prev != NULL) {
            prev->right = cur;
            cur->left = prev;
        }
        prev = cur;

        // Traverse right subtree
        solve(cur->right, head, prev);
    }

public:
    // GFG Signature
    Node* bTreeToClist(Node* root) {
        if (!root) return NULL;

        Node *head = NULL, *prev = NULL;
        solve(root, head, prev);

        // Connect tail and head to form a CIRCULAR doubly linked list
        head->left = prev;
        prev->right = head;

        return head;
    }
};

// Helper function to print CDLL in forward order
void printCDLL(Node* head) {
    if (!head) return;

    Node* curr = head;
    do {
        cout << curr->data;
        if (curr->right != head) {
            cout << " <-> ";
        }
        curr = curr->right;
    } while (curr != head);

    cout << " (Circular back to " << head->data << ")\n";
}

int main() {
    Solution ob;

    // Example 1:
    //      1
    //    /   \
    //   3     2
    // Expected: 3 <-> 1 <-> 2
    Node* root1 = new Node(1);
    root1->left = new Node(3);
    root1->right = new Node(2);

    Node* cdll1 = ob.bTreeToClist(root1);
    cout << "Example 1 CDLL: ";
    printCDLL(cdll1);

    // Example 2:
    //         10
    //        /  \
    //       20   30
    //      /  \
    //     40   60
    // Expected: 40 <-> 20 <-> 60 <-> 10 <-> 30
    Node* root2 = new Node(10);
    root2->left = new Node(20);
    root2->right = new Node(30);
    root2->left->left = new Node(40);
    root2->left->right = new Node(60);

    Node* cdll2 = ob.bTreeToClist(root2);
    cout << "Example 2 CDLL: ";
    printCDLL(cdll2);

    return 0;
}
