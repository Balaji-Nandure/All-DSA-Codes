/*
    Problem Name: Predecessor and Successor
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a BST and an integer key, find the inorder predecessor and
    successor of the given key. If either is not found, set it to NULL.
    Note: The key may or may not exist in the BST.
    - Predecessor: the LARGEST value that is STRICTLY LESS than the key.
    - Successor  : the SMALLEST value that is STRICTLY GREATER than the key.

    Expected Complexities:
    Time Complexity: O(H), where H is the height of the BST.
                     O(log N) for a balanced BST, O(N) for a skewed BST.
    Space Complexity: O(1), since we use an iterative approach — no recursion stack needed!

    Love Babbar Style Approach:
    The KEY insight: We DON'T need to do a full inorder traversal. We exploit the BST
    property to navigate smartly, updating our best candidates along the way!

    Case 1 — We hit a node GREATER than key (root->data > key):
        - This node could be our Successor (it's greater than key, and we haven't found
          anything closer yet). So UPDATE suc = root.
        - But can we find something even closer to key? YES! Go LEFT (values decrease).

    Case 2 — We hit a node LESS than key (root->data < key):
        - This node could be our Predecessor (it's less than key, best so far). So UPDATE pre = root.
        - But can we find something even closer to key? YES! Go RIGHT (values increase).

    Case 3 — We hit the EXACT KEY (root->data == key):
        - Predecessor is the RIGHTMOST node of the LEFT subtree (largest value < key).
        - Successor is the LEFTMOST node of the RIGHT subtree (smallest value > key).
        - Find them and BREAK — we're done!

    Why does this work? Because at every step we're using BST ordering to
    zoom in on better and better candidates. No wasted visits!

    Dry Run:
    BST:        50
               /  \
              30   70
             / \  / \
            20 40 60  80
    key = 65 (NOT in BST)

    - root=50,  50 < 65  --> pre = Node(50), go RIGHT
    - root=70,  70 > 65  --> suc = Node(70), go LEFT
    - root=60,  60 < 65  --> pre = Node(60), go RIGHT (60 is a BETTER predecessor than 50!)
    - root=NULL          --> STOP
    - Answer: pre=60, suc=70 ✓

    Dry Run 2:
    BST:    8
           / \
          1   9
           \    \
            4   10
           /
          3
    key = 8 (EXISTS in BST)

    - root=8, 8 == 8  --> EXACT KEY FOUND!
        - Left subtree exists (Node(1)): find RIGHTMOST
          Node(1) -> right=Node(4) -> right=NULL --> rightmost = Node(4) --> pre = Node(4)
        - Right subtree exists (Node(9)): find LEFTMOST
          Node(9) -> left=NULL --> leftmost = Node(9) --> suc = Node(9)
        - BREAK
    - Answer: pre=4, suc=9 ✓
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
    // GFG Signature: returns a vector where result[0] = predecessor, result[1] = successor
    // If not found, the respective pointer is NULL.
    vector<Node*> findPreSuc(Node* root, int key) {
        Node* pre = NULL;
        Node* suc = NULL;

        Node* curr = root;

        while (curr != NULL) {

            if (curr->data == key) {
                // EXACT KEY FOUND!

                // 1. Predecessor = RIGHTMOST node of the LEFT subtree
                if (curr->left != NULL) {
                    Node* temp = curr->left;
                    while (temp->right != NULL) {
                        temp = temp->right;  // Keep going right to find the largest
                    }
                    pre = temp;
                }

                // 2. Successor = LEFTMOST node of the RIGHT subtree
                if (curr->right != NULL) {
                    Node* temp = curr->right;
                    while (temp->left != NULL) {
                        temp = temp->left;  // Keep going left to find the smallest
                    }
                    suc = temp;
                }

                break;  // We've found everything we need — stop the loop!

            } else if (curr->data > key) {
                // Current node is GREATER than key — it's a valid successor candidate!
                // Update and move LEFT to search for an even closer (smaller) successor.
                suc  = curr;
                curr = curr->left;

            } else {
                // Current node is LESS than key — it's a valid predecessor candidate!
                // Update and move RIGHT to search for an even closer (larger) predecessor.
                pre  = curr;
                curr = curr->right;
            }
        }

        // Return as {predecessor, successor} — NULL if not found
        return {pre, suc};
    }
};

int main() {
    // Example 1:
    //         50
    //        /  \
    //       30   70
    //      / \  / \
    //     20 40 60  80
    // key = 65  --> Expected: pre=60, suc=70

    Node* root1 = new Node(50);
    root1->left         = new Node(30);
    root1->right        = new Node(70);
    root1->left->left   = new Node(20);
    root1->left->right  = new Node(40);
    root1->right->left  = new Node(60);
    root1->right->right = new Node(80);

    Solution ob;
    vector<Node*> ans1 = ob.findPreSuc(root1, 65);

    // Output: Predecessor: 60  Successor: 70
    cout << "Predecessor: " << (ans1[0] ? to_string(ans1[0]->data) : "NULL") << "\n";
    cout << "Successor  : " << (ans1[1] ? to_string(ans1[1]->data) : "NULL") << "\n\n";

    // Example 2:
    //     8
    //    / \
    //   1   9
    //    \    \
    //     4   10
    //    /
    //   3
    // key = 8  --> Expected: pre=4, suc=9

    Node* root2 = new Node(8);
    root2->left              = new Node(1);
    root2->right             = new Node(9);
    root2->left->right       = new Node(4);
    root2->left->right->left = new Node(3);
    root2->right->right      = new Node(10);

    vector<Node*> ans2 = ob.findPreSuc(root2, 8);

    // Output: Predecessor: 4  Successor: 9
    cout << "Predecessor: " << (ans2[0] ? to_string(ans2[0]->data) : "NULL") << "\n";
    cout << "Successor  : " << (ans2[1] ? to_string(ans2[1]->data) : "NULL") << "\n";

    return 0;
}
