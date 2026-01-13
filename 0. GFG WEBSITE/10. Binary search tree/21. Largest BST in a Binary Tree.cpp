/*
Problem:
Largest BST in a Binary Tree

Given a Binary Tree, find the size (number of nodes) of the
largest subtree which is also a Binary Search Tree (BST).

Rules:
- Subtree must follow strict BST property.
- Tree is NOT necessarily a BST.
- Return size of the largest BST subtree.

Example:
Input Tree:
          50
         /  \
       30    60
      / \   / \
     5  20 45  70
                 \
                  80

Output:
5

Explanation:
The subtree rooted at 60 is a BST with nodes {60,45,70,80}
(plus correct structure), size = 5.

Approach (Optimal – Postorder Tree DP):
For every node, compute and return:
- isBST      → whether subtree is BST
- size       → size of subtree if BST
- minVal     → minimum value in subtree
- maxVal     → maximum value in subtree

Logic:
- Perform postorder traversal.
- A node is root of BST if:
    left.isBST == true
    right.isBST == true
    left.maxVal < root->data < right.minVal
- Track maximum BST size found.

GeeksforGeeks:
https://www.geeksforgeeks.org/largest-bst-binary-tree-set-2/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(H)
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
    struct Info {
        bool isBST;
        int size;
        int minVal;
        int maxVal;
    };

    Info solve(Node* root, int& ans) {

        if (root == NULL) {
            return {true, 0, INT_MAX, INT_MIN};
        }

        Info L = solve(root->left, ans);
        Info R = solve(root->right, ans);

        Info curr;

        if (L.isBST && R.isBST &&
            root->data > L.maxVal &&
            root->data < R.minVal) {

            curr.isBST = true;
            curr.size = L.size + R.size + 1;
            curr.minVal = min(root->data, L.minVal);
            curr.maxVal = max(root->data, R.maxVal);

            ans = max(ans, curr.size);
        } else {
            curr.isBST = false;
            curr.size = 0;
            curr.minVal = INT_MIN;
            curr.maxVal = INT_MAX;
        }

        return curr;
    }

    int largestBst(Node* root) {

        int ans = 0;
        solve(root, ans);
        return ans;
    }
};
