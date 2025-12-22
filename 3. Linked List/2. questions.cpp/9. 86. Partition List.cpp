/*
LeetCode 86: Partition List

Given the head of a linked list and a value x, partition it such that all nodes 
less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Explanation: Nodes less than 3 are [1,2,2] and nodes >= 3 are [4,3,5]. 
They maintain their relative order.
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
 * Problem: Partition List
 *
 * LeetCode 86: Partition List
 *
 * Partition list such that nodes < x come before nodes >= x.
 * Preserve relative order within each partition.
 * Example: [1,4,3,2,5,2], x=3 -> [1,2,2,4,3,5]
 *
 * Time: O(n) - single pass
 * Space: O(1)
 */

    ListNode* partition(ListNode* head, int x) {
        // Create two dummy nodes for two partitions
        ListNode* lessDummy = new ListNode(0);      // Nodes < x
        ListNode* greaterDummy = new ListNode(0);   // Nodes >= x
        
        // Pointers to track tail of each partition
        ListNode* lessTail = lessDummy;
        ListNode* greaterTail = greaterDummy;
        
        ListNode* current = head;
        
        // Partition: separate nodes into two lists
        while (current != nullptr) {
            if (current->val < x) {
                // Add to less than x partition
                lessTail->next = current;
                lessTail = lessTail->next;
            } else {
                // Add to greater than or equal to x partition
                greaterTail->next = current;
                greaterTail = greaterTail->next;
            }
            current = current->next;
        }
        
        // Connect partitions: less -> greater
        lessTail->next = greaterDummy->next;
        greaterTail->next = nullptr;  // Important: terminate list to avoid cycles
            
        // Get new head (skip dummy)
        ListNode* result = lessDummy->next;
        
        // Clean up dummy nodes
        delete lessDummy;
        delete greaterDummy;
        
        return result;
    }
};

/*
Approach: Two Pointers with Dummy Nodes
- Create two separate lists: one for nodes < x, one for nodes >= x
- Use dummy nodes to simplify edge cases (empty partitions)
- Traverse the original list and append nodes to appropriate partition
- Connect the two partitions: less partition -> greater partition
- Terminate the greater partition properly

Time Complexity: O(n) - single pass through the list
Space Complexity: O(1) - only using constant extra space (dummy nodes)

Key Insight:
- We need to maintain relative order, so we can't use sorting
- Two-pointer technique with dummy nodes makes it clean
- Always terminate the greater partition to avoid cycles
- Dummy nodes eliminate edge case handling (empty partitions)

Example Walkthrough:
Input: head = [1,4,3,2,5,2], x = 3
Less partition: [1,2,2]
Greater partition: [4,3,5]
Result: [1,2,2,4,3,5]
*/

