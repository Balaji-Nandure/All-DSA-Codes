/*
Problem:
Merge Sort for a Doubly Linked List

Given the head of a doubly linked list,
sort the list in ascending order using Merge Sort
and return the head of the sorted list.

Important:
- Do NOT convert the list into an array.
- Sorting must be done by rearranging links.
- Merge Sort is preferred for linked lists.

Examples:
Input  : 4 <-> 2 <-> 5 <-> 1 <-> 3
Output : 1 <-> 2 <-> 3 <-> 4 <-> 5

Input  : 10 <-> 7 <-> 8
Output : 7 <-> 8 <-> 10


-----------------------------------
Approach (Expected / Optimal – Merge Sort on Linked List):
-----------------------------------
1. Split the linked list into two halves using slow & fast pointers.
2. Recursively sort both halves.
3. Merge the two sorted halves into one sorted list.
4. Ensure both next and prev pointers are correctly updated.

Why this works:
- Merge Sort does not require random access.
- Stable sort (preserves relative order).
- Guaranteed O(n log n) time complexity.
- Very suitable for linked lists.

Time Complexity:
O(n log n)

Space Complexity:
O(log n)   (recursion stack)


GeeksforGeeks:
https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/

LeetCode:
No direct equivalent problem.
(Related to sorting linked lists)
*/


// Definition for Doubly Linked List Node
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        next = NULL;
        prev = NULL;
    }
};


// ------------------------------------------------------------
// Split the list into two halves
// ------------------------------------------------------------
Node* split(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* second = slow->next;
    slow->next = NULL;

    if (second != NULL) {
        second->prev = NULL;
    }

    return second;
}


// ------------------------------------------------------------
// Merge two sorted doubly linked lists
// ------------------------------------------------------------
Node* merge(Node* first, Node* second) {
    // Handle empty lists
    if (!first) return second;
    if (!second) return first;

    // Dummy node to ease merging
    Node dummy(0);
    Node* tail = &dummy;

    while (first && second) {
        if (first->data <= second->data) {
            tail->next = first;
            first->prev = tail;
            first = first->next;
        } else {
            tail->next = second;
            second->prev = tail;
            second = second->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    if (first) {
        tail->next = first;
        first->prev = tail;
    } else if (second) {
        tail->next = second;
        second->prev = tail;
    }

    // Detach dummy node
    Node* mergedHead = dummy.next;
    if (mergedHead) mergedHead->prev = NULL;
    return mergedHead;
}


// ------------------------------------------------------------
// Merge Sort (Main Function)
// ------------------------------------------------------------
Node* mergeSort(Node* head) {

    // Base case: empty or single node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Step 1: Split list
    Node* second = split(head);

    // Step 2: Recursively sort both halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Step 3: Merge sorted halves
    return merge(head, second);
}
