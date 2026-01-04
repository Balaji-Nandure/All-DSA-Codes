/*
Problem:
Remove Duplicates from an Unsorted Doubly Linked List

Given the head of an UNSORTED doubly linked list,
remove all duplicate nodes so that each value appears only once.
The relative order of first occurrences must be preserved.

Important:
- The list is NOT sorted.
- Do NOT create new nodes.
- Properly update BOTH next and prev pointers.

Examples:
Input  : 1 <-> 3 <-> 2 <-> 3 <-> 1 <-> 4
Output : 1 <-> 3 <-> 2 <-> 4

Input  : 5 <-> 5 <-> 5 <-> 5
Output : 5

Input  : 1 <-> 2 <-> 3
Output : 1 <-> 2 <-> 3


-----------------------------------
Approach (Expected / Optimal – Hashing):
-----------------------------------
1. Use an unordered_set to store values already seen.
2. Traverse the doubly linked list node by node.
3. For each node:
   - If its value is already present in the set:
       • Remove the node by adjusting links
   - Else:
       • Insert value into the set
4. Continue till the end.

Why this works:
- Hashing provides O(1) average-time lookup.
- First occurrence is preserved.
- Pointer updates maintain DLL integrity.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-doubly-linked-list/

LeetCode:
No direct equivalent problem.
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


Node* removeDuplicates(Node* head) {

    // Empty list or single node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    unordered_set<int> seen;

    Node* curr = head;

    while (curr != NULL) {

        // If duplicate found
        if (seen.count(curr->data)) {

            Node* toDelete = curr;

            // Fix previous link
            if (curr->prev != NULL) {
                curr->prev->next = curr->next;
            }

            // Fix next link
            if (curr->next != NULL) {
                curr->next->prev = curr->prev;
            }

            curr = curr->next;   // move ahead

            // delete toDelete;  // optional (platform-dependent)
        }
        else {
            seen.insert(curr->data);
            curr = curr->next;
        }
    }

    return head;
}
