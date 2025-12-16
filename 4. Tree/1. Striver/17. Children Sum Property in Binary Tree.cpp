/*
 * Problem: Children Sum Property in Binary Tree
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/children-sum-parent/1
 *
 * Problem 1: Check if tree follows Children Sum Property
 * A tree follows Children Sum Property if for every node, the value of the node
 * equals the sum of values of its left and right children (if they exist).
 *
 * Problem 2: Convert tree to follow Children Sum Property
 * Convert a given binary tree to follow children sum property. You can only
 * increment node values, not decrement. If a node's value is less than the sum
 * of its children, increment the node. If a node's value is greater than the
 * sum of its children, increment the children (recursively).
 *
 * Example 1 (Check):
 *       10
 *      /  \
 *     4    6
 *    / \  / \
 *   2  2 3  3
 *
 * 10 = 4 + 6 ✓
 * 4 = 2 + 2 ✓
 * 6 = 3 + 3 ✓
 * Result: true (follows property)
 *
 * Approach 1: Check Property (Recursive)
 * - For each node, check if node->val == (left->val + right->val)
 * - Recursively check left and right subtrees
 *
 * Approach 2: Convert to Property (Post-order)
 * - Traverse in post-order (children before parent)
 * - If parent > sum of children, increment children
 * - If parent < sum of children, increment parent (but we can only increment)
 * - Actually: increment children if parent is greater, increment parent if parent is less
 *
 * Approach 3: Convert to Property (Bottom-up)
 * - Start from leaves and work upward
 * - Adjust values to satisfy property
 *
 * Time: O(n) - visit each node once
 * Space: O(h) - recursion stack, where h is height
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

#include <algorithm>
using namespace std;

// Solution 0: Optimal Solution - Convert to Children Sum Property (O(n) time, O(h) space)
class OptimalConvertChildrenSumPropertySolution {
public:
    void changeTree(TreeNode* root) {
        if (root == nullptr) return;

        // DOWN: Ensure children are at least as large as parent (push parent value down if needed)
        int child = 0;
        if (root->left)  child += root->left->val;
        if (root->right) child += root->right->val;

        if (child >= root->val) {
            // If children sum greater/equal, update parent
            root->val = child;
        } else {
            // Otherwise, push parent value down to children
            if (root->left) root->left->val = root->val;
            else if (root->right) root->right->val = root->val;
        }

        // Recursively process children
        changeTree(root->left);
        changeTree(root->right);

        // UP: After processing children, set current node to sum of (possibly updated) children
        int tot = 0;
        if (root->left)  tot += root->left->val;
        if (root->right) tot += root->right->val;
        if (root->left || root->right) root->val = tot;
    }
};

// Solution 1: Check if tree follows Children Sum Property (Recursive)
class CheckChildrenSumPropertySolution {
public:
    bool isChildrenSumProperty(TreeNode* root) {
        if (!root) return true;
        
        // Leaf node always satisfies the property
        if (!root->left && !root->right) {
            return true;
        }
        
        int sum = 0;
        if (root->left) sum += root->left->val;
        if (root->right) sum += root->right->val;
        
        // Check if current node satisfies property
        if (root->val != sum) {
            return false;
        }
        
        // Recursively check left and right subtrees
        return isChildrenSumProperty(root->left) && 
               isChildrenSumProperty(root->right);
    }
};

// Solution 2: Convert tree to follow Children Sum Property (Post-order)
class ConvertChildrenSumPropertyPostOrderSolution {
public:
    void convertToChildrenSumProperty(TreeNode* root) {
        if (!root) return;
        
        // Post-order traversal: process children first
        convertToChildrenSumProperty(root->left);
        convertToChildrenSumProperty(root->right);
        
        // After processing children, adjust current node
        int sum = 0;
        if (root->left) sum += root->left->val;
        if (root->right) sum += root->right->val;
        
        // If children sum is greater, increment current node
        if (sum > root->val) {
            root->val = sum;
        }
        // If current node is greater, increment children
        else if (root->val > sum && sum > 0) {
            int diff = root->val - sum;
            if (root->left) {
                root->left->val += diff;
                // Recursively fix the subtree
                convertToChildrenSumProperty(root->left);
            } else if (root->right) {
                root->right->val += diff;
                convertToChildrenSumProperty(root->right);
            }
        }
    }
};

// Solution 4: Convert with proper bottom-up approach (Recommended)
class ConvertChildrenSumPropertyBottomUpSolution {
public:
    void convertToChildrenSumProperty(TreeNode* root) {
        if (!root) return;
        
        // Post-order: process children first
        convertToChildrenSumProperty(root->left);
        convertToChildrenSumProperty(root->right);
        
        int childSum = 0;
        if (root->left) childSum += root->left->val;
        if (root->right) childSum += root->right->val;
        
        // If children sum is greater, update parent
        if (childSum > root->val) {
            root->val = childSum;
        }
        // If parent is greater, distribute excess to children
        else if (root->val > childSum) {
            if (root->left) {
                root->left->val += (root->val - childSum);
                // Recursively fix the subtree
                incrementSubtree(root->left, root->val - childSum);
            } else if (root->right) {
                root->right->val += (root->val - childSum);
                incrementSubtree(root->right, root->val - childSum);
            }
        }
    }
    
private:
    // This helper function recursively increments the leftmost child (or right child if left does not exist) 
    // by the given increment value. It is used to "push down" excess value from a parent node 
    // to its descendants so that the children sum property holds after a value update at the parent.
    void incrementSubtree(TreeNode* node, int increment) {
        if (!node) return;
        
        if (node->left) {
            node->left->val += increment;
            incrementSubtree(node->left, increment);
        } else if (node->right) {
            node->right->val += increment;
            incrementSubtree(node->right, increment);
        }
    }
};
