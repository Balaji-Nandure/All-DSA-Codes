/*
    Problem Name: Corner Nodes in Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, find the corner elements from root to the last level.
    The corner elements are defined as the leftmost (`i == 0`) and rightmost (`i == n - 1`)
    nodes at each level of the binary tree.

    Examples:
    Input:
             1
           /   \
          2     3
         / \   / \
        4   5 6   7

    Output: [1, 2, 3, 4, 7]
    Explanation:
    - Level 0: [1]       -> Corner nodes: 1
    - Level 1: [2, 3]    -> Corner nodes: 2, 3
    - Level 2: [4, 5, 6, 7] -> Corner nodes: 4, 7

    Input:
            10
           /  \
          20  30
         /  \
        40  60
    Output: [10, 20, 30, 40, 60]

    Constraints:
    1 <= N <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node is pushed and popped from the queue once.
    Space Complexity: O(W), where W is the maximum width of the tree, for the queue.

    Love Babbar Style Approach:
    Level Order Traversal (BFS) Index-Based Selection:

    1. INTUITION:
       - A standard Level Order Traversal (BFS) processes nodes level by level.
       - For any level containing `n` nodes:
         * Node at `i = 0` is the LEFTMOST corner node of that level.
         * Node at `i = n - 1` is the RIGHTMOST corner node of that level.
         * Note: If `n == 1` (level has only one node, e.g. root), `i == 0` and `i == n - 1`
           refer to the exact same node, so it is pushed ONCE.

    2. ALGORITHM:
       - `if (!root) return ans;`
       - Push `root` into `queue<Node*> q`.
       - While (`!q.empty()`):
         * `int n = q.size();`
         * For `i` from `0` to `n - 1`:
           - `Node* cur = q.front(); q.pop();`
           - `if (i == 0 || i == n - 1) ans.push_back(cur->data);`
           - `if (cur->left) q.push(cur->left);`
           - `if (cur->right) q.push(cur->right);`
       - Return `ans`.

    Dry Run:
             1
           /   \
          2     3
         / \   / \
        4   5 6   7

    - Level 0: n=1 -> i=0: cur=1 -> ans=[1]. q=[2, 3]
    - Level 1: n=2 -> i=0: cur=2 (ans=[1, 2]). i=1: cur=3 (ans=[1, 2, 3]). q=[4, 5, 6, 7]
    - Level 2: n=4 -> i=0: cur=4 (ans=[1, 2, 3, 4]). i=1: cur=5. i=2: cur=6. i=3: cur=7 (ans=[1, 2, 3, 4, 7]).

    Result: [1, 2, 3, 4, 7] ✓
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
    vector<int> printCorner(Node *root) {
        vector<int> ans;
        if (!root) return ans;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();

            for (int i = 0; i < n; i++) {
                Node* cur = q.front();
                q.pop();

                // Pick the first (leftmost) and last (rightmost) node of each level
                if (i == 0 || i == n - 1)
                    ans.push_back(cur->data);

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //             1
    //           /   \
    //          2     3
    //         / \   / \
    //        4   5 6   7
    // Expected Output: 1 2 3 4 7
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->right->left = new Node(6);
    root1->right->right = new Node(7);

    vector<int> corners1 = ob.printCorner(root1);
    cout << "Example 1 Corner Nodes: ";
    for (int val : corners1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //         10
    //        /  \
    //       20   30
    //      /  \
    //     40   60
    // Expected Output: 10 20 30 40 60
    Node* root2 = new Node(10);
    root2->left = new Node(20);
    root2->right = new Node(30);
    root2->left->left = new Node(40);
    root2->left->right = new Node(60);

    vector<int> corners2 = ob.printCorner(root2);
    cout << "Example 2 Corner Nodes: ";
    for (int val : corners2) cout << val << " ";
    cout << "\n";

    return 0;
}
