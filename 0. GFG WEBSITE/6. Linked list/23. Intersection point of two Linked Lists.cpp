/*
Problem:
Intersection Point of Two Linked Lists

Given the heads of two singly linked lists,
find the node at which the two lists intersect.
Return the data of the intersecting node.
If the lists do not intersect, return -1.

Important:
- Intersection means both lists share the SAME NODE reference,
  not just the same value.
- Do NOT modify the linked lists.
- Efficient solution expected.

Examples:
Input:
List1: 10 -> 15 -> 30
List2: 3  -> 6  -> 9
                  \
                   15 -> 30
Output: 15

Input:
List1: 1 -> 2 -> 3
List2: 4 -> 5
Output: -1


-----------------------------------
Approach (Expected / Optimal – Two Pointer Switching):
-----------------------------------
1. Use two pointers p1 and p2 starting at head1 and head2.
2. Move both pointers one step at a time.
3. When a pointer reaches NULL:
   - Redirect it to the head of the other list.
4. Eventually:
   - Either both pointers meet at the intersection node
   - Or both become NULL (no intersection)

Why this works:
- Both pointers traverse equal total distance:
    length1 + length2
- Length difference is neutralized automatically.
- No extra space is used.

Time Complexity:
O(n + m)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/

LeetCode:
https://leetcode.com/problems/intersection-of-two-linked-lists/
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


int intersectionPoint(Node* head1, Node* head2) {

    if (head1 == NULL || head2 == NULL) {
        return -1;
    }

    Node* p1 = head1;
    Node* p2 = head2;

    // Traverse both lists
    while (p1 != p2) {
        if(p1){
            p1 = p1->next;
        } else {
            p1 = head2;
        }

        if(p2){
            p2 = p2->next;
        } else {
            p2 = head1;
        }
    }

    // Either intersection node or NULL
    if (p1 == NULL) {
        return -1;
    }

    return p1->data;
}
