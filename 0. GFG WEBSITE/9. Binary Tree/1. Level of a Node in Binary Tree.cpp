/*
Problem:
Level of a Node in a Binary Tree

Given a binary tree and a target node value X,
find the level (depth) of the node in the binary tree.
Root node is at level 1.

If the node is not present, return 0.

Rules:
- Levels are counted starting from 1.
- Use any traversal method.

Example:
Input:
        1
      /   \
     2     3
    / \
   4   5

X = 5

Output:
3

Approach (Optimized – Level Order Traversal / BFS):
- Use a queue to perform BFS.
- Traverse level by level.
- Keep track of current level.
- When the target node is found, return the level.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-level-of-a-given-node-in-a-binary-tree/

LeetCode:
No direct equivalent problem.

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
    int getLevel(Node* root, int target) {

        if (root == NULL) return 0;

        queue<Node*> q;
        q.push(root);
        int level = 1;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {
                Node* curr = q.front();
                q.pop();

                if (curr->data == target) {
                    return level;
                }

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            level++;
        }

        return 0;
    }
};
