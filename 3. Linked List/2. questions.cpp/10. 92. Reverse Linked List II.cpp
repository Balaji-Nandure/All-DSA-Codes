/*
LeetCode 92: Reverse Linked List II

Given the head of a singly linked list and two integers left and right where left <= right, 
reverse the nodes of the list from position left to position right, and return the reversed list.

Example:
Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Explanation: Reverse nodes from position 2 to 4: [1,2,3,4,5] -> [1,4,3,2,5]
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
/*
 * Problem: Reverse Linked List II
 *
 * LeetCode 92: Reverse Linked List II
 *
 * Reverse nodes from position left to right (1-indexed).
 * Example: [1,2,3,4,5], left=2, right=4 -> [1,4,3,2,5]
 *
 * Time: O(n) - single pass
 * Space: O(1)
 */

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // Dummy node handles edge case (left = 1)
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // Find node before reversal starts (at position left-1)
        ListNode* prev = dummy;
        for (int i = 1; i < left; i++) {
            prev = prev->next;
        }
        
        // Start reversing from prev->next
        ListNode* current = prev->next;
        ListNode* next = nullptr;
        ListNode* reversePrev = nullptr;  // Previous node in reversed sublist
        ListNode* tail = current;  // Tail of reversed sublist (will be at left position)
        
        // Reverse sublist from left to right
        for (int i = 0; i < right - left + 1; i++) {
            next = current->next;        // Save next
            current->next = reversePrev; // Reverse link
            reversePrev = current;        // Move reversePrev forward
            current = next;              // Move current forward
        }
        
        // Connect: prev -> new head of reversed sublist
        // tail -> node after right position
        prev->next = reversePrev;  // Connect before reversed part
        tail->next = current;      // Connect after reversed part
        
        return dummy->next;
    }
};

/*
Approach: Standard Reversal Technique
- Use dummy node to handle edge case (left = 1)
- Find the node before the reversal starts (prev)
- Use standard reversal technique with three pointers:
  - reversePrev: tracks the previous node in the reversed sublist
  - current: current node being processed
  - next: next node to process
- After reversal, connect:
  - prev->next to the new head of reversed sublist (reversePrev)
  - tail of reversed sublist to the node after right position (current)

Time Complexity: O(n) - single pass through the list
Space Complexity: O(1) - only using constant extra space

Key Insight:
- We need to reverse a sublist while keeping the rest of the list intact
- Use a dummy node to simplify edge cases
- Standard reversal: for each node, set current->next = reversePrev, then move pointers
- Track the tail of reversed sublist to connect it to the remaining list

Example Walkthrough:
Input: head = [1,2,3,4,5], left = 2, right = 4
Step 1: Find prev (node at position 1) -> node with value 1
Step 2: Reverse sublist [2,3,4]:
  - Start: current = 2, reversePrev = nullptr
  - Iteration 1: current = 2, next = 3, 2->next = nullptr, reversePrev = 2, current = 3
  - Iteration 2: current = 3, next = 4, 3->next = 2, reversePrev = 3, current = 4
  - Iteration 3: current = 4, next = 5, 4->next = 3, reversePrev = 4, current = 5
Step 3: Connect: prev->next = 4, tail(2)->next = 5
Result: [1,4,3,2,5]
*/

