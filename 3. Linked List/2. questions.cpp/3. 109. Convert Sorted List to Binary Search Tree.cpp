/*
LeetCode 109: Convert Sorted List to Binary Search Tree

Given the head of a singly linked list where elements are sorted in ascending order, 
convert it to a height-balanced binary search tree.

Example:
Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.
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

/*
Approach 1: Find Middle Node (Recursive)
- Find the middle node of the linked list using two pointers
- Use middle node as root
- Recursively build left subtree from left half
- Recursively build right subtree from right half
- Disconnect the list at middle to separate left and right halves

Time Complexity: O(n log n) - finding middle takes O(n), done log n times
Space Complexity: O(log n) - recursion stack

Key Insight:
- The middle element of a sorted list should be the root of BST
- Left half forms left subtree, right half forms right subtree
- This ensures the BST is height-balanced
*/

class Solution {
private:
    // Helper function to find the middle node of a linked list
    ListNode* findMiddle(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Disconnect the left half from the middle node
        if (prev != nullptr) {
            prev->next = nullptr;
        }
        
        return slow;
    }
    
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        if (head->next == nullptr) {
            return new TreeNode(head->val);
        }
        
        // Find the middle node
        ListNode* mid = findMiddle(head);
        
        // Create root with middle value
        TreeNode* root = new TreeNode(mid->val);
        
        // Recursively build left and right subtrees
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(mid->next);
        
        return root;
    }
};
