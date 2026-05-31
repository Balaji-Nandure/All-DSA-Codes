/*
GeeksforGeeks: Remove duplicates from a sorted DLL
Difficulty: Easy

Problem:
Given a doubly linked list of n nodes sorted by values, remove duplicate nodes present in the linked list.

Example 1:
Input: head: 1<->1<->1<->2<->3<->4
Output: 1<->2<->3<->4
Explanation: Only the first occurance of node with value 1 is retained along with other distinct values. 

Example 2:
Input: head: 1<->2<->2<->3<->3<->4<->4
Output: 1<->2<->3<->4
Explanation: Only the first occurance of nodes with values 2, 3 and 4 are retained, rest repeating nodes are deleted.

Core Idea:
Since the doubly linked list is already sorted, any duplicate elements will be adjacent to each other. 
We can traverse the list with a pointer `curr`. At each node, we check if its data is equal to the data of the next node (`curr->next->data`). 
If they are equal, it means `curr->next` is a duplicate. We bypass `curr->next` by pointing `curr->next` to `curr->next->next`. 
If `curr->next->next` exists, its `prev` pointer should be updated to point to `curr`. 
Then we delete the duplicate node to free memory. If they are not equal, we just move `curr` to `curr->next`.

Approach:
1. Handle the base case: If `head == NULL`, return NULL.
2. Initialize `curr = head`.
3. Loop while `curr != NULL && curr->next != NULL`:
   a. Check if `curr->data == curr->next->data`.
   b. If true, the next node is a duplicate:
      - `Node* temp = curr->next;`
      - `curr->next = temp->next;`
      - If `temp->next != NULL`, `temp->next->prev = curr;`
      - `delete temp;`
   c. If false, simply advance `curr`:
      - `curr = curr->next;`
4. Return the modified `head`.

Time Complexity: O(N) where N is the number of nodes. We traverse the list exactly once.
Space Complexity: O(1) as we modify the pointers in place.

GFG Link:
https://www.geeksforgeeks.org/problems/remove-duplicates-from-a-sorted-doubly-linked-list/1
*/

#include <iostream>

using namespace std;

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

class Solution {
public:
    Node* removeDuplicates(struct Node *head) {
        if (head == NULL) return NULL;
        
        Node* curr = head;
        
        while (curr != NULL && curr->next != NULL) {
            if (curr->data == curr->next->data) {
                // Next node is a duplicate, so we delete it
                Node* temp = curr->next;
                curr->next = temp->next;
                
                if (temp->next != NULL) {
                    temp->next->prev = curr;
                }
                
                delete temp;
            } else {
                // No duplicate, advance the pointer
                curr = curr->next;
            }
        }
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: head: 1<->1<->1<->2<->3<->4

Initial state:
head -> [1] <-> [1] <-> [1] <-> [2] <-> [3] <-> [4] -> NULL
curr = head (points to 1st [1])

Step 1:
curr points to 1st [1].
`curr->data` (1) == `curr->next->data` (1) is TRUE.
- temp = curr->next (points to 2nd [1])
- curr->next = temp->next (points to 3rd [1])
- temp->next->prev = curr (3rd [1].prev points to 1st [1])
- delete temp (2nd [1] is deleted)
List: [1] <-> [1] <-> [2] <-> [3] <-> [4] -> NULL
(curr is still at 1st [1])

Step 2:
curr points to 1st [1].
`curr->data` (1) == `curr->next->data` (1) is TRUE.
- temp = curr->next (points to 3rd [1])
- curr->next = temp->next (points to [2])
- temp->next->prev = curr ([2].prev points to 1st [1])
- delete temp (3rd [1] is deleted)
List: [1] <-> [2] <-> [3] <-> [4] -> NULL
(curr is still at 1st [1])

Step 3:
curr points to 1st [1].
`curr->data` (1) == `curr->next->data` (2) is FALSE.
- curr = curr->next (curr now points to [2])

Step 4:
curr points to [2].
`curr->data` (2) == `curr->next->data` (3) is FALSE.
- curr = curr->next (curr now points to [3])

Step 5:
curr points to [3].
`curr->data` (3) == `curr->next->data` (4) is FALSE.
- curr = curr->next (curr now points to [4])

Step 6:
curr points to [4].
`curr->next` is NULL. Loop terminates.

Final Output Linked List:
1<->2<->3<->4
*/
