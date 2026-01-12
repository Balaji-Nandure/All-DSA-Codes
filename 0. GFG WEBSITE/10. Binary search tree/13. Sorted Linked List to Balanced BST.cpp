/*
Problem:
Sorted Linked List to Balanced Binary Search Tree

Given the head of a sorted (ascending) singly linked list,
convert it into a height-balanced Binary Search Tree (BST).

Rules:
- Use all nodes from the linked list.
- The resulting BST must be height-balanced.
- Do NOT convert the linked list to an array.

Example:
Input:
1 -> 2 -> 3 -> 4 -> 5

Output (one possible BST):
      3
     / \
    2   5
   /   /
  1   4

Approach (Optimized – Inorder Simulation on Linked List):
- Count the number of nodes in the linked list.
- Build BST using divide & conquer on index range [0…n-1].
- Construct left subtree first.
- Use current list node as root (simulating inorder traversal).
- Move list pointer forward.
- Construct right subtree.

Why this works:
- Inorder traversal of BST yields sorted order.
- Linked list is already sorted.
- Simulating inorder guarantees balance and correctness.

GeeksforGeeks:
https://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/

LeetCode:
https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

Time Complexity:
O(N)

Space Complexity:
O(H)  (recursion stack)
*/

struct ListNode {
    int data;
    ListNode* next;

    ListNode(int x) {
        data = x;
        next = NULL;
    }
};

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
    int countNodes(ListNode* head) {
        int cnt = 0;
        while (head) {
            cnt++;
            head = head->next;
        }
        return cnt;
    }

    Node* buildBST(ListNode*& head, int l, int r) {

        if (l > r) return NULL;

        int mid = l + (r - l) / 2;

        Node* leftChild = buildBST(head, l, mid - 1);

        Node* root = new Node(head->data);
        root->left = leftChild;

        head = head->next;

        root->right = buildBST(head, mid + 1, r);

        return root;
    }

    Node* sortedListToBST(ListNode* head) {

        int n = countNodes(head);
        return buildBST(head, 0, n - 1);
    }
};
