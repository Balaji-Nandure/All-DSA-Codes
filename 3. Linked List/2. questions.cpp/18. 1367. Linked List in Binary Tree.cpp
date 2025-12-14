/*
LeetCode 1367: Linked List in Binary Tree

Given a binary tree root and a linked list with head as the first node.
Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
In this context downward path means a path starting at some node and going downwards.

Example:
Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: Nodes in blue form a subpath in the tree.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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

class Solution {
private:
    // Helper function to check if linked list exists starting from a tree node
    bool dfs(TreeNode* root, ListNode* head) {
        // Step 1:
        // Base case: if we've matched all nodes in the linked list
        // This means we found the complete path
        if (head == nullptr) {
            return true;
        }
        
        // Step 2:
        // Base case: if tree node is null but linked list still has nodes
        // This means we couldn't find a complete path
        if (root == nullptr) {
            return false;
        }
        
        // Step 3:
        // Check if current tree node value matches current linked list node value
        if (root->val != head->val) {
            return false;
        }
        
        // Step 4:
        // If values match, continue matching the rest of the linked list
        // Try both left and right children
        return dfs(root->left, head->next) || dfs(root->right, head->next);
    }
    
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        // Step 1:
        // Base case: if linked list is empty, it exists (trivially)
        if (head == nullptr) {
            return true;
        }
        
        // Step 2:
        // Base case: if tree is empty but linked list is not, it doesn't exist
        if (root == nullptr) {
            return false;
        }
        
        // Step 3:
        // Check if the linked list exists starting from current tree node
        // This uses DFS to match the linked list path
        if (dfs(root, head)) {
            return true;
        }
        
        // Step 4:
        // If not found starting from current node, try starting from left and right children
        // This allows us to check all possible starting points in the tree
        return isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};

/*
Approach: DFS with Two-Level Recursion
- Outer recursion: Check if linked list exists starting from any node in the tree
- Inner recursion (dfs): Check if linked list exists as a downward path from a specific tree node
- For each tree node, try to match the entire linked list starting from that node
- If not found, recursively check left and right subtrees

Time Complexity: O(n * m) - where n is number of tree nodes, m is length of linked list
Space Complexity: O(h) - where h is height of tree (recursion stack)

Key Insight:
- We need to check if the linked list exists starting from ANY node in the tree
- Once we find a starting point, we need to match the entire linked list going downward
- Two-level recursion: outer checks all starting points, inner checks path from a point
- The path must be continuous downward (parent to child)

Example Walkthrough:
Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Step 1: Check starting from root (1): doesn't match 4
Step 2: Check starting from root->left (4): matches 4, check dfs(4, [2,8])
  - dfs(4, [2,8]): 4 != 2, return false
Step 3: Check starting from root->right (4): matches 4, check dfs(4, [2,8])
  - dfs(4, [2,8]): 4 != 2, return false
Step 4: Check starting from root->left->left (2): matches 4? No, continue
Step 5: Check starting from root->left->right (2): matches 4? No, continue
Step 6: Eventually find path: 4 -> 2 -> 8
Output: true
*/

