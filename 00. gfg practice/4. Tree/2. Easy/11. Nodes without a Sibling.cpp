/*
Problem: Nodes without a Sibling

Given the root of a Binary Tree, find all nodes that do not have a sibling. Return the nodes in increasing order.
Two nodes are considered siblings if they share the same parent.
Note: 
- The root node cannot have a parent, so it should not be included in the answer.
- If every node has a sibling, return a list containing only -1.

Constraints:
1 <= number of nodes <= 10^4
1 <= node->data <= 10^4

--------------------------------------------------

Pattern:
Tree Traversal (DFS/BFS) + Sorting

--------------------------------------------------

Key Observation:
- A node fundamentally lacks a sibling if and only if its parent possesses exactly one child (either exclusively left or exclusively right).
- We can perform a straightforward traversal of the entire tree. For every single node we visit, we thoughtfully check its children.
- If it has a left child but no right child, the left child has absolutely no sibling.
- If it has a right child but no left child, the right child has absolutely no sibling.
- We aggressively collect all such nodes, precisely sort them to satisfy the strict "increasing order" requirement, and return.

--------------------------------------------------

Approach:
1. Create a recursive `dfs` helper function taking the current `root` and a reference to our result vector `res`.
2. Base case: If `root` is `nullptr`, just safely return.
3. Sibling Check:
    a. If `root->left` exists and `root->right` does NOT, push `root->left->data` into `res`.
    b. If `root->right` exists and `root->left` does NOT, push `root->right->data` into `res`.
4. Recursively traverse the left and right subtrees to rigorously check all the lower levels.
5. In the main function, initialize `res` and kick off `dfs`.
6. If `res` is completely empty after the traversal completes, push `-1` into it.
7. Otherwise, sort `res` in ascending order using standard `std::sort`.
8. Return the populated `res` array.

--------------------------------------------------

Time Complexity: O(N log N) where N is the total number of nodes. Traversing the tree takes exactly O(N) time, and sorting the results takes up to O(N log N) in the absolute worst case where almost every single node has no sibling.
Space Complexity: O(N) in the worst case to explicitly store the result array and adequately accommodate the recursive DFS call stack height (up to O(N) for a perfectly skewed tree).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/print-all-nodes-that-dont-have-sibling/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

class Solution {
private:
    void dfs(Node* root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        
        // If left child exists but right doesn't, left child natively has no sibling
        if (root->left != nullptr && root->right == nullptr) {
            res.push_back(root->left->data);
        }
        
        // If right child exists but left doesn't, right child natively has no sibling
        if (root->right != nullptr && root->left == nullptr) {
            res.push_back(root->right->data);
        }
        
        // Recursively aggressively check the rest of the tree
        dfs(root->left, res);
        dfs(root->right, res);
    }

public:
    vector<int> noSibling(Node* root) {
        vector<int> res;
        dfs(root, res);
        
        // If absolutely no nodes without siblings were found
        if (res.empty()) {
            res.push_back(-1);
        } else {
            // Sort to gracefully meet the strictly increasing order constraint
            sort(res.begin(), res.end());
        }
        
        return res;
    }
};
