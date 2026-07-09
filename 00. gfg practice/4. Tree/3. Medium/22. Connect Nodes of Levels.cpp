/*
    Problem Name: Connect Nodes of Levels
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree where each node has an extra `nextRight` pointer,
    connect all nodes at the SAME LEVEL. Each node's `nextRight` should point to its
    immediate right neighbor. The LAST node at each level should have `nextRight = NULL`.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Standard BFS visits each node once.
    Space Complexity: O(W), where W is the maximum width of the tree (max nodes at any level).

    Love Babbar Style Approach:
    This is literally a Level Order Traversal (BFS) with ONE extra step — connect
    siblings at each level!

    In a normal BFS, we process nodes level by level using a queue. The trick is:
    at each level, we KNOW exactly how many nodes are on that level (queue size).
    So for each level:
    1. Pop nodes one by one from the queue.
    2. Each node's `nextRight` should point to the NEXT node we pop at the same level.
    3. The LAST node at the level gets `nextRight = NULL`.

    Simple implementation trick:
    - Process nodes at a level. For every node EXCEPT the last, set
      `currentNode->nextRight = queue.front()` (the next node in line!).
    - The last node naturally keeps `nextRight = NULL`.

    Dry Run:
    Tree:        1
                / \
               2   3
              / \    \
             4   5    6

    Level 0: Queue = [1]
      - Pop 1: no more nodes at this level → nextRight = NULL
      - Push children: 2, 3
      - Level connections: 1 → NULL

    Level 1: Queue = [2, 3], size = 2
      - Pop 2 (i=0): queue.front() = 3 → 2->nextRight = 3
      - Push children of 2: 4, 5
      - Pop 3 (i=1): last node → nextRight = NULL
      - Push children of 3: 6
      - Level connections: 2 → 3 → NULL

    Level 2: Queue = [4, 5, 6], size = 3
      - Pop 4 (i=0): queue.front() = 5 → 4->nextRight = 5
      - Pop 5 (i=1): queue.front() = 6 → 5->nextRight = 6
      - Pop 6 (i=2): last node → nextRight = NULL
      - Level connections: 4 → 5 → 6 → NULL

    Output: [1, #, 2, 3, #, 4, 5, 6, #] ✓
    (where # represents the end of a level / NULL nextRight)
*/

#include <iostream>
#include <queue>

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
    // GFG Signature
    Node* connect(Node* root) {
        // Edge Case: Empty tree
        if (root == NULL) return NULL;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();  // Number of nodes at the current level

            for (int i = 0; i < levelSize; i++) {
                Node* curr = q.front();
                q.pop();

                // If this is NOT the last node at this level,
                // point its nextRight to the NEXT node in the queue (its right neighbor!)
                if (i < levelSize - 1) {
                    curr->nextRight = q.front();
                } else {
                    // LAST node at this level — no right neighbor exists
                    curr->nextRight = NULL;
                }

                // Push children for the NEXT level
                if (curr->left)  q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
        }

        return root;
    }
};

// Helper: Print level-order with '#' marking end of each level (to verify nextRight connections)
void printConnected(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";

            if (curr->left)  q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << "# ";  // End of level marker
    }
    cout << "\n";
}

int main() {
    // Example 1:
    //         1
    //        / \
    //       2   3
    //      / \    \
    //     4   5    6
    // Expected: 1 # 2 3 # 4 5 6 #
    // Connections: 1→NULL, 2→3→NULL, 4→5→6→NULL

    Node* root1 = new Node(1);
    root1->left         = new Node(2);
    root1->right        = new Node(3);
    root1->left->left   = new Node(4);
    root1->left->right  = new Node(5);
    root1->right->right = new Node(6);

    Solution ob;
    ob.connect(root1);

    // Output: 1 # 2 3 # 4 5 6 #
    cout << "Connected Tree (Example 1): ";
    printConnected(root1);

    // Verify nextRight pointers manually
    cout << "Node 2 nextRight: " << (root1->left->nextRight ? to_string(root1->left->nextRight->data) : "NULL") << "\n";
    cout << "Node 4 nextRight: " << (root1->left->left->nextRight ? to_string(root1->left->left->nextRight->data) : "NULL") << "\n";
    cout << "Node 5 nextRight: " << (root1->left->right->nextRight ? to_string(root1->left->right->nextRight->data) : "NULL") << "\n";

    return 0;
}
