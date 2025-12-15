/*
 * Problem: Children Sum Property in Binary Tree
 *
 * GeeksforGeeks: https://www.geeksforgeeks.org/check-for-children-sum-property-in-a-binary-tree/
 * GeeksforGeeks (Convert): https://www.geeksforgeeks.org/convert-an-arbitrary-binary-tree-to-a-tree-that-holds-children-sum-property/
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

// Solution 3: Convert tree to follow Children Sum Property (Bottom-up with increment only)
class ConvertChildrenSumPropertyIncrementOnlySolution {
public:
    void convertToChildrenSumProperty(TreeNode* root) {
        if (!root) return;
        
        int childSum = 0;
        if (root->left) childSum += root->left->val;
        if (root->right) childSum += root->right->val;
        
        // If children sum is greater than parent, increment parent
        if (childSum > root->val) {
            root->val = childSum;
        }
        // If parent is greater than children sum, increment children
        else if (root->val > childSum) {
            if (root->left) root->left->val = root->val;
            if (root->right) root->right->val = root->val;
        }
        
        // Recursively process children
        convertToChildrenSumProperty(root->left);
        convertToChildrenSumProperty(root->right);
        
        // After processing children, update current node again
        childSum = 0;
        if (root->left) childSum += root->left->val;
        if (root->right) childSum += root->right->val;
        
        // If children were updated, update parent
        if (root->left || root->right) {
            root->val = childSum;
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

// Solution 5: Simple conversion (increment children if needed)
class SimpleConvertChildrenSumPropertySolution {
public:
    void convertToChildrenSumProperty(TreeNode* root) {
        if (!root || (!root->left && !root->right)) {
            return; // Leaf node or null
        }
        
        // Recursively process children first
        convertToChildrenSumProperty(root->left);
        convertToChildrenSumProperty(root->right);
        
        int childSum = 0;
        if (root->left) childSum += root->left->val;
        if (root->right) childSum += root->right->val;
        
        // If children sum is greater, update parent
        if (childSum > root->val) {
            root->val = childSum;
        }
        // If parent is greater, increment children equally
        else if (root->val > childSum) {
            int diff = root->val - childSum;
            if (root->left) {
                root->left->val += diff;
            } else if (root->right) {
                root->right->val += diff;
            }
        }
    }
};
