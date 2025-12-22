/*
 * Problem: Remove Linked List Elements
 *
 * LeetCode 203: Remove Linked List Elements
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-all-occurrences-of-a-given-key-in-a-doubly-linked-list/1
 *
 * Remove all nodes with given value from linked list.
 * Example: [1,2,6,3,4,5,6], val=6 -> [1,2,3,4,5]
 *
 * Time: O(n) - single pass
 * Space: O(1)
 */

// Remove all nodes with given value
ListNode* removeElements(ListNode* head, int val) {
    // Dummy node simplifies deletion at head
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* current = dummy;

    // Traverse and delete nodes with value 'val'
    while (current->next != nullptr) {
        if (current->next->val == val) {
            // Delete the node
            ListNode* temp = current->next;
            current->next = current->next->next; // Bypass node to delete
            delete temp;
        } else {
            current = current->next; // Move forward only if not deleted
        }
    }

    // Return new head (skip dummy)
    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}