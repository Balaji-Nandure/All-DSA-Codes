/*
 * Problem: Introduction to Binary Trees and Traversals
 *
 * Basic binary tree structure and traversal methods:
 * - Preorder: Root -> Left -> Right
 * - Inorder: Left -> Root -> Right
 * - Postorder: Left -> Right -> Root
 * - Level Order: Level by level (BFS)
 *
 * Time: O(n) for all traversals
 * Space: O(h) for recursive, O(n) for iterative (stack/queue)
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Preorder Traversal: Root -> Left -> Right
void preorder(Node* root) {
    // Base case: empty tree
    if (!root) return;
    // Action: Process root first
    cout << root->data << " ";
    // Recurse: Left subtree, then right subtree
    preorder(root->left);
    preorder(root->right);
}

// Iterative Preorder: Use stack (push right first, then left)
void iterativePreorder(Node* root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* node = st.top();
        st.pop();
        cout << node->data << " "; // Process root
        // Push right first, then left (so left is processed first)
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}

// Iterative inorder traversal using queue
void iterativeInorder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}


// Inorder Traversal: Left -> Root -> Right
void inorder(Node* root) {
    // Base case: empty tree
    if (!root) return;
    // Recurse: Left subtree first
    inorder(root->left);
    // Action: Process root
    cout << root->data << " ";
    // Recurse: Right subtree
    inorder(root->right);
}

// Iterative Inorder: Use stack to go left, process, then go right
void iterativeInorder(Node* root) {
    if (!root) return;
    stack<Node*> st;
    Node* curr = root;
    while (curr != nullptr || !st.empty()) {
        // Step 1: Go as left as possible, pushing all nodes
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        // Step 2: Process node (leftmost unprocessed)
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        // Step 3: Move to right subtree
        curr = curr->right;
    }
}

// Postorder Traversal: Left -> Right -> Root
void postorder(Node* root) {
    // Base case: empty tree
    if (!root) return;
    // Recurse: Left subtree first
    postorder(root->left);
    // Recurse: Right subtree
    postorder(root->right);
    // Action: Process root last
    cout << root->data << " ";
}

// Iterative Postorder: Use two stacks
// Push to st1, pop and push to st2, then pop from st2 gives postorder
void iterativePostorder(Node* root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);
    // Process nodes: root -> right -> left in st1
    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();
        // Push to st2 (will be processed in reverse order)
        st2.push(node);
        // Push left first, then right (so right is on top in st2)
        if (node->left)  st1.push(node->left);
        if (node->right) st1.push(node->right);
    }
    // Pop from st2 gives postorder (Left -> Right -> Root)
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Iterative postorder traversal using one stack 







// Level Order Traversal (BFS): Process level by level using queue
void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        cout << node->data << " "; // Process node
        q.pop();
        // Add children to queue for next level
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

int main() {
    // Same construction as the screenshot
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);

    cout << "Preorder: ";
    preorder(root);
    cout << "\nInorder: ";
    inorder(root);
    cout << "\n";
    cout << "Postorder: ";
    postorder(root);
    cout << "\nLevel Order: ";
    levelOrder(root);
    cout << "\n";

    return 0;
}
