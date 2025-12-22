/*
 * Problem: Delete Node in a Linked List
 *
 * LeetCode 237: Delete Node in a Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1
 *
 * There is a singly-linked list head and we want to delete a node node in it.
You are given the node to be deleted node. You will not be given access to the first node of head.
All the values of the linked list are unique, and it is guaranteed that the given node node is not the last node in the linked list.
Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:
- The value of the given node should not exist in the linked list.
- The number of nodes in the linked list should decrease by one.
- All the values before node should be in the same order.
- All the values after node should be in the same order.

Example:
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(nullptr) {}
 * };
 */

/*
 * Problem: Delete Node in a Linked List
 *
 * LeetCode 237: Delete Node in a Linked List
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1
 *
 * Delete a node when only that node is given (no access to head).
 * We can't delete the node directly, so we copy next node's value and delete next.
 *
 * Time: O(1) - constant time operation
 * Space: O(1)
 */

class Solution {
public:
    void deleteNode(ListNode* node) {
        // Since we don't have access to head, we can't traverse from beginning
        // Instead, copy next node's value to current node, then delete next node
        // This effectively "deletes" the given node
        
        // Copy value from next node to current node
        node->val = node->next->val;
        
        // Store next node to delete it
        ListNode* temp = node->next;
        
        // Bypass next node: point current to node after next
        node->next = node->next->next;
        
        // Delete the next node (good practice)
        delete temp;
    }
};

/*
Approach:
- We don't have access to the head of the list, only the node to be deleted
- We can't delete the current node directly, but we can copy the next node's value
- Then we delete the next node instead
- This effectively "deletes" the given node

Time Complexity: O(1)
Space Complexity: O(1)

Example:
Input: head = [4,5,1,9], node = 5
- Copy value 1 to node 5: [4,1,1,9]
- Point node 5 to node 9: [4,1,9]
- Delete the duplicate node 1
Result: [4,1,9]
*/

