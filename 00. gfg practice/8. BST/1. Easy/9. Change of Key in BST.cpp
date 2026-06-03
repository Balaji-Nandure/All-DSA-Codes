/*
GeeksforGeeks: Change of Key in BST
Difficulty: Easy

Problem:
Given a Binary Search Tree, change an old key value present in the tree to the given new key value.

Example 1:
Input: Root of below tree
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 
     Old key value:  40
     New key value:  10

Output: BST should be modified to following
              50
           /     \
          30      70
         /       /  \
       20      60   80  
       /
     10

Core Idea:
In a Binary Search Tree, simply replacing the `oldVal` with `newVal` in the node could violate the BST structural property (where left subtree elements are strictly smaller and right subtree elements are strictly greater than the root). 
For example, changing 40 to 10 means 10 is no longer greater than 30, completely violating the tree's order constraints.
Therefore, a "change key" operation in a BST is universally accomplished through two standard operations:
1. Delete the node containing `oldVal` from the BST.
2. Insert a new node containing `newVal` into the BST.
This ensures the BST properties are flawlessly maintained.

Approach:
1. Implement a standard `deleteNode(root, key)` function for a BST:
   - Search for the key.
   - If found, handle the 3 deletion cases: 0 children (leaf), 1 child, or 2 children.
   - For 2 children, find the inorder successor (smallest value in the right subtree), replace the node's value with it, and delete the inorder successor.
2. Implement a standard recursive `insert(root, key)` function for a BST.
3. In `changeKey(root, oldVal, newVal)`:
   - Call `root = deleteNode(root, oldVal)`.
   - Call `root = insert(root, newVal)`.
   - Return `root`.

Time Complexity: O(H) where H is the height of the tree. Both deletion and insertion take O(H) time.
Space Complexity: O(H) auxiliary space for the recursion stack during deletion and insertion.

GFG Link: https://www.geeksforgeeks.org/problems/change-of-key-in-bst/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
private:
    Node* minValueNode(Node* node) {
        Node* current = node;
        // Loop down to find the leftmost leaf
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr) return root;

        // If the key to be deleted is smaller than the root's key, then it lies in left subtree
        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        }
        // If the key to be deleted is greater than the root's key, then it lies in right subtree
        else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        }
        // If key is same as root's key, then This is the node to be deleted
        else {
            // Node with only one child or no child
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's content to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* insert(Node* root, int key) {
        // If the tree is empty, return a new node
        if (root == nullptr) return new Node(key);

        // Otherwise, recur down the tree
        if (key < root->data) {
            root->left = insert(root->left, key);
        } else if (key > root->data) {
            root->right = insert(root->right, key);
        }
        
        // Return the (unchanged) node pointer
        return root;
    }

public:
    Node *changeKey(Node *root, int oldVal, int newVal) {
        // Step 1: Delete old value from the tree
        root = deleteNode(root, oldVal);
        
        // Step 2: Insert new value into the tree
        root = insert(root, newVal);
        
        return root;
    }
};

/*
Dry Run — Example 1:
Input: oldVal = 40, newVal = 10
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 

1. Call changeKey(root, 40, 10).
2. deleteNode(root, 40) is called.
   - 40 < 50 -> left
   - 40 > 30 -> right
   - 40 == 40 -> match found!
   - Node(40) is a leaf node (left and right are NULL).
   - returns NULL to 30's right. Node(40) is deleted.
   
   Tree becomes:
              50
           /     \
          30      70
         /       /  \
       20       60   80 

3. insert(root, 10) is called.
   - 10 < 50 -> left
   - 10 < 30 -> left
   - 10 < 20 -> left
   - 20's left is NULL, creates Node(10) and attaches it to 20's left.
   
   Tree becomes:
              50
           /     \
          30      70
         /       /  \
       20      60   80 
       /
     10

4. Returns the modified root (50).

Output structure matches the expected modified BST.
*/
