/*
    Problem Name: Diagonal Tree Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a binary tree, return the diagonal traversal. Imagine lines of slope -1 passing
    through the tree. Nodes on the same diagonal line belong to the same group.
    Left subtree diagonal elements come before right subtree elements.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node visited exactly once.
    Space Complexity: O(N), for the queue and result vector.

    Love Babbar Style Approach:
    The KEY insight — what does "diagonal" mean in a tree?

    When you go RIGHT from a node, you stay on the SAME diagonal!
    When you go LEFT from a node, you drop to the NEXT diagonal (diagonal + 1)!

    Think of it like this:
        - Root is on diagonal 0.
        - Going RIGHT keeps you on the same diagonal (same slope -1 line).
        - Going LEFT moves you one diagonal down.

    So diagonal traversal is basically: for each node, keep going right (same diagonal),
    and push any left children into a queue for later processing (next diagonals).

    BFS Approach:
    1. Start with root in the queue.
    2. Pop a node from the queue.
    3. Keep walking RIGHT from this node — add each node to the result.
       Every time we see a LEFT child along the way, push it into the queue.
    4. Repeat until queue is empty.

    This naturally gives us diagonal 0 first, then diagonal 1, then diagonal 2, etc.!

    Dry Run:
    Tree:         8
                /   \
               3     10
              / \      \
             1   6     14
                / \   /
               4   7 13

    Queue starts: [8]

    Pop 8: Walk right → 8 → 10 → 14 → NULL
        - At 8: push left child 3 into queue
        - At 10: no left child
        - At 14: push left child 13 into queue
        Result so far: [8, 10, 14]
        Queue: [3, 13]

    Pop 3: Walk right → 3 → 6 → 7 → NULL
        - At 3: push left child 1 into queue
        - At 6: push left child 4 into queue
        - At 7: no left child
        Result so far: [8, 10, 14, 3, 6, 7]
        Queue: [13, 1, 4]

    Pop 13: Walk right → 13 → NULL
        - No left child
        Result so far: [8, 10, 14, 3, 6, 7, 13]
        Queue: [1, 4]

    Pop 1: Walk right → 1 → NULL
        - No left child
        Result so far: [8, 10, 14, 3, 6, 7, 13, 1]
        Queue: [4]

    Pop 4: Walk right → 4 → NULL
        - No left child
        Result: [8, 10, 14, 3, 6, 7, 13, 1, 4]
        Queue: [] → DONE!

    Answer: [8, 10, 14, 3, 6, 7, 13, 1, 4] ✓
*/

#include <iostream>
#include <vector>
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
    // GFG Signature
    vector<int> diagonal(Node* root) {
        vector<int> result;

        // Edge Case: Empty tree
        if (root == NULL) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            // Walk along the RIGHT path — all these nodes are on the SAME diagonal
            while (curr != NULL) {
                // Add current node to the result (it's on this diagonal)
                result.push_back(curr->data);

                // If there's a LEFT child, it belongs to the NEXT diagonal → queue it!
                if (curr->left != NULL) {
                    q.push(curr->left);
                }

                // Keep going RIGHT — same diagonal!
                curr = curr->right;
            }
        }

        return result;
    }
};

int main() {
    // Example 1:
    //           8
    //         /   \
    //        3     10
    //       / \      \
    //      1   6     14
    //         / \   /
    //        4   7 13
    // Expected: [8, 10, 14, 3, 6, 7, 13, 1, 4]

    Node* root1 = new Node(8);
    root1->left              = new Node(3);
    root1->right             = new Node(10);
    root1->left->left        = new Node(1);
    root1->left->right       = new Node(6);
    root1->right->right      = new Node(14);
    root1->left->right->left  = new Node(4);
    root1->left->right->right = new Node(7);
    root1->right->right->left = new Node(13);

    Solution ob;
    vector<int> ans1 = ob.diagonal(root1);

    // Output: 8 10 14 3 6 7 13 1 4
    cout << "Diagonal Traversal (Example 1): ";
    for (int val : ans1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //     1
    //    /
    //   2
    //  /
    // 3
    // Expected: [1, 2, 3]

    Node* root2 = new Node(1);
    root2->left       = new Node(2);
    root2->left->left = new Node(3);

    vector<int> ans2 = ob.diagonal(root2);

    // Output: 1 2 3
    cout << "Diagonal Traversal (Example 2): ";
    for (int val : ans2) cout << val << " ";
    cout << "\n";

    return 0;
}
