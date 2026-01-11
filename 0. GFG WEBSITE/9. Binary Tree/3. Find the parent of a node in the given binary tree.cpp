/*
Problem:
Find the Parent of a Node in a Binary Tree

Given a binary tree and a target node value X,
find and return the parent of the node containing X.
If X is the root or not present in the tree, return -1.

Rules:
- Tree is NOT necessarily a BST.
- Root has no parent.
- Return parent node value, not pointer.

Example:
Input:
        1
      /   \
     2     3
    / \
   4   5

X = 5

Output:
2

Approach (Optimized – Level Order Traversal / BFS):
- Use a queue for BFS traversal.
- For every node:
  - Check if its left or right child has value X.
  - If yes, current node is the parent.
- If traversal completes without finding, return -1.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-parent-of-a-node-in-binary-tree/

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
    int findParent(Node* root, int x) {

        if (root == NULL || root->data == x) return -1;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* curr = q.front();
            q.pop();

            if (curr->left) {
                if (curr->left->data == x) return curr->data;
                q.push(curr->left);
            }

            if (curr->right) {
                if (curr->right->data == x) return curr->data;
                q.push(curr->right);
            }
        }

        return -1;
    }
};
/*
Problem:
Find the Parent of a Node in a Binary Tree

Given a binary tree and a target node value X,
find and return the parent of the node containing X.
If X is the root or not present in the tree, return -1.

Rules:
- Tree is NOT necessarily a BST.
- Root has no parent.
- Return parent node value, not pointer.

Example:
Input:
        1
      /   \
     2     3
    / \
   4   5

X = 5

Output:
2

Approach (Optimized – Level Order Traversal / BFS):
- Use a queue for BFS traversal.
- For every node:
  - Check if its left or right child has value X.
  - If yes, current node is the parent.
- If traversal completes without finding, return -1.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-parent-of-a-node-in-binary-tree/

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
    int findParent(Node* root, int x) {

        if (root == NULL || root->data == x) return -1;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* curr = q.front();
            q.pop();

            if (curr->left) {
                if (curr->left->data == x) return curr->data;
                q.push(curr->left);
            }

            if (curr->right) {
                if (curr->right->data == x) return curr->data;
                q.push(curr->right);
            }
        }

        return -1;
    }
};
