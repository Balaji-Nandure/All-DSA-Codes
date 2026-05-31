/*
GeeksforGeeks: Insertion at specific position in circular linked list
Difficulty: Easy

Problem:
Given a circular linked list of size N and an integer x, your task is to insert a new node with value x at a specific position pos in the circular linked list. 
The position pos is zero-based, and it is guaranteed that the position is valid (0 <= pos <= N). 
Return the updated circular linked list.

Example 1:
Input: head = [2 -> 3 -> 4], pos = 1, x = 5 
Output: 2 5 3 4
Explanation: The new node with data 5 is inserted at position 1. The list becomes 2 -> 5 -> 3 -> 4.

Example 2:
Input: head = [2 -> 3 -> 4], pos = 0, x = 1
Output: 1 2 3 4
Explanation: The new node with data 1 is inserted at position 0, making it the new head. The list becomes 1 -> 2 -> 3 -> 4.

Core Idea:
Inserting a node into a circular linked list is similar to a singly linked list with a twist when inserting at the head (position 0). 
Since the last node points to the head, inserting a new node at position 0 requires us to traverse the list to find the last node and update its `next` pointer to point to the new head. 
For any other position (pos > 0), we just need to traverse to `pos - 1`, link the new node appropriately, and we're done.

Approach:
1. Create a `newNode` with data `x`.
2. Handle `pos == 0`:
   - If the list is empty (though constraints say N >= 1), we point `newNode->next` to itself and return it.
   - Otherwise, initialize `curr = head` and traverse until `curr->next == head` (finding the last node).
   - Set the last node's `next` to point to `newNode` (`curr->next = newNode`).
   - Set `newNode->next` to the original `head`.
   - Return `newNode` as the new head.
3. Handle `pos > 0`:
   - Initialize `curr = head`.
   - Traverse the list with a loop `for (int i = 0; i < pos - 1; i++)`, moving `curr = curr->next`. This places `curr` at the node just before the target position.
   - Insert the new node: `newNode->next = curr->next` and `curr->next = newNode`.
   - Return the original `head`.

Time Complexity: O(N) because if we insert at position 0, we must traverse to the end of the list. Similarly, if `pos` is near the end, we traverse up to `pos - 1` nodes.
Space Complexity: O(1) since we only use a new node and a couple of traversal pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/insertion-in-circular-linked-list/1
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
    Node* insertAtPosition(Node* head, int pos, int x) {
        Node* newNode = new Node(x);

        // Case 1: Inserting at position 0 (new head)
        if (pos == 0) {
            // Safety check for empty list
            if (head == NULL) {
                newNode->next = newNode;
                return newNode;
            }

            Node* curr = head;
            
            // Find the last node in the circular list
            while (curr->next != head) {
                curr = curr->next;
            }

            // Update pointers to insert at the beginning
            curr->next = newNode;
            newNode->next = head;
            
            return newNode; // The new node becomes the new head
        }

        // Case 2: Inserting at position > 0
        Node* curr = head;
        
        // Traverse to the node just before the desired position (pos - 1)
        for (int i = 0; i < pos - 1; i++) {
            curr = curr->next;
        }

        // Insert the new node
        newNode->next = curr->next;
        curr->next = newNode;

        return head;
    }
};

/*
Dry Run — Example 1:
Input: head = [2 -> 3 -> 4], pos = 1, x = 5 

Initial State:
head -> 2 -> 3 -> 4 -> (back to 2)
pos = 1, x = 5

Step 1: Create new node
newNode -> 5 -> NULL

Step 2: Check pos == 0. False.

Step 3: Traverse to pos - 1 (which is 0)
The loop `for (int i = 0; i < 0; i++)` does not run.
curr remains pointing to node 2.

Step 4: Insert
newNode->next = curr->next (5 points to 3)
curr->next = newNode (2 points to 5)

Final List:
head -> 2 -> 5 -> 3 -> 4 -> (back to 2)
Return head (2)
*/
