/*
    Problem Name: Children Sum in a Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, determine whether the tree satisfies the Children Sum Property. 
    In this property, each non-leaf node must have a value equal to the sum of its left and right children's values. 
    A NULL child is considered to have a value of 0, and all leaf nodes are considered valid by default.
    Return true if every node in the tree satisfies this condition, otherwise return false.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    1. This problem is extremely straightforward because it only asks us to check the IMMEDIATE children (unlike the "Sum Tree" problem which asks for the entire subtree sum).
    2. We can easily solve this with a simple recursive DFS traversal.
    3. Base Cases:
       - If the tree is empty (`root == NULL`), it satisfies the property by default (return true).
       - If it is a leaf node (`root->left == NULL && root->right == NULL`), it also satisfies the property by default (return true).
    4. For any normal node, we gently grab the values of its left and right children. If a child is NULL, its value is just 0.
    5. We then check the core condition: Is `root->data == leftData + rightData`?
       - If NO: Instantly return false. This will short-circuit and fail the tree immediately.
    6. If YES, the current node is fine, but we still need to recursively check if both the left subtree AND the right subtree satisfy the property.

    Dry Run:
    Tree:
           35
         /    \
       20      15
      /  \    /  \
     15   5  10   5

    - Node 35: left=20, right=15. 20+15 == 35? YES. Check children.
    - Node 20: left=15, right=5. 15+5 == 20? YES. Check children.
    - Node 15 (left): leaf, returns true.
    - Node 5 (left): leaf, returns true.
    - Node 15 (right): left=10, right=5. 10+5 == 15? YES. Check children.
    - Node 10: leaf, returns true.
    - Node 5 (right): leaf, returns true.
    
    Result: True. Matches perfectly!
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
public:
    // Function to check whether all nodes of a tree have the value 
    // equal to the sum of their child nodes.
    bool isSumProperty(Node *root) {
        // Base case 1: Empty tree is valid
        if (root == NULL) {
            return true;
        }
        
        // Base case 2: Leaf node is valid by default
        if (root->left == NULL && root->right == NULL) {
            return true;
        }
        
        // Grab the values of left and right children (0 if NULL)
        int leftData = 0;
        int rightData = 0;
        
        if (root->left) {
            leftData = root->left->data;
        }
        if (root->right) {
            rightData = root->right->data;
        }
        
        // If current node violates the rule, instantly return false
        if (root->data != leftData + rightData) {
            return false;
        }
        
        // Recursively check if both left and right subtrees are also valid
        return isSumProperty(root->left) && isSumProperty(root->right);
    }
};

int main() {
    // Example test case 
    //        35
    //      /    \ 
    //    20      15   
    //   /  \    /  \
    // 15    5  10   5
    
    Node* root = new Node(35);
    root->left = new Node(20);
    root->right = new Node(15);
    
    root->left->left = new Node(15);
    root->left->right = new Node(5);
    
    root->right->left = new Node(10);
    root->right->right = new Node(5);
    
    Solution ob;
    if (ob.isSumProperty(root)) {
        cout << "True\n";
    } else {
        cout << "False\n";
    }
    
    return 0;
}
