/*
Problem:
Sum of K Smallest Elements in a Binary Search Tree (BST)

Given a Binary Search Tree and an integer K,
find the sum of the K smallest elements in the BST.
If the BST has fewer than K nodes, return the sum of all nodes.

Rules:
- BST property holds (left < root < right).
- K ≥ 1.

Example:
BST:
        10
       /  \
      5   20
     / \
    3   7

K = 3

Smallest elements: 3, 5, 7
Output:
15

Approach (Optimized – Inorder Traversal):
- Inorder traversal of BST gives sorted order (ascending).
- Traverse Left → Root → Right.
- Keep adding node values until K elements are counted.
- Stop traversal once K elements are processed.

GeeksforGeeks:
https://www.geeksforgeeks.org/sum-k-smallest-elements-bst/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(H + K) average, O(N) worst case

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
    void inorder(Node* root, int& k, int& sum) {

        if (root == NULL || k == 0) return;

        inorder(root->left, k, sum);

        if (k > 0) {
            sum += root->data;
            k--;
        }

        inorder(root->right, k, sum);
    }

    int sumKSmallest(Node* root, int K) {

        int sum = 0;
        inorder(root, K, sum);
        return sum;
    }
};
