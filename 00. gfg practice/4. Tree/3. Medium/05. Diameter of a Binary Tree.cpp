/*
    Problem Name: Diameter of a Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, your task is to find the diameter of the binary tree. 
    The diameter of a binary tree is defined as the number of edges on the longest path between any two nodes. 
    Note that this path may or may not pass through the root of the tree.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit every node exactly once during the traversal.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    1. The diameter of a tree is simply the maximum value of `(left_height + right_height)` across ALL nodes in the tree.
    2. Instead of calling a separate height function for every node (which would take a slow O(N^2) time), we can heavily optimize this to O(N). We calculate the height and update the maximum diameter simultaneously in the exact same recursive call!
    3. We write a simple recursive `height` function that takes the current node and a reference variable `d` (to store our absolute max diameter).
    4. For any node, we recursively find the height of its left subtree (`lh`) and right subtree (`rh`).
    5. The longest path passing through this specific node has exactly `lh + rh` edges. We update our max diameter tracker: `d = max(d, lh + rh)`.
    6. Finally, we just return the height of the current node back up to its parent: `max(lh, rh) + 1`.

    Dry Run:
    Tree:
           1
         /
        2
       / \
      3   4

    - height(3): lh=0, rh=0. d = max(0, 0+0) = 0. returns 1.
    - height(4): lh=0, rh=0. d = max(0, 0+0) = 0. returns 1.
    - height(2): lh=1, rh=1. d = max(0, 1+1) = 2. returns 2.
    - height(1): lh=2, rh=0. d = max(2, 2+0) = 2. returns 3.
    
    Result `d` = 2 edges. Matches perfectly!
*/

#include <iostream>
#include <algorithm>

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
    int height(Node* root, int& d) {
        // Base case: null node has a height of 0
        if (root == NULL) {
            return 0;
        }
        
        // Find heights of left and right subtrees
        int lh = height(root->left, d);
        int rh = height(root->right, d);
        
        // The diameter passing through this node is lh + rh edges
        // Update the maximum diameter found so far
        d = max(d, lh + rh);
        
        // Return the height of this tree to the parent
        return max(lh, rh) + 1;
    }

public:
    // Function to return the diameter of a Binary Tree.
    int diameter(Node* root) {
        int d = 0;
        height(root, d);
        return d;
    }
};

int main() {
    // Example test case 
    //        1
    //      / 
    //     2   
    //    / \ 
    //   3   4 
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->left->left = new Node(3);
    root->left->right = new Node(4);
    
    Solution ob;
    cout << ob.diameter(root) << "\n";
    
    return 0;
}
