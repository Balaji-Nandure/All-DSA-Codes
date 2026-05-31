/*
GeeksforGeeks: Linked List Insertion At Beginning
Difficulty: Easy

Problem:
You are given the head of a Singly Linked List and a value x, insert that value x at the beginning of the LinkedList and return the head of the modified Linked List.

Example 1:
Input: x = 1, linked list: 2 -> 10
Output: 1 -> 2 -> 10
Explanation: We can see that 1 is inserted at the beginning of the linked list.

Example 2:
Input: x = 1, linked list: 2 -> 3 -> 4 -> 5
Output: 1 -> 2 -> 3 -> 4 -> 5
Explanation: We can see that 1 is inserted at the beginning of the linked list.

Core Idea:
To insert a new node at the beginning of a singly linked list, we simply need to create a new node with the given value, set its `next` pointer to point to the current head of the list, and then update the head of the list to be this new node.

Approach:
1. Create a new `Node` with the given value `x`.
2. Assign the `next` pointer of this newly created node to the current `head` of the linked list.
3. Return the new node, as it is now the new head of the linked list.

Time Complexity: O(1) - Inserting at the beginning takes constant time since we only manipulate two pointers.
Space Complexity: O(1) - We only create one new node, requiring constant extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/linked-list-insertion-at-beginning/1
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
    // Function to insert a node at the beginning of the linked list.
    Node* insertAtBegining(Node* head, int x) {
        // Create a new node with the given data
        Node* newNode = new Node(x);
        
        // Point the next of new node to the current head
        newNode->next = head;
        
        // The new node becomes the new head of the list
        return newNode;
    }
};

/*
Dry Run — Example 1:
Input: x = 1, linked list: 2 -> 10

Initial State:
head -> 2 -> 10 -> NULL

Step 1: Create a new node with value `x`
newNode = Node(1)
newNode -> 1 -> NULL

Step 2: Point `newNode->next` to `head`
newNode->next = head
newNode -> 1 -> 2 -> 10 -> NULL

Step 3: Return `newNode` as the new head
The updated linked list is: 1 -> 2 -> 10 -> NULL

Final Output: 1 -> 2 -> 10
*/
