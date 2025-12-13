/*
LeetCode 2487: Remove Nodes From Linked List

You are given the head of a linked list.
Remove every node which has a node with a strictly greater value anywhere to the right side of it.
Return the head of the modified linked list.

Example:
Input: head = [5,2,13,3,8]
Output: [13,8]
Explanation: The nodes that should be removed are 5, 2, and 3.
- Node 13 is to the right of node 5.
- Node 13 is to the right of node 2.
- Node 8 is to the right of node 3.
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

class Solution {
private:
    // Helper function to reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
    
public:
    ListNode* removeNodes(ListNode* head) {
        // Step 1: Reverse the list
        head = reverseList(head);
        
        // Step 2: Traverse and remove nodes with value less than max seen so far
        ListNode* current = head;
        int maxVal = current->val;
        
        while (current->next != nullptr) {
            if (current->next->val < maxVal) {
                // Remove the node
                current->next = current->next->next;
            } else {
                // Update max and move forward
                maxVal = max(maxVal, current->next->val);
                current = current->next;
            }
        }
        
        // Step 3: Reverse the list back
        head = reverseList(head);
        
        return head;
    }
};

// Approach 2: Using Stack (Monotonic Stack)
class Solution2 {
public:
    ListNode* removeNodes(ListNode* head) {
        stack<ListNode*> st;
        ListNode* current = head;
        
        // Traverse the list and maintain a decreasing stack
        while (current != nullptr) {
            // Remove all nodes from stack that have value less than current
            while (!st.empty() && st.top()->val < current->val) {
                st.pop();
            }
            
            // Connect the previous node to current
            if (!st.empty()) {
                st.top()->next = current;
            } else {
                // This is the new head
                head = current;
            }
            
            st.push(current);
            current = current->next;
        }
        
        return head;
    }
};

/*
Approach 1: Reverse, Remove, Reverse Back
- Reverse the linked list so we can process from right to left
- Traverse and remove nodes with value less than the maximum seen so far
- Reverse the list back to get the original order

Time Complexity: O(n) - reverse O(n), traverse O(n), reverse back O(n)
Space Complexity: O(1) - only using constant extra space

Approach 2: Using Monotonic Stack
- Use a stack to maintain nodes in decreasing order
- For each node, remove all nodes from stack that have smaller values
- Connect the previous node (from stack) to current node
- The stack naturally maintains the nodes we want to keep

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - stack to store nodes

Key Insight:
- We need to remove nodes that have a greater value to their right
- This is equivalent to keeping only nodes that are greater than or equal to all nodes to their right
- Processing from right to left makes it easier: we can track the maximum seen so far
- Alternatively, use a monotonic stack to maintain decreasing order

Example Walkthrough:
Input: head = [5,2,13,3,8]
Step 1: Reverse -> [8,3,13,2,5]
Step 2: Traverse and remove:
  - Start: max = 8, keep 8
  - Next: 3 < 8, remove 3
  - Next: 13 > 8, keep 13, max = 13
  - Next: 2 < 13, remove 2
  - Next: 5 < 13, remove 5
  - Result: [8,13]
Step 3: Reverse back -> [13,8]
Output: [13,8]
*/

