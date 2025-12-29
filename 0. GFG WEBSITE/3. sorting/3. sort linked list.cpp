/*
=============================
SORTING A LINKED LIST
=============================

--------------------------------------------------
1) Bubble Sort on Linked List
--------------------------------------------------
Approach:
- Repeatedly traverse the list.
- Compare adjacent nodes and swap their data if out of order.
- Continue passes until no swaps occur.

Time: O(n^2)
Space: O(1)
*/

void bubbleSort(Node* head) {
    if (!head) return;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        Node* cur = head;

        while (cur->next) {
            if (cur->data > cur->next->data) {
                swap(cur->data, cur->next->data);
                swapped = true;
            }
            cur = cur->next;
        }
    }
}

/*
--------------------------------------------------
4) Merge Sort on Linked List  ✅ BEST
--------------------------------------------------
Approach:
- Use slow & fast pointer to split list into halves.
- Recursively sort both halves.
- Merge the two sorted linked lists.

Time: O(n log n)
Space: O(log n) recursion
*/

// merge recursive
Node* merge(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data <= l2->data) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

Node* getMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) return head;

    Node* mid = getMiddle(head);
    Node* right = mid->next;
    mid->next = nullptr;

    Node* left = mergeSort(head);
    right = mergeSort(right);

    return merge(left, right);
}


/*
--------------------------------------------------
Which Sorting Algorithm is BEST for Linked Lists?
--------------------------------------------------
Answer:
Merge Sort

Reason:
- Does not require random access.
- Splitting and merging are pointer-based.
- Guaranteed O(n log n) time.
- Stable sorting.

Bubble / Insertion:
- Only good for very small lists.

Quick Sort:
- Not ideal due to recursion & partition complexity.
*/


/*
=============================
PRACTICE LINKS
=============================

GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/sort-a-linked-list/1

LeetCode:
https://leetcode.com/problems/sort-list/
*/
