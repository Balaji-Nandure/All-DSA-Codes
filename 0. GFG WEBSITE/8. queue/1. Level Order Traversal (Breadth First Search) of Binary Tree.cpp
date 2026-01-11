/*
Problem:
Level Order Traversal (Breadth First Search) of Binary Tree

Given the root of a binary tree, perform a level order traversal
of its nodes’ values (from left to right, level by level).

Rules:
- Visit all nodes at the present depth before moving to the next depth.
- Return the traversal as a list of values.

Example:
Input:
        1
      /   \
     2     3
    / \     \
   4   5     6

Output:
[1, 2, 3, 4, 5, 6]

Approach (Optimized – Queue / BFS):
- Use a queue to store tree nodes.
- Push root node into the queue.
- While queue is not empty:
  - Pop front node, add its value to result.
  - Push its left and right children if they exist.

GeeksforGeeks:
https://www.geeksforgeeks.org/level-order-tree-traversal/

LeetCode:
https://leetcode.com/problems/binary-tree-level-order-traversal/

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {

        vector<vector<int>> result;
        if (root == NULL) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            vector<int> level;
            for (int i = 0; i < sz; ++i) {
                Node* curr = q.front();
                q.pop();

                level.push_back(curr->data);

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            result.push_back(level);
        }

        return result;
    }
};
