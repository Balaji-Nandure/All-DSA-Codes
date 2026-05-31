/*
GeeksforGeeks: Linked List Delete at Position
Difficulty: Easy

Problem:
Given the head of a linked list of size n and an integer pos, delete the node at position pos and return the updated head of the linked list.
Note: Positions use 1-based indexing.

Example 1:
Input: head: 1->2->3->4->5, pos = 4
Output: 1->2->3->5
Explanation: The 4th node is 4. After deleting it, the list becomes 1->2->3->5.

Example 2:
Input: head: 2->5->7->8->99->100, pos = 6
Output: 2->5->7->8->99
Explanation: The 6th node is 100. After deleting it, the list becomes 2->5->7->8->99.

Core Idea:
To delete a node at a specific position (1-based), we need to handle two cases:
1. If `pos == 1`, we are deleting the head. We just update the head to `head->next` and delete the original head.
2. If `pos > 1`, we need to find the node just *before* the node to be deleted (at position `pos - 1`). 
   Once we reach the `(pos - 1)`-th node, we can bypass the `pos`-th node by updating `curr->next = curr->next->next`. 
   Finally, we delete the bypassed node.

Approach:
1. If the list is empty (`head == NULL`), return `NULL`.
2. If `pos == 1`:
   - Store the current head in a `temp` pointer.
   - Update `head = head->next`.
   - Delete `temp` and return the new `head`.
3. If `pos > 1`, use a pointer `curr` initialized to `head`.
4. Run a loop from `i = 1` to `pos - 1` to advance `curr` to the node just before the one to be deleted.
5. Store the node to be deleted `Node* nodeToDelete = curr->next`.
6. Update the `next` pointer of `curr`: `curr->next = nodeToDelete->next`.
7. Delete `nodeToDelete` to free memory.
8. Return the original `head`.

Time Complexity: O(N) where N is the `pos`. In the worst case, we traverse up to the end of the list.
Space Complexity: O(1) as we only use a few extra pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    Node* deleteAtPosition(Node* head, int pos) {
        // Base case: empty list
        if (head == NULL) {
            return NULL;
        }

        // Case 1: Delete the head node (pos = 1)
        if (pos == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return head;
        }

        // Case 2: Delete a node at position > 1
        Node* curr = head;
        
        // Traverse to the node just before the position to be deleted (pos - 1)
        for (int i = 1; i < pos - 1 && curr != NULL; i++) {
            curr = curr->next;
        }

        // If pos is out of bounds (curr is NULL or curr->next is NULL)
        // Constraints say 1 <= pos <= n, so this won't happen for valid inputs.
        if (curr == NULL || curr->next == NULL) {
            return head;
        }

        // Node to be deleted is curr->next
        Node* nodeToDelete = curr->next;
        
        // Bypass the node to be deleted
        curr->next = nodeToDelete->next;
        
        // Free the memory
        delete nodeToDelete;

        return head;
    }
};

/*
Dry Run — Example 1:
Input: head: 1->2->3->4->5, pos = 4

Initial State:
head -> 1 -> 2 -> 3 -> 4 -> 5 -> NULL
pos = 4

Step 1: Check if pos == 1. No.

Step 2: Traverse to pos - 1 (which is 3)
i = 1: curr = curr->next (curr becomes node 2)
i = 2: curr = curr->next (curr becomes node 3)
Loop terminates.
curr now points to node 3.

Step 3: Delete the node
nodeToDelete = curr->next (points to node 4)
curr->next = nodeToDelete->next (node 3 points to node 5)
delete nodeToDelete (node 4 is deleted)

Final List:
1 -> 2 -> 3 -> 5 -> NULL
Return: head
*/
