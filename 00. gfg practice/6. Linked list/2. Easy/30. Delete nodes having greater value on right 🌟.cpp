/*
GeeksforGeeks: Delete nodes having greater value on right
Difficulty: Easy

Problem:
Given a singly linked list, remove all nodes that have a node with a greater value anywhere to their right in the list. Return the head of the modified linked list.

Example 1:
Input: LinkedList = 12->15->10->11->5->6->2->3
Output: 15->11->6->3
Explanation: Since, 12, 10, 5 and 2 are the elements which have greater elements on the following nodes. So, after deleting them, the linked list would be 15, 11, 6, 3.

Example 2:
Input: LinkedList = 10->20->30->40->50->60
Output: 60
Explanation: All the nodes except the last node have a greater value node on their right, so all the nodes except the last node must be removed.

Core Idea:
It is difficult to determine if a node has a greater element to its right by traversing from left to right without taking O(N^2) time or O(N) extra space (like a stack).
Instead, we can process the list from right to left in O(N) time and O(1) space by first reversing the list.
Once reversed, the problem reduces to keeping track of the maximum value seen so far while traversing.
If a node's value is smaller than the maximum seen so far, it means it originally had a greater value to its right, so we delete it.
Otherwise, we keep it and update the maximum. Finally, we reverse the list back to its original order.

Approach:
1. Reverse the given linked list.
2. Initialize `max_so_far` to the value of the new head.
3. Traverse the reversed list using a `curr` pointer and keep track of the `prev` node.
   - If `curr->data < max_so_far`, the node needs to be deleted.
     - `prev->next = curr->next`
     - `delete curr`
     - `curr = prev->next`
   - Else, the node is kept.
     - `max_so_far = curr->data`
     - `prev = curr`
     - `curr = curr->next`
4. Reverse the list again to restore the original order.
5. Return the head of the final list.

Time Complexity: O(N) where N is the number of nodes. We traverse the list a few times (reverse, filter, reverse).
Space Complexity: O(1) as we modify pointers in-place.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-nodes-having-greater-value-on-right/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
private:
    Node* reverseList(Node* head) {
        Node* prev = NULL;
        Node* curr = head;
        while (curr != NULL) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }

public:
    Node* compute(Node* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }

        // Step 1: Reverse the linked list
        head = reverseList(head);

        // Step 2: Traverse and delete smaller nodes
        Node* curr = head;
        Node* prev = head;
        int max_so_far = head->data;

        curr = curr->next;

        while (curr != NULL) {
            if (curr->data < max_so_far) {
                // Delete the current node
                prev->next = curr->next;
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            } else {
                // Keep the current node and update max_so_far
                max_so_far = curr->data;
                prev = curr;
                curr = curr->next;
            }
        }

        // Step 3: Reverse the list back to the original order
        head = reverseList(head);

        return head;
    }
};

/*
Dry Run — Example 1:
Input: 12->15->10->11->5->6->2->3

Step 1: Reverse list
List becomes: 3->2->6->5->11->10->15->12
max_so_far = 3, prev = 3, curr = 2

Step 2: Traverse
- curr = 2: 2 < 3. Delete 2. 
  prev (3) -> next becomes 6. curr moves to 6.
  List: 3->6->5->11->10->15->12
  
- curr = 6: 6 >= 3. Keep 6. 
  max_so_far = 6. prev = 6. curr moves to 5.
  
- curr = 5: 5 < 6. Delete 5.
  prev (6) -> next becomes 11. curr moves to 11.
  List: 3->6->11->10->15->12
  
- curr = 11: 11 >= 6. Keep 11.
  max_so_far = 11. prev = 11. curr moves to 10.
  
- curr = 10: 10 < 11. Delete 10.
  prev (11) -> next becomes 15. curr moves to 15.
  List: 3->6->11->15->12
  
- curr = 15: 15 >= 11. Keep 15.
  max_so_far = 15. prev = 15. curr moves to 12.
  
- curr = 12: 12 < 15. Delete 12.
  prev (15) -> next becomes NULL. curr moves to NULL.
  List: 3->6->11->15

Step 3: Reverse list back
List becomes: 15->11->6->3
Return head

Final Output: 15->11->6->3
*/
