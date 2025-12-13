/*
LeetCode 1721: Swapping Nodes in a Linked List

You are given the head of a linked list, and an integer k.
Return the head of the linked list after swapping the values of the kth node 
from the beginning and the kth node from the end (the list is 1-indexed).

Example:
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]
Explanation: We swap the values of node 2 (value 2) and node 4 (value 4).
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
public:
    ListNode* swapNodes(ListNode* head, int k) {
        // Find the length of the linked list
        int length = 0;
        ListNode* current = head;
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        
        // Find kth node from beginning (1-indexed)
        ListNode* first = head;
        for (int i = 1; i < k; i++) {
            first = first->next;
        }
        
        // Find kth node from end (which is (length - k + 1)th from beginning)
        ListNode* second = head;
        for (int i = 1; i < length - k + 1; i++) {
            second = second->next;
        }
        
        // Swap the values
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
        
        return head;
    }
};

// Approach 2: One Pass (More Efficient)
class Solution2 {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode* first = nullptr;
        ListNode* second = nullptr;
        ListNode* current = head;
        
        // Traverse the list once
        int count = 0;
        while (current != nullptr) {
            count++;
            
            // When we reach kth node, store it
            if (count == k) {
                first = current;
                second = head; // initialize second pointer to head
            }
            
            // if count is greater than k, move second pointer to next node
            if (count > k) {
                second = second->next;
            } 
            
            current = current->next;
        }
        
        // Swap values
        swap(first->val, second->val);
        
        return head;
    }
};

/*
Approach 1: Two Pass
- First pass: Calculate the length of the list
- Find kth node from beginning (at position k)
- Find kth node from end (at position length - k + 1 from beginning)
- Swap the values of both nodes

Time Complexity: O(n) - two passes through the list
Space Complexity: O(1)

Approach 2: One Pass (More Efficient)
- Use two pointers: one to find kth node from beginning, 
  another to find kth node from end
- When we reach kth node, start moving the second pointer from head
- By the time we reach the end, second pointer will be at kth node from end
- Swap the values

Time Complexity: O(n) - single pass through the list
Space Complexity: O(1)

Key Insight:
- kth node from end = (length - k + 1)th node from beginning
- We can find both nodes in a single pass using two pointers
- Since we only need to swap values (not nodes), we just swap the values

Example Walkthrough:
Input: [1,2,3,4,5], k = 2
- kth from beginning: node at position 2 (value 2)
- kth from end: node at position 5-2+1 = 4 (value 4)
- Swap: [1,4,3,2,5]
*/

