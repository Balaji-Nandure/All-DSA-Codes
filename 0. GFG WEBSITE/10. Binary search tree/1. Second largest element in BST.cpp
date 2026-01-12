/*
Problem:
Second Largest Element in a Binary Search Tree (BST)

Given a BST, find the second largest element.
If the tree has fewer than 2 nodes, return -1.

Approach (Optimized – Reverse Inorder Traversal):
- Traverse in Right → Root → Left order.
- Keep count of visited nodes.
- First visited node is the largest.
- Second visited node is the second largest.
- Stop traversal once found.

GeeksforGeeks:
https://www.geeksforgeeks.org/find-the-second-largest-element-in-bst/

Time Complexity:
O(H) average, O(N) worst case

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
    void reverseInorder(Node* root, int& count, int& ans) {

        if (root == NULL || count >= 2) return;

        reverseInorder(root->right, count, ans);

        count++;
        if (count == 2) {
            ans = root->data;
            return;
        }

        reverseInorder(root->left, count, ans);
    }

    int secondLargest(Node* root) {

        if (root == NULL) return -1;

        int count = 0;
        int ans = -1;

        reverseInorder(root, count, ans);
        return ans;
    }
};
