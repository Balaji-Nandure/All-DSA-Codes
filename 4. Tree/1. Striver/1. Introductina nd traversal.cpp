/*
 * Topic: Binary Tree Representation (Striver - Trees)
 *
 * This file shows the basic binary tree Node structure and how to create
 * a simple tree using pointers (same as in your screenshot).
 *
 * Example tree built in main():
 *
 *        1
 *      /   \
 *     2     3
 *      \
 *       5
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

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Iterative preorder traversal
void iterativePreorder(Node* root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* node = st.top();
        st.pop();
        cout << node->data << " ";
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


void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void iterativeInorder(Node* root) {
    if (!root) return;
    stack<Node*> st;
    Node* curr = root;
    while (curr != nullptr || !st.empty()) {
        // Step 1: Go as left as possible
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }
        // Step 2: Process the node
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        // Step 3: Move to right subtree
        curr = curr->right;
    }
}

// postorder starts here
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Iterative postorder traversal using two stacks
void iterativePostorder(Node* root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();
        // Push current node to second stack
        st2.push(node);
        // Push left and right children
        if (node->left)  st1.push(node->left);
        if (node->right) st1.push(node->right);
    }
    // Second stack gives postorder
    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// Iterative postorder traversal using one stack 







// level order traversal
void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        cout << node->data << " ";
        q.pop();
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
