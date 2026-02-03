/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Problem: Construct Binary Tree from Preorder and Postorder Traversal (LeetCode 889)
// Given two integer arrays, preorder and postorder where preorder is the preorder 
// traversal of a binary tree of distinct values and postorder is the postorder 
// traversal of the same tree, reconstruct and return the binary tree.
// If there exist multiple answers, you can return any of them.
//
// Example:
// preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
//       1
//      / \
//     2   3
//    / \ / \
//   4  5 6  7
// Approach 2: Iterative with Stack
// Use stack to track parent nodes while building the tree

// Approach 2: Iterative with Stack
// Key Insights:
// 1. Preorder: root -> left -> right (process nodes in this order)
// 2. Postorder: left -> right -> root (nodes appear in this order when subtrees complete)
// 3. Use stack to track potential parent nodes
// 4. When a node in preorder matches postorder[j], it means that subtree is complete
// 5. First child goes to left, second child goes to right
//
// Algorithm:
// 1. Create root from preorder[0] and push to stack
// 2. For each remaining node in preorder:
//    a) Create new node
//    b) Pop completed subtrees (nodes matching postorder)
//    c) Attach new node as left child (if empty) or right child
//    d) Push new node to stack
// 3. Return root
//
// Time Complexity: O(n) - process each node once
// Space Complexity: O(n) - stack can hold up to n nodes

class Solution2 {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        stack<TreeNode*> st;
        TreeNode* root = new TreeNode(preorder[0]);
        st.push(root);
        
        int j = 0; // postorder index
        
        for (int i = 1; i < preorder.size(); i++) {
            TreeNode* node = new TreeNode(preorder[i]);
            
            // Pop nodes from stack if they match postorder
            // This means their subtrees are complete
            while (!st.empty() && st.top()->val == postorder[j]) {
                st.pop();
                j++;
            }
            
            // Attach node to the top of stack
            // First child becomes left, second child becomes right
            if (!st.top()->left) {
                st.top()->left = node;
            } else {
                st.top()->right = node;
            }
            
            st.push(node);
        }
        
        return root;
    }
};

// Approach 3: Recursive Solution
// Key Insight:
// - preorder[0] is the root
// - preorder[1] is the left subtree root (if exists)
// - Find preorder[1] in postorder to determine left subtree size
// - Recursively build left and right subtrees
//
// Algorithm:
// 1. Base case: if preorder is empty, return nullptr
// 2. Create root from preorder[0]
// 3. If only one node, return root
// 4. Find preorder[1] (left child) in postorder to get left subtree size
// 5. Recursively build left subtree using:
//    - preorder[1...1+leftSize]
//    - postorder[0...leftSize-1]
// 6. Recursively build right subtree using:
//    - preorder[1+leftSize...end]
//    - postorder[leftSize...end-1]
// 7. Return root
//
// Time Complexity: O(n²) - finding in postorder takes O(n) for each node
// Space Complexity: O(n) - recursion stack

class Solution3 {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        return build(preorder, 0, preorder.size() - 1, 
                    postorder, 0, postorder.size() - 1);
    }
    
private:
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                   vector<int>& postorder, int postStart, int postEnd) {
        // Base case: empty range
        if (preStart > preEnd) return nullptr;
        
        // Create root from first element of preorder
        TreeNode* root = new TreeNode(preorder[preStart]);
        
        // If only one node, return it
        if (preStart == preEnd) return root;
        
        // Find left subtree root (preorder[preStart + 1]) in postorder
        int leftRootVal = preorder[preStart + 1];
        int leftRootIdx = postStart;
        while (postorder[leftRootIdx] != leftRootVal) {
            leftRootIdx++;
        }
        
        // Calculate left subtree size
        int leftSize = leftRootIdx - postStart + 1;
        
        // Recursively build left subtree
        root->left = build(preorder, preStart + 1, preStart + leftSize,
                          postorder, postStart, leftRootIdx);
        
        // Recursively build right subtree
        root->right = build(preorder, preStart + leftSize + 1, preEnd,
                           postorder, leftRootIdx + 1, postEnd - 1);
        
        return root;
    }
};

