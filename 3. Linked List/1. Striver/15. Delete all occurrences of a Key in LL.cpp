
ListNode* removeElements(ListNode* head, int val) {
    // Create a dummy node to simplify deletion at head
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* current = dummy;

    while (current->next != nullptr) {
        if (current->next->val == val) {
            // Delete the node
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }

    // Get the new head before deleting dummy
    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}

    