ListNode* mergeKLists(vector<ListNode*>& lists) {
    /*
    Problem:
    Merge k sorted linked lists into one sorted linked list.

    Simplified Approach (Min-Heap):
    - Use a min-heap storing ListNode*.
    - Custom comparator struct instead of lambda/function.
    - Heap always gives the smallest node among k lists.

    Time:
    O(N log k)

    Space:
    O(k)
    */

    // Comparator for min-heap
    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

    // Push first node of each list
    for (ListNode* head : lists) {
        if (head) {
            minHeap.push(head);
        }
    }

    ListNode *dummy = new ListNode(0);
    ListNode* tail = dummy;

    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();

        tail->next = node;
        tail = tail->next;

        if (node->next) {
            minHeap.push(node->next);
        }
    }

    return dummy.next;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1

LeetCode:
https://leetcode.com/problems/merge-k-sorted-lists/
*/
