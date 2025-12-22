/*
 * Problem: Lowest Common Ancestor in a Binary Search Tree (BST)
 *
 * LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-bst/1
 *
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two
 * given nodes in the BST.
 *
 * The lowest common ancestor is defined between two nodes p and q as the lowest
 * node in T that has both p and q as descendants (where we allow a node to be a
 * descendant of itself).
 *
 * Because this is a BST, we can use the BST property to guide the search:
 * - If both p and q are smaller than root, LCA lies in the left subtree.
 * - If both p and q are greater than root, LCA lies in the right subtree.
 * - Otherwise, root is the LCA (either p and q are on different sides, or one is root).
 *
 * Example:
 *       6
 *      / \
 *     2   8
 *    / \ / \
 *   0  4 7  9
 *     / \
 *    3   5
 *
 * LCA(2, 8) = 6
 * LCA(2, 4) = 2
 *
 * Approach 1: Recursive Using BST Property
 * - Compare p->val and q->val with root->val
 * - Recurse left if both are smaller, right if both are greater
 * - Otherwise, return root
 *
 * Approach 2: Iterative Using BST Property
 * - Same logic as recursive but in a loop (O(1) space)
 *
 * Approach 3: Normalize Values (minVal, maxVal)
 * - Let low = min(p->val, q->val), high = max(p->val, q->val)
 * - Move root down until low <= root->val <= high
 * - That root is the LCA
 *
 * Time: O(h) where h is the height of the tree
 * - O(log n) for balanced BST
 * - O(n) for skewed BST
 * Space: O(h) for recursive, O(1) for iterative
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution 1: Recursive Using BST Property
class RecursiveSolution {
public:
/*
 * Problem: Lowest Common Ancestor in Binary Search Tree
 *
 * LeetCode 235: Lowest Common Ancestor of a Binary Search Tree
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/lowest-common-ancestor-in-a-bst/1
 *
 * Find LCA of two nodes in BST using BST property.
 * If both < root, LCA in left; if both > root, LCA in right; else root is LCA.
 *
 * Time: O(h) - where h is height
 * Space: O(1) for iterative, O(h) for recursive
 */

    // Recursive: Use BST property to navigate
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        
        // Both nodes < root: LCA in left subtree
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        
        // Both nodes > root: LCA in right subtree
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        
        // Split point: root is LCA (nodes on different sides or one is root)
        return root;
    }
};

// Solution 2: Iterative Using BST Property (O(1) space)
class IterativeSolution {
public:
    // Iterative: O(1) space, same logic
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* current = root;
        
        while (current != NULL) {
            // Both < current: go left
            if (p->val < current->val && q->val < current->val) {
                current = current->left;
            } 
            // Both > current: go right
            else if (p->val > current->val && q->val > current->val) {
                current = current->right;
            } 
            // Split point: current is LCA
            else {
                return current;
            }
        }
        
        return NULL;
    }
};