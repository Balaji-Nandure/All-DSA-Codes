/*
GeeksforGeeks: Delete Alternate Nodes
Difficulty: Easy

Problem:
Given a Singly Linked List, Delete all alternate nodes of the list ie delete all the nodes present in even positions.

Example 1:
Input: LinkedList: 1->2->3->4->5->6
Output: 1->3->5
Explanation: Deleting alternate nodes ie 2, 4, 6 results in the linked list with elements 1->3->5.

Example 2:
Input: LinkedList: 99->59->42->20
Output: 99->42

Core Idea:
To delete alternate nodes (nodes at even positions like 2nd, 4th, 6th, etc.), we can traverse the list starting from the `head`.
For every node `curr`, the node to be deleted is `curr->next`.
We simply change `curr->next` to `curr->next->next`, delete the alternate node to free up memory, and then advance `curr` to the next valid node (`curr->next`).
We continue this process as long as both `curr` and `curr->next` are not NULL.

Approach:
1. Handle base case: If the list is empty (`head == NULL`) or has only one node (`head->next == NULL`), there are no alternate nodes to delete, so just return.
2. Initialize a pointer `curr = head`.
3. Loop while `curr != NULL && curr->next != NULL`:
   a. Store the node to be deleted: `Node* temp = curr->next;`
   b. Unlink the node: `curr->next = temp->next;`
   c. Free memory: `delete temp;`
   d. Move to the next node: `curr = curr->next;`
4. The head remains unchanged, so the function returns `void` (or just modifies the list in place).

Time Complexity: O(N) where N is the number of nodes in the linked list. We traverse the list once.
Space Complexity: O(1) as we are only modifying pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-alternate-nodes/1
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
    void deleteAlt(Node *head) {
        if (head == NULL) return;

        Node* curr = head;

        while (curr != NULL && curr->next != NULL) {
            // Node to be deleted
            Node* temp = curr->next;
            
            // Bypass the alternate node
            curr->next = temp->next;
            
            // Free the memory of the alternate node
            delete temp;
            
            // Move to the next valid node
            curr = curr->next;
        }
    }
};

/*
Dry Run — Example 1:
Input: LinkedList: 1->2->3->4->5->6

Initial state:
head -> [1] -> [2] -> [3] -> [4] -> [5] -> [6] -> NULL
curr = head (points to 1)

Step 1:
curr points to 1. `curr != NULL && curr->next != NULL` (TRUE).
- temp = curr->next (points to 2)
- curr->next = temp->next (1 -> 3)
- delete temp (2 is deleted)
- curr = curr->next (curr now points to 3)
List: 1 -> 3 -> 4 -> 5 -> 6 -> NULL

Step 2:
curr points to 3. `curr != NULL && curr->next != NULL` (TRUE).
- temp = curr->next (points to 4)
- curr->next = temp->next (3 -> 5)
- delete temp (4 is deleted)
- curr = curr->next (curr now points to 5)
List: 1 -> 3 -> 5 -> 6 -> NULL

Step 3:
curr points to 5. `curr != NULL && curr->next != NULL` (TRUE).
- temp = curr->next (points to 6)
- curr->next = temp->next (5 -> NULL)
- delete temp (6 is deleted)
- curr = curr->next (curr now points to NULL)
List: 1 -> 3 -> 5 -> NULL

Step 4:
curr points to NULL. `curr != NULL && curr->next != NULL` (FALSE).
Loop terminates.

Final Output Linked List:
1 -> 3 -> 5 -> NULL
*/
