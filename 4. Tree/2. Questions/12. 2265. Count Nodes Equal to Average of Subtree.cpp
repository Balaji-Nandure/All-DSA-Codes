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

// Problem: Count Nodes Equal to Average of Subtree (LeetCode 2265)
// Given the root of a binary tree, return the number of nodes where the value 
// of the node equals the average of the values in its subtree.
// Note: The average is the sum of all values divided by the number of nodes (integer division).
//
// Example:
//     4
//    / \
//   8   5
//  / \   \
// 0   1   6
// Node 4: average = (4+8+5+0+1+6)/6 = 24/6 = 4 ✓
// Node 5: average = (5+6)/2 = 11/2 = 5 ✓
//
// Approach: DFS with subtree information
// 1. For each node, calculate:
//    - Sum of all values in its subtree
//    - Count of all nodes in its subtree
// 2. Check if node's value equals average (sum / count)
// 3. Return both sum and count to parent for its calculation
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        int count = 0;
        dfs(root, count);
        return count;
    }
    
private:
    // Returns {sum of subtree, count of nodes in subtree}
    pair<int, int> dfs(TreeNode* node, int& count) {
        if (!node) return {0, 0};
        
        // Get sum and count from left and right subtrees
        auto [leftSum, leftCount] = dfs(node->left, count);
        auto [rightSum, rightCount] = dfs(node->right, count);
        
        // Calculate sum and count for current subtree
        int totalSum = leftSum + rightSum + node->val;
        int totalCount = leftCount + rightCount + 1;
        
        // Check if current node's value equals average of its subtree
        int average = totalSum / totalCount;
        if (node->val == average) {
            count++;
        }
        
        return {totalSum, totalCount};
    }
};



