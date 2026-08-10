/*
    Problem Name: Check if two Nodes are Cousins
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree with distinct node values and two integers a and b,
    check whether the nodes with values a and b are cousins.

    Note: Two nodes are cousins if they are at the SAME depth/level but have DIFFERENT parents.

    Examples:
    Input: root = [1, 2, 3], a = 2, b = 3
    Output: false
    Explanation: Nodes 2 and 3 are at the same level but share the same parent (1). Not cousins.

    Input: root = [1, 2, 3, 5, N, N, 4], a = 5, b = 4
    Output: true
    Explanation: Nodes 5 and 4 are at the same level (depth 2) and have different parents (2 and 3). Cousins!

    Input: root = [10, 5, 15, 3, 7, 12, 20], a = 7, b = 12
    Output: true
    Explanation: Nodes 7 and 12 are at depth 2 with different parents (5 and 15). Cousins!

    Constraints:
    1 <= number of nodes <= 10^5
    1 <= node->data <= 10^5
    1 <= a, b <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. BFS level order traversal processes each node once.
    Space Complexity: O(W), where W is the maximum width of the tree, for the queue.

    Love Babbar Style Approach:
    Level Order Traversal (BFS) Level-by-Level Validation:

    1. INTUITION:
       - What makes two nodes COUSINS?
         * Condition 1: They must be at the SAME depth.
         * Condition 2: They must have DIFFERENT parents.
       - A BFS (Level Order Traversal) processes nodes level-by-level:
         * At each level, we track boolean flags `x` (found `a`) and `y` (found `b`).
         * Before pushing children to queue, check if current node is parent of BOTH `a` and `b`.
           If yes -> return `false` (siblings, same parent!).
         * After completing a level:
           - If `x && y` are both `true` -> return `true` (both found at same level, different parents!).
           - If `x || y` is `true` (one found, but not the other) -> return `false` (they exist at different levels!).

    2. ALGORITHM:
       - Queue initialized with `root`.
       - While queue is not empty:
         * `n = q.size()`, flags `x = false, y = false`.
         * Process all `n` nodes of current level:
           - `cur = q.front(); q.pop();`
           - Check parent constraint: If `cur->left` and `cur->right` match `{a, b}`, return `false`.
           - Push children and update `x` or `y` if `a` or `b` is discovered.
         * After level loop:
           - `if (x && y)` return `true`.
           - `if (x || y)` return `false`.
       - Return `false`.

    Dry Run:
             1
           /   \
          2     3
         /       \
        5         4
    a = 5, b = 4

    - Level 0: q=[1]. n=1. cur=1. Left=2, Right=3. q=[2, 3]. x=false, y=false.
    - Level 1: q=[2, 3]. n=2.
      - cur=2: left=5 -> x=true. q=[5].
      - cur=3: right=4 -> y=true. q=[5, 4].
      - Level 1 finished. x=true, y=true -> BOTH FOUND AT SAME LEVEL! -> Return true ✓
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
    // GFG Signature
    bool isCousins(Node* root, int a, int b) {
        if (!root) return false;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            bool x = false, y = false;

            while (n--) {
                Node* cur = q.front();
                q.pop();

                // Check if current node is parent to BOTH a and b -> same parent -> NOT cousins
                if (cur->left && cur->right &&
                    ((cur->left->data == a && cur->right->data == b) ||
                     (cur->left->data == b && cur->right->data == a)))
                    return false;

                if (cur->left) {
                    q.push(cur->left);
                    if (cur->left->data == a) x = true;
                    if (cur->left->data == b) y = true;
                }

                if (cur->right) {
                    q.push(cur->right);
                    if (cur->right->data == a) x = true;
                    if (cur->right->data == b) y = true;
                }
            }

            // Both nodes found at the current level -> Cousins!
            if (x && y) return true;

            // One node found at current level, but not the other -> Different levels!
            if (x || y) return false;
        }

        return false;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //      1
    //     / \
    //    2   3
    // a = 2, b = 3  --> Expected Output: false (siblings)
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);

    cout << "Example 1 (a=2, b=3): " << (ob.isCousins(root1, 2, 3) ? "true" : "false") << "\n";

    // Example 2:
    //         1
    //       /   \
    //      2     3
    //     /       \
    //    5         4
    // a = 5, b = 4  --> Expected Output: true (cousins)
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(5);
    root2->right->right = new Node(4);

    cout << "Example 2 (a=5, b=4): " << (ob.isCousins(root2, 5, 4) ? "true" : "false") << "\n";

    // Example 3:
    //          10
    //        /    \
    //       5      15
    //      / \    /  \
    //     3   7  12  20
    // a = 7, b = 12  --> Expected Output: true
    Node* root3 = new Node(10);
    root3->left = new Node(5);
    root3->right = new Node(15);
    root3->left->left = new Node(3);
    root3->left->right = new Node(7);
    root3->right->left = new Node(12);
    root3->right->right = new Node(20);

    cout << "Example 3 (a=7, b=12): " << (ob.isCousins(root3, 7, 12) ? "true" : "false") << "\n";

    return 0;
}
