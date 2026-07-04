/*
    Problem Name: Tree Boundary Traversal
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a root of a Binary Tree, return its boundary traversal in the following order:
    1. Left Boundary: Nodes from the root to the leftmost non-leaf node, preferring the left child over the right and excluding leaves.
    2. Leaf Nodes: All leaf nodes from left to right, covering every leaf in the tree.
    3. Reverse Right Boundary: Nodes from the root to the rightmost non-leaf node, preferring the right child over the left, excluding leaves, and added in reverse order.
    Note: The root is included once, leaves are added separately to avoid repetition.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes in the tree. We traverse parts of the tree multiple times but overall it scales linearly.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack during leaf traversal and for storing the right boundary temporary array.

    Love Babbar Style Approach:
    1. The problem becomes extremely simple if we break it down strictly into three disjoint operations:
       a) Collect Left Boundary (excluding leaves)
       b) Collect all Leaves (using standard DFS)
       c) Collect Right Boundary (excluding leaves, and reversed)
    2. First, handle the root. If it's not a leaf, add it to our `ans` array immediately. (If it is a leaf, the leaf-collector will grab it later).
    3. For Left Boundary: 
       - Start from `root->left`. 
       - If it's not a leaf, push it. 
       - Always prefer going left (`curr->left`). If left doesn't exist, ONLY then go right (`curr->right`).
    4. For Leaves: 
       - Simple recursive Pre-order traversal. If a node is a leaf, push it to `ans`.
    5. For Right Boundary: 
       - Start from `root->right`. 
       - If it's not a leaf, push it to a temporary array `temp`. 
       - Always prefer going right (`curr->right`). If right doesn't exist, ONLY then go left (`curr->left`).
       - Finally, iterate `temp` backwards and push all its elements to `ans` to effectively get the reverse order!

    Dry Run:
    Tree:
            1
             \
              2
               \
                3
                 \
                  4
    - Root 1: Not a leaf. ans = [1]
    - Left Boundary: root->left is NULL. Does nothing.
    - Leaves: DFS finds node 4 as the only leaf. ans = [1, 4]
    - Right Boundary: Start at 2. 2 is not leaf -> temp=[2], go right to 3.
      3 is not leaf -> temp=[2, 3], go right to 4. 4 is leaf, loop ends.
      Reverse temp -> [3, 2]. Add to ans.
      
    Final Answer = [1, 4, 3, 2]. Matches perfectly!
*/

#include <iostream>
#include <vector>

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
    // Helper function to check if a node is a leaf
    bool isLeaf(Node* root) {
        return (root->left == NULL && root->right == NULL);
    }
    
    // Helper function to collect all leaves from left to right
    void traverseLeaves(Node* root, vector<int>& ans) {
        if (root == NULL) return;
        
        if (isLeaf(root)) {
            ans.push_back(root->data);
            return;
        }
        
        traverseLeaves(root->left, ans);
        traverseLeaves(root->right, ans);
    }

public:
    vector<int> boundary(Node* root) {
        vector<int> ans;
        if (root == NULL) return ans;
        
        // Add root if it's not a leaf
        if (!isLeaf(root)) {
            ans.push_back(root->data);
        }
        
        // 1. Traverse Left Boundary
        Node* curr = root->left;
        while (curr) {
            if (!isLeaf(curr)) {
                ans.push_back(curr->data);
            }
            if (curr->left) {
                curr = curr->left; // Prefer left child
            } else {
                curr = curr->right; // Fallback to right child
            }
        }
        
        // 2. Traverse all Leaf Nodes
        traverseLeaves(root, ans);
        
        // 3. Traverse Right Boundary
        curr = root->right;
        vector<int> temp; // Temporary array to hold right boundary for reversing
        while (curr) {
            if (!isLeaf(curr)) {
                temp.push_back(curr->data);
            }
            if (curr->right) {
                curr = curr->right; // Prefer right child
            } else {
                curr = curr->left; // Fallback to left child
            }
        }
        
        // Add right boundary to ans in reverse order
        for (int i = temp.size() - 1; i >= 0; i--) {
            ans.push_back(temp[i]);
        }
        
        return ans;
    }
};

int main() {
    // Example test case (Right skewed tree)
    //    1
    //     \
    //      2
    //       \
    //        3
    //         \
    //          4
    
    Node* root = new Node(1);
    root->right = new Node(2);
    root->right->right = new Node(3);
    root->right->right->right = new Node(4);
    
    Solution ob;
    vector<int> res = ob.boundary(root);
    
    for (int x : res) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}
