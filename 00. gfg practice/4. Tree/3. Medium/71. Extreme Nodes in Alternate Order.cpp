/*
    Problem Name: Extreme Nodes in Alternate Order
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, return a list containing the alternating extreme nodes at
    each level, starting with the rightmost node at the first level (Level 0).
    - Level 0 (even): Select Rightmost node.
    - Level 1 (odd):  Select Leftmost node.
    - Level 2 (even): Select Rightmost node.
    - Level 3 (odd):  Select Leftmost node, and so on...

    Examples:
    Input: root = [1, 2, 3, 4, 5, N, N, 7]
    Output: [1, 2, 5, 7]
    Explanation:
    - Level 0 (even): [1] -> Rightmost: 1
    - Level 1 (odd):  [2, 3] -> Leftmost: 2
    - Level 2 (even): [4, 5] -> Rightmost: 5
    - Level 3 (odd):  [7] -> Leftmost: 7

    Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14]
    Output: [20, 8, 12, 10]
    Explanation:
    - Level 0 (even): [20] -> Rightmost: 20
    - Level 1 (odd):  [8, 22] -> Leftmost: 8
    - Level 2 (even): [4, 12] -> Rightmost: 12
    - Level 3 (odd):  [10, 14] -> Leftmost: 10

    Constraints:
    1 <= number of nodes <= 10^5
    1 <= node->data <= 5 * 10^5

    Expected Complexities:
    Time Complexity: O(N), single pass BFS level order traversal.
    Space Complexity: O(N), for the BFS queue.

    Love Babbar Style Approach:
    BFS Level Order Traversal with Parity Flag:

    1. INTUITION:
       - Perform standard BFS Level Order Traversal level by level using a queue.
       - Track current `level` index (starting at 0).
       - For each level of size `sz`:
         * If `level` is EVEN (`level % 2 == 0`): pick the RIGHTMOST node (`i == sz - 1`).
         * If `level` is ODD (`level % 2 == 1`): pick the LEFTMOST node (`i == 0`).
       - Append selected node values to `result` and increment `level++`.

    2. ALGORITHM:
       - `if (!root) return {};`
       - Initialize `queue<Node*> q`, `vector<int> result`, `int level = 0`.
       - `q.push(root);`
       - While (`!q.empty()`):
         * `int sz = q.size();`
         * For `i = 0` to `sz - 1`:
           - `Node* curr = q.front(); q.pop();`
           - `if (level % 2 == 0 && i == sz - 1) result.push_back(curr->data);`
           - `if (level % 2 == 1 && i == 0) result.push_back(curr->data);`
           - `if (curr->left) q.push(curr->left);`
           - `if (curr->right) q.push(curr->right);`
         * `level++;`
       - Return `result`.

    Dry Run:
    root = [1, 2, 3, 4, 5, N, N, 7]
    - Level 0 (even): sz = 1. i = 0 == sz-1 -> res = [1]. q = [2, 3].
    - Level 1 (odd):  sz = 2. i = 0 -> res = [1, 2]. q = [4, 5].
    - Level 2 (even): sz = 2. i = 1 == sz-1 -> res = [1, 2, 5]. q = [7].
    - Level 3 (odd):  sz = 1. i = 0 -> res = [1, 2, 5, 7].
    Result: [1, 2, 5, 7] ✓
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
    // GFG Signature - BFS Alternate Extreme Nodes Selection
    vector<int> ExtremeNode(Node* root) {
        if (!root) return {};

        queue<Node*> q;
        q.push(root);

        vector<int> result;
        int level = 0;

        while (!q.empty()) {
            int sz = q.size();

            for (int i = 0; i < sz; i++) {
                Node* curr = q.front();
                q.pop();

                // Even Level (0, 2, 4...): Select Rightmost node (i == sz - 1)
                if (level % 2 == 0 && i == sz - 1) {
                    result.push_back(curr->data);
                }

                // Odd Level (1, 3, 5...): Select Leftmost node (i == 0)
                if (level % 2 == 1 && i == 0) {
                    result.push_back(curr->data);
                }

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            level++;
        }

        return result;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        / \
    //       4   5
    //      /
    //     7
    // Expected Output: 1 2 5 7
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->left->right = new Node(5);
    root1->left->left->left = new Node(7);

    vector<int> res1 = ob.ExtremeNode(root1);
    cout << "Example 1 Extreme Nodes: ";
    for (int val : res1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //            20
    //          /    \
    //         8      22
    //        / \
    //       4   12
    //          /  \
    //         10  14
    // Expected Output: 20 8 12 10
    Node* root2 = new Node(20);
    root2->left = new Node(8);
    root2->right = new Node(22);
    root2->left->left = new Node(4);
    root2->left->right = new Node(12);
    root2->left->right->left = new Node(10);
    root2->left->right->right = new Node(14);

    vector<int> res2 = ob.ExtremeNode(root2);
    cout << "Example 2 Extreme Nodes: ";
    for (int val : res2) cout << val << " ";
    cout << "\n";

    return 0;
}
