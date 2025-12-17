/*
 * Problem: Delete a Node in Binary Search Tree
 *
 * LeetCode 450: Delete Node in a BST
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-a-node-from-bst/1
 *
 * Given a root node reference of a BST and a key, delete the node with the given
 * key in the BST. Return the root node reference (possibly updated) of the BST.
 *
 * Example:
 * Input:
 *       5
 *      / \
 *     3   6
 *    / \   \
 *   2   4   7
 *
 * key = 3
 * Output:
 *       5
 *      / \
 *     4   6
 *    /     \
 *   2       7
 *
 * OR (using predecessor):
 *       5
 *      / \
 *     2   6
 *      \   \
 *       4   7
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 *
 * Three Cases for Deletion:
 * 1. Node has no children (leaf) - simply delete it
 * 2. Node has one child - replace node with its child
 * 3. Node has two children - replace with inorder successor/predecessor
 *
 * Approach 1: Recursive
 * - Find the node to delete
 * - Handle three cases: 0, 1, or 2 children
 * - For case 3, find inorder successor (leftmost in right subtree) or
 *   inorder predecessor (rightmost in left subtree)
 *
 * Approach 2: Iterative
 * - Traverse to find the node and its parent
 * - Handle deletion cases
 *
 * Time: O(h) where h is the height of the tree
 * - O(log n) for balanced BST
 * - O(n) for skewed BST
 * Space: O(1) for iterative, O(h) for recursive
 */

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
/* =========================================================
   LeetCode 29: Delete a Node in a Binary Search Tree
   All standard C++ solutions in ONE place
   ========================================================= */


/* ---------------------------------------------------------
   Approach 1: Recursive (Classic & Most Expected)
   ---------------------------------------------------------
   Logic:
   - Traverse BST to find key
   - 3 cases when node found:
     1) Leaf node
     2) One child
     3) Two children → replace with inorder successor
   Time: O(h)
   Space: O(h)
*/
// =========================================================
// Approach 1: Recursive (Classic & Most Expected)
// =========================================================
class SolutionRecursive {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr)
            return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Case 1 & 2: No child or one child
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Two children
            TreeNode* succ = getMin(root->right);
            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }
        return root;
    }

private:
    // Helper: Find min value node in subtree
    TreeNode* getMin(TreeNode* node) {
        while (node != nullptr && node->left != nullptr)
            node = node->left;
        return node;
    }
};

// =========================================================
// Approach 3: Recursive Using Inorder Successor
// (Explicitly shows successor replacement)
// =========================================================
class SolutionSuccessor {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root)
            return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;

            TreeNode* succ = root->right;
            while (succ->left)
                succ = succ->left;

            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }
        return root;
    }
};


// =========================================================
// Approach 4: Recursive Using Inorder Predecessor
// Replace node with maximum from left subtree
// =========================================================
class SolutionPredecessor {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root)
            return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;

            TreeNode* pred = root->left;
            while (pred->right)
                pred = pred->right;

            root->val = pred->val;
            root->left = deleteNode(root->left, pred->val);
        }
        return root;
    }
};
    