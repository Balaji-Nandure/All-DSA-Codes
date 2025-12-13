/*
LeetCode 143: Reorder List

You are given the head of a singly linked-list. The list can be represented as:
L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

Example:
Input: head = [1,2,3,4]
Output: [1,4,2,3]
Explanation: The list is reordered as L0 → L4 → L1 → L3
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
    void reorderList(ListNode* head) {
        if (!head || !head->next) {
            return;
        }
        
        // Step 1: Find the middle of the list using two pointers
        ListNode* slow = head;
        ListNode* fast = head;
        
        // this loop stops at the left half of the list
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Split the list into two halves
        ListNode* secondHalf = slow->next;
        slow->next = nullptr;  // Disconnect the two halves
        
        // Step 3: Reverse the second half
        secondHalf = reverseList(secondHalf);
        
        // Step 4: Merge the two halves alternately
        ListNode* first = head;
        ListNode* second = secondHalf;
        
        while (second) {
            ListNode* firstNext = first->next;
            ListNode* secondNext = second->next;
            
            first->next = second;
            second->next = firstNext;
            
            first = firstNext;
            second = secondNext;
        }
    }
};

/*
Approach: Find Middle, Reverse Second Half, Merge
- Find the middle of the linked list using two pointers (slow and fast)
- Split the list into two halves at the middle
- Reverse the second half
- Merge the two halves alternately: first node from first half, then first node from second half, etc.

Time Complexity: O(n) - find middle O(n), reverse O(n), merge O(n)
Space Complexity: O(1) - only using constant extra space

Key Insight:
- The reordering pattern is: L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → ...
- This is equivalent to interleaving the first half with the reversed second half
- We need to find the middle, reverse the second half, then merge alternately

Example Walkthrough:
Input: head = [1,2,3,4]
Step 1: Find middle -> slow points to node 2
Step 2: Split: first half = [1,2], second half = [3,4]
Step 3: Reverse second half: [4,3]
Step 4: Merge alternately:
  - 1 -> 4 -> 2 -> 3
Result: [1,4,2,3]
*/

