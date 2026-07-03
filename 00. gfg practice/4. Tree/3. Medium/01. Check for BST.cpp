/*
    Problem Name: Check for BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree. Check whether it is a BST or not.
    A BST is defined as follows:
    - The left subtree of a node contains only nodes with data less than the node's data.
    - The right subtree of a node contains only nodes with data greater than the node's data.
    - Both the left and right subtrees must also be binary search trees.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    1. A simple and elegant way to check if a tree is a BST is to define a valid range (min and max limit) for every node.
    2. The root node can have any value from -infinity to +infinity.
    3. When we go to the left child, its value must be strictly smaller than its parent's value. So, its maximum allowed limit becomes the parent's data.
    4. When we go to the right child, its value must be strictly greater than its parent's value. So, its minimum allowed limit becomes the parent's data.
    5. We use a simple helper recursive function `solve(root, minVal, maxVal)`. 
       - If the current node's data is out of bounds (<= minVal or >= maxVal), we return false!
       - Otherwise, we recursively check the left and right subtrees with updated ranges.
    6. Since node values can go up to 10^9, we use `long long` limits (`LONG_MIN` and `LONG_MAX`) to prevent any overflow or boundary failures.
*/

#include <iostream>
#include <climits>

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
    bool solve(Node* root, long long minVal, long long maxVal) {
        // Base case: an empty tree is a valid BST
        if (root == NULL)
            return true;
            
        // If the current node violates the range, it's not a BST
        if (root->data >= maxVal || root->data <= minVal)
            return false;
            
        // Check left and right subtrees with updated ranges
        bool leftValid = solve(root->left, minVal, root->data);
        bool rightValid = solve(root->right, root->data, maxVal);
        
        return leftValid && rightValid;
    }

public:
    // Function to check whether a Binary Tree is BST or not.
    bool isBST(Node* root) {
        // Using LONG_MIN and LONG_MAX to safely handle boundary node values up to 10^9
        return solve(root, LONG_MIN, LONG_MAX);
    }
};

int main() {
    // Example test case to verify logic
    //      2
    //     / \
    //    1   3
    //         \
    //          5
    
    Node* root = new Node(2);
    root->left = new Node(1);
    root->right = new Node(3);
    root->right->right = new Node(5);
    
    Solution ob;
    if (ob.isBST(root)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    
    return 0;
}
