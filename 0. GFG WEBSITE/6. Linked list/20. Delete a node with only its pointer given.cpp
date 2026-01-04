/*
Problem:
Delete a Node with Only Its Pointer Given

You are given a pointer/reference to a node in a singly linked list.
The head pointer is NOT given.
Delete this node from the linked list.

Important Constraints:
- The given node is NOT the last node.
- You must NOT traverse the list.
- You must NOT access the head.

Classic Interview Problem.

Examples:
Input:
List : 1 -> 2 -> 3 -> 4 -> 5
Given node = 3
Output:
1 -> 2 -> 4 -> 5

Explanation:
We cannot move backward or access head.
So we copy data from next node and bypass it.


-----------------------------------
Approach (Expected / Optimal – Data Copy Trick):
-----------------------------------
1. Copy the data of the next node into the current node.
2. Change the current node’s next pointer to skip the next node.
3. Effectively, the next node gets deleted.

Why this works:
- We cannot delete the current node directly without head.
- Copying next node’s data makes current node act like the next node.
- Skipping the next node removes it from the list.

Important Limitation:
- This method DOES NOT work for deleting the last node.

Time Complexity:
O(1)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/delete-a-node-without-head-pointer/

LeetCode:
https://leetcode.com/problems/delete-node-in-a-linked-list/
*/


// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


void deleteNode(Node* node) {

    // Given constraint: node is not the last node
    if (node == NULL || node->next == NULL) {
        return;
    }

    Node* temp = node->next;

    // Copy next node's data into current node
    node->data = temp->data;

    // Skip the next node
    node->next = temp->next;

    // delete temp; // optional depending on platform
}
