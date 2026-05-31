/*
GeeksforGeeks: Insertion at a Given Position in a Linked List
Difficulty: Easy

Problem:
You are given the head of a Singly Linked List, a position pos and value val. Insert the val data at the given position (1-based index) of the LinkedList and return the head of the modified Linked List.

Example 1:
Input: pos = 3, val = 4, Linked List: 1 -> 3
Output: 1 -> 3 -> 4
Explanation: After inserting 4 at position 3 we'll get our linked list as 1 -> 3 -> 4.

Example 2:
Input: pos = 2, val = 5, Linked List: 1 -> 2 -> 9
Output: 1 -> 5 -> 2 -> 9
Explanation: After inserting 5 at position 2 we'll get our linked list as 1 -> 5 -> 2 -> 9.

Core Idea:
To insert a new node at a given position `pos`, we handle two main cases:
1. If `pos == 1`, we're inserting at the head. We just make the new node point to the current head, and the new node becomes the new head.
2. If `pos > 1`, we must traverse the list to reach the node just before our target position (which is at `pos - 1`). Then, we insert the new node right after this `(pos - 1)`-th node by adjusting the `next` pointers.

Approach:
1. Create a new `Node` with the given `val`.
2. Check if `pos == 1`. If so, point `newNode->next` to `head` and return `newNode` as the new head.
3. Otherwise, use a pointer `curr` initialized to `head` to traverse the list.
4. Run a loop from `i = 1` up to `pos - 1`. In each iteration, move `curr` to `curr->next`.
5. Once the loop finishes, `curr` points to the `(pos - 1)`-th node.
6. Set `newNode->next = curr->next`.
7. Set `curr->next = newNode`.
8. Return the original `head`.

Time Complexity: O(N) where N is the `pos`. In the worst case, we might insert at the end, traversing the entire list.
Space Complexity: O(1) as only a new node and a traversal pointer are created.

GFG Link:
https://www.geeksforgeeks.org/problems/insert-a-node-in-linked-list/1
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
    Node* insertAtPosition(Node* head, int pos, int val) {
        // Create the new node
        Node* newNode = new Node(val);

        // Case 1: Insert at the head (position 1)
        if (pos == 1) {
            newNode->next = head;
            return newNode;
        }

        // Case 2: Insert at a position > 1
        Node* curr = head;
        
        // Traverse to the node just before the insertion point (pos - 1)
        for (int i = 1; i < pos - 1 && curr != NULL; i++) {
            curr = curr->next;
        }

        // If curr is NULL, it means pos is greater than the size of the list + 1.
        // Based on the constraints (1 <= pos <= List Size + 1), this won't happen.
        if (curr != NULL) {
            newNode->next = curr->next;
            curr->next = newNode;
        }

        return head;
    }
};

/*
Dry Run — Example 2:
Input: pos = 2, val = 5, Linked List: 1 -> 2 -> 9

Initial State:
head -> 1 -> 2 -> 9 -> NULL
pos = 2, val = 5

Step 1: Create new node
newNode -> 5 -> NULL

Step 2: Check if pos == 1. No (pos is 2).

Step 3: Traverse to pos - 1
pos - 1 = 1.
The loop `for (int i = 1; i < pos - 1...` will not execute since 1 < 1 is false.
curr remains at head (node 1).

Step 4: Insert the node
newNode->next = curr->next (newNode's next points to 2)
curr->next = newNode (node 1's next points to newNode, which is 5)

List State:
1 -> 5 -> 2 -> 9 -> NULL

Final Output: 1 -> 5 -> 2 -> 9
Return: head
*/
