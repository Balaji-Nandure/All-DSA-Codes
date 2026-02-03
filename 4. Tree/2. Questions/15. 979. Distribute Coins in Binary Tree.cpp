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

// Problem: Distribute Coins in Binary Tree (LeetCode 979)
// Given the root of a binary tree with n nodes where each node has some coins,
// there are exactly n coins in total. In one move, we can choose two adjacent 
// nodes and move one coin from one node to another.
// Return the minimum number of moves required to make every node have exactly one coin.
//
// Example:
//     3
//    / \
//   0   0
// Node 0 (left) needs 1 coin from root: 1 move
// Node 0 (right) needs 1 coin from root: 1 move
// Total: 2 moves
//
// Approach: DFS with balance calculation
// 1. For each node, calculate its "balance" = coins - 1 (excess or deficit)
// 2. A node needs to pass its excess coins to parent or receive deficit from parent
// 3. The number of moves for a subtree = |balance of left| + |balance of right|
// 4. Each coin that needs to move through an edge counts as one move
// 5. Return the balance to parent so it can calculate its own balance
//
// Key Insight: 
// - If a node has 3 coins, it has 2 excess coins (balance = +2)
// - If a node has 0 coins, it needs 1 coin (balance = -1)
// - The absolute value of balance is the number of moves through that edge
//
// Time Complexity: O(n) - visit each node once
// Space Complexity: O(h) - recursion stack where h is height

class Solution {
public:
    int distributeCoins(TreeNode* root) {
        int moves = 0;
        dfs(root, moves);
        return moves;
    }
    
private:
    // Returns the balance (excess or deficit) of coins for this subtree
    // balance = total coins in subtree - number of nodes in subtree
    int dfs(TreeNode* node, int& moves) {
        if (!node) return 0;
        
        // Get balance from left and right subtrees
        int leftBalance = dfs(node->left, moves);
        int rightBalance = dfs(node->right, moves);
        
        // Add the absolute values to moves (coins moving through edges)
        moves += abs(leftBalance) + abs(rightBalance);
        
        // Return balance for current subtree
        // (coins in current node - 1) + balances from children
        return node->val - 1 + leftBalance + rightBalance;
    }
};

 