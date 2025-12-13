/*
LeetCode 2816: Double a Number Represented as a Linked List

You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.
Return the head of the linked list after doubling it.

Example:
Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The number represented by this linked list is 189, and 189 * 2 = 378.
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
    ListNode* doubleIt(ListNode* head) {
        // Reverse the list to process from least significant to most significant
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        // Now prev is the head of reversed list (least significant digit first)
        head = prev;
        current = head;
        int carry = 0;
        
        // Double each digit and handle carry
        while (current != nullptr) {
            int doubled = current->val * 2 + carry;
            current->val = doubled % 10;
            carry = doubled / 10;
            
            // If this is the last node and we have carry, create a new node
            if (current->next == nullptr && carry > 0) {
                current->next = new ListNode(carry);
                carry = 0;
            }
            
            current = current->next;
        }
        
        // Reverse the list back
        prev = nullptr;
        current = head;
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
};

// Approach 2: Recursive (Process from right to left)
class Solution2 {
private:
    int doubleHelper(ListNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        // Recursively process the next node first (right to left)
        int carry = doubleHelper(node->next);
        
        // Double current digit and add carry
        int doubled = node->val * 2 + carry;
        node->val = doubled % 10;
        
        return doubled / 10;
    }
    
public:
    ListNode* doubleIt(ListNode* head) {
        int carry = doubleHelper(head);
        
        // If there's a carry after processing all nodes, create a new head
        if (carry > 0) {
            ListNode* newHead = new ListNode(carry);
            newHead->next = head;
            return newHead;
        }
        
        return head;
    }
};

/*
Approach 1: Reverse, Double, Reverse Back
- Reverse the list to process from least significant digit to most significant
- Traverse and double each digit, handling carry
- If carry remains after last node, create a new node
- Reverse the list back to original order

Time Complexity: O(n) - reverse O(n), traverse O(n), reverse back O(n)
Space Complexity: O(1) - only using constant extra space

Approach 2: Recursive (Process from Right to Left)
- Use recursion to process nodes from right to left
- Double each digit and propagate carry backwards
- If carry remains, create a new head node

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - recursion stack depth

Key Insight:
- Since digits are stored in reverse order (least significant first), we can process from left to right
- We need to handle carry propagation
- If carry remains after processing all digits, we need to add a new most significant digit
- Approach 1 is iterative and space-efficient
- Approach 2 is recursive and more elegant but uses O(n) space

Example Walkthrough:
Input: head = [1,8,9] (represents 189)
Step 1: Reverse -> [9,8,1]
Step 2: Double each digit:
  - 9 * 2 = 18, digit = 8, carry = 1
  - 8 * 2 + 1 = 17, digit = 7, carry = 1
  - 1 * 2 + 1 = 3, digit = 3, carry = 0
  - Result: [8,7,3]
Step 3: Reverse back -> [3,7,8] (represents 378)
Output: [3,7,8]
*/

