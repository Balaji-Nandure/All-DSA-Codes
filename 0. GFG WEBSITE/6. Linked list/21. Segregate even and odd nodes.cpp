/*
Problem:
Segregate Even and Odd Nodes in a Linked List

Given the head of a singly linked list,
rearrange the list such that:
- All nodes containing EVEN values come first
- Followed by all nodes containing ODD values
- The RELATIVE ORDER among even nodes and among odd nodes
  must be preserved (stable segregation).

Examples:
Input  : 17 -> 15 -> 8 -> 12 -> 10 -> 5 -> 4
Output : 8 -> 12 -> 10 -> 4 -> 17 -> 15 -> 5

Input  : 1 -> 3 -> 5
Output : 1 -> 3 -> 5

Input  : 2 -> 4 -> 6
Output : 2 -> 4 -> 6


-----------------------------------
Approach (Expected / Optimal – Two Dummy Lists):
-----------------------------------
1. Create two dummy lists:
   - even list for nodes with even data
   - odd list  for nodes with odd data
2. Traverse the original list once:
   - Append each node to either even or odd list.
   - Detach node safely while appending.
3. Connect even list with odd list.
4. Return head of the combined list.

Why this works:
- One pass over the list.
- Stable order preserved by tail insertion.
- Clean pointer manipulation using dummy nodes.

Time Complexity:
O(n)

Space Complexity:
O(1)   (only constant extra dummy nodes)


GeeksforGeeks:
https://www.geeksforgeeks.org/segregate-even-and-odd-elements-in-a-linked-list/

LeetCode:
No direct equivalent problem.
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



class Solution {
public:
    Node* divide(Node* head) {
        // code here
        Node *evenDummy = new Node(-1);
        Node *oddDummy = new Node(-1);
        
        Node *evenTail = evenDummy;
        Node *oddTail = oddDummy;
        Node *curr = head;
        
        while(curr){
            Node* nextNode = curr->next;
            if(curr->data % 2){
                // odd
                oddTail->next = curr;
                oddTail = curr;
                // curr = curr->next;
                curr->next = nullptr;
            } else {
                //even
                evenTail->next = curr;
                evenTail = curr;
                // curr = curr->next;
                curr->next = nullptr;
            }
            curr = nextNode;
        }
        
        evenTail->next = oddDummy->next;
        return evenDummy->next;
    }
};
