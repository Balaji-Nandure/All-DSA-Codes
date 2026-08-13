/*
    Problem Name: Complete Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree, check whether it is a Complete Binary Tree (CBT).
    - A Complete Binary Tree is a binary tree in which every level, except possibly the last,
      is completely filled, and all nodes in the last level are as far left as possible.

    Examples:
    Input: root = [1, 2, 3]
    Output: true
    Explanation:
            1
          /   \
         2     3
    All levels are completely filled -> Complete Binary Tree.

    Input: root = [1, 2, 3, 4, N, 5, 6]
    Output: false
    Explanation:
            1
          /   \
         2     3
        / \   / \
       4   N 5   6
    Node 2 has a missing right child (NULL), but node 3 has left and right children (5, 6).
    Since there is a gap before node 5, it is NOT a Complete Binary Tree!

    Constraints:
    1 <= number of nodes <= 10^5
    0 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. BFS level order visits each node once.
    Space Complexity: O(N), for the BFS queue.

    Love Babbar Style Approach:
    BFS Level Order Traversal (NULL Flag Strategy):

    1. INTUITION:
       - In a Level Order Traversal of a Complete Binary Tree:
         * Nodes must be packed tightly from left to right without any missing gaps.
         * Therefore, once we encounter the FIRST `NULL` node (a missing child):
           - ALL subsequent nodes in level order traversal MUST ALSO BE `NULL`!
         * If we see ANY non-NULL node AFTER encountering a `NULL` node:
           - It indicates a gap in the tree structure -> Return `false`!

    2. ALGORITHM:
       - `if (!root) return true;`
       - Initialize `queue<Node*> q`, `bool nullFound = false`.
       - `q.push(root);`
       - While (`!q.empty()`):
         * `Node* curr = q.front(); q.pop();`
         * If (`curr == NULL`):
           - `nullFound = true;`
         * Else:
           - If (`nullFound == true`) return `false`; // Gap detected!
           - `q.push(curr->left);`
           - `q.push(curr->right);`
       - Return `true`.

    Dry Run:
            1
          /   \
         2     3
        /
       4

    - q = [1], nullFound = false
    - Pop 1 -> q = [2, 3]
    - Pop 2 -> q = [3, 4, NULL]
    - Pop 3 -> q = [4, NULL, NULL, NULL]
    - Pop 4 -> q = [NULL, NULL, NULL, NULL, NULL, NULL]
    - Pop NULL -> nullFound = true
    - Pop NULL -> nullFound = true
    - Queue empties -> Returns true ✓
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
public:
    // GFG Signature - Level Order NULL Flag Traversal
    bool isCompleteBC(Node* root) {
        if (!root) return true;

        queue<Node*> q;
        q.push(root);

        bool nullFound = false;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr == NULL) {
                // First NULL encountered: all remaining nodes in queue must also be NULL
                nullFound = true;
            } else {
                // If we encounter a non-NULL node after a NULL node, tree is not complete
                if (nullFound) {
                    return false;
                }

                // Push left and right children (including NULLs)
                q.push(curr->left);
                q.push(curr->right);
            }
        }

        return true;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //        1
    //      /   \
    //     2     3
    // Expected Output: true
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);

    cout << "Example 1 Is Complete Tree: " << (ob.isCompleteBC(root1) ? "true" : "false") << "\n";

    // Example 2:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   N 5   6
    // Expected Output: false
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->right->left = new Node(5);
    root2->right->right = new Node(6);

    cout << "Example 2 Is Complete Tree: " << (ob.isCompleteBC(root2) ? "true" : "false") << "\n";

    return 0;
}
