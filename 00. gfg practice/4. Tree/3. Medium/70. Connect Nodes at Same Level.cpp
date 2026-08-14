/*
    Problem Name: Connect Nodes at Same Level
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, connect the nodes that are at the same level.
    The Node structure contains an additional `nextRight` pointer:
    - Set `nextRight` to point to the adjacent right node at the same level.
    - The rightmost node at each level must point to `NULL`.

    Examples:
    Input:
               10
             /   \
            3     5
           / \     \
          4   1     2

    Output Connected Tree:
               10 ---------> NULL
              /  \
             3 -> 5 -------> NULL
            / \    \
           4-> 1 -> 2 -----> NULL

    Input: root = [10, 20, 30, 40, 60]
    Output Connected Tree:
               10 ---------> NULL
              /  \
             20 -> 30 -----> NULL
            /  \
           40 -> 60 -------> NULL

    Constraints:
    1 <= number of nodes <= 10^5
    0 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. BFS visits each node once.
    Space Complexity: O(N), for the BFS queue.

    Love Babbar Style Approach:
    BFS Level Order Traversal (Level Linking):

    1. INTUITION:
       - Using a Queue-based Level Order Traversal (BFS):
         * For each level of size `sz`, we process nodes from left to right.
         * Maintain a `prev` pointer initialized to `NULL`.
         * For each popped node `curr`:
           - If `prev != NULL`, link `prev->nextRight = curr`.
           - Update `prev = curr`.
           - Enqueue `curr->left` and `curr->right`.
         * After processing all nodes of the level, the rightmost node `prev->nextRight` is set to `NULL`.

    2. ALGORITHM:
       - `if (!root) return;`
       - Initialize `queue<Node*> q`.
       - `q.push(root);`
       - While (`!q.empty()`):
         * `int sz = q.size();`
         * `Node* prev = NULL;`
         * For `i = 0` to `sz - 1`:
           - `Node* curr = q.front(); q.pop();`
           - `if (prev != NULL) prev->nextRight = curr;`
           - `prev = curr;`
           - `if (curr->left) q.push(curr->left);`
           - `if (curr->right) q.push(curr->right);`
         * `prev->nextRight = NULL;`

    Dry Run:
               10
             /   \
            3     5

    - Level 0: sz = 1. curr = 10, prev = 10. 10->nextRight = NULL. q = [3, 5].
    - Level 1: sz = 2.
      * curr = 3, prev = 3.
      * curr = 5, prev->nextRight (3->nextRight) = 5. prev = 5.
      * 5->nextRight = NULL.
    Output: 10 -> NULL, 3 -> 5 -> NULL ✓
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for a binary tree node with nextRight pointer.
struct Node {
    int data;
    Node* left;
    Node* right;
    Node* nextRight;

    Node(int val) {
        data = val;
        left = right = nextRight = NULL;
    }
};

class Solution {
public:
    // GFG Signature - BFS Level Order Traversal
    void connect(Node *root) {
        if (!root) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            Node* prev = NULL;

            for (int i = 0; i < sz; i++) {
                Node* curr = q.front();
                q.pop();

                // Connect previous node's nextRight to current node
                if (prev != NULL) {
                    prev->nextRight = curr;
                }

                prev = curr;

                // Push left and right children to queue
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            // Rightmost node of current level points to NULL
            if (prev != NULL) {
                prev->nextRight = NULL;
            }
        }
    }
};

// Helper function to print level-by-level using nextRight pointers
void printNextRight(Node* root) {
    Node* levelStart = root;

    while (levelStart != NULL) {
        Node* curr = levelStart;
        levelStart = NULL;

        while (curr != NULL) {
            cout << curr->data;
            if (curr->nextRight) {
                cout << " -> " << curr->nextRight->data << " ";
            } else {
                cout << " -> NULL";
            }

            // Find start of next level
            if (!levelStart) {
                if (curr->left) levelStart = curr->left;
                else if (curr->right) levelStart = curr->right;
            }

            curr = curr->nextRight;
        }
        cout << "\n";
    }
}

int main() {
    Solution ob;

    // Example 1:
    //            10
    //          /   \
    //         3     5
    //        / \     \
    //       4   1     2
    Node* root1 = new Node(10);
    root1->left = new Node(3);
    root1->right = new Node(5);
    root1->left->left = new Node(4);
    root1->left->right = new Node(1);
    root1->right->right = new Node(2);

    ob.connect(root1);
    cout << "Example 1 Connected Tree (by nextRight pointers):\n";
    printNextRight(root1);
    cout << "\n";

    // Example 2:
    //         10
    //        /  \
    //       20   30
    //      /  \
    //     40   60
    Node* root2 = new Node(10);
    root2->left = new Node(20);
    root2->right = new Node(30);
    root2->left->left = new Node(40);
    root2->left->right = new Node(60);

    ob.connect(root2);
    cout << "Example 2 Connected Tree (by nextRight pointers):\n";
    printNextRight(root2);

    return 0;
}
