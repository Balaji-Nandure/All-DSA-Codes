/*
Problem:
Convert a Given Binary Tree to a Doubly Linked List (DLL) in Linear Time

Given the root of a Binary Tree,
convert it into a Doubly Linked List (DLL) in-place.

Rules:
- The DLL should follow INORDER traversal of the Binary Tree.
- Left pointer of a tree node should act as "prev".
- Right pointer of a tree node should act as "next".
- Do NOT create new nodes.
- Conversion must be done in O(n) time.

Examples:

Binary Tree:
        10
       /  \
     12    15
    /  \
   25   30

DLL (Inorder):
25 <-> 12 <-> 30 <-> 10 <-> 15


-----------------------------------
Approach (Expected / Optimal – Inorder Traversal with Prev Pointer):
-----------------------------------
Key Insight:
- Inorder traversal of a Binary Tree gives the correct order for DLL.
- While traversing:
    • Maintain a pointer `prev` to track previous processed node.
    • Connect current node with `prev`.

Steps:
1. Do inorder traversal (Left → Root → Right).
2. For each visited node:
   - If prev is NULL → this node is the head of DLL.
   - Else:
       prev->right = curr
       curr->left  = prev
3. Update prev = curr.
4. After traversal, head points to the DLL head.

Why this works:
- Each node is visited exactly once → O(n)
- No extra data structures used.
- Pointers reused in-place.

Time Complexity:
O(n)

Space Complexity:
O(h)   (recursion stack, h = tree height)


GeeksforGeeks:
https://www.geeksforgeeks.org/convert-binary-tree-to-doubly-linked-list-by-setting-left-and-right-pointers/

LeetCode:
No direct equivalent problem.
(Related to tree inorder traversal)
*/


// Definition for Binary Tree node
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


// Helper function for inorder traversal
void inorder(Node* curr, Node*& prev, Node*& head) {

    if (curr == NULL) {
        return;
    }

    // Left subtree
    inorder(curr->left, prev, head);

    // Process current node
    if (prev == NULL) {
        // First node (leftmost) becomes DLL head
        head = curr;
    } else {
        prev->right = curr;
        curr->left = prev;
    }

    prev = curr;

    // Right subtree
    inorder(curr->right, prev, head);
}


// Main conversion function
Node* binaryTreeToDLL(Node* root) {

    Node* head = NULL;
    Node* prev = NULL;

    inorder(root, prev, head);

    return head;
}
