/*
 * Problem: Floor in a Binary Search Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/floor-in-bst/1
 *
 * Given a Binary Search Tree and a number X, find Floor of X.
 * Floor(X) is a number that is either equal to X or is immediately smaller than X.
 * If Floor doesn't exist, return -1.
 *
 * Example:
 * Input:
 *       8
 *      / \
 *     4   12
 *    / \  / \
 *   2   6 10 14
 *
 * X = 5
 * Output: 4 (largest value <= 5)
 *
 * X = 6
 * Output: 6 (exact match)
 *
 * X = 1
 * Output: -1 (no value <= 1)
 *
 * BST Property:
 * - Left subtree contains nodes with values < root
 * - Right subtree contains nodes with values > root
 *
 * Approach 1: Recursive
 * - If root is NULL, return -1
 * - If root->val == X, return root->val
 * - If root->val > X, search in left subtree
 * - If root->val < X, floor might be root or in right subtree
 *
 * Approach 2: Iterative
 * - Traverse down the tree
 * - Keep track of potential floor value
 * - Update floor when we find a value <= X
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

// Solution 1: Recursive Approach
class RecursiveSolution {
public:
/*
 * Problem: Floor in Binary Search Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/floor-in-bst/1
 *
 * Find largest value <= X in BST.
 * Floor(X) = largest value <= X, or -1 if not found.
 *
 * Time: O(h) - where h is height
 * Space: O(1) for iterative, O(h) for recursive
 */

    // Recursive: Track potential floor while traversing
    int findFloor(TreeNode* root, int X) {
        if (root == NULL) return -1;
        
        // Exact match: return it
        if (root->val == X) {
            return root->val;
        }
        
        // root > X: floor must be in left subtree
        if (root->val > X) {
            return findFloor(root->left, X);
        }
        
        // root < X: floor might be root or in right subtree
        int rightFloor = findFloor(root->right, X);
        
        // Return larger valid floor (rightFloor or root)
        return (rightFloor <= X && rightFloor != -1) ? rightFloor : root->val;
    }
};

// Solution 2: Iterative Approach (O(1) space)
class IterativeSolution {
public:
    // Iterative: Track potential floor while traversing
    int findFloor(TreeNode* root, int X) {
        int floor = -1;
        TreeNode* current = root;
        
        while (current != NULL) {
            // Exact match: return it
            if (current->val == X) {
                return current->val;
            }
            
            // current < X: potential floor, try to find larger in right
            if (current->val < X) {
                floor = current->val;
                current = current->right;
            } else {
                // current > X: floor must be in left subtree
                current = current->left;
            }
        }
        
        return floor;
    }
};
