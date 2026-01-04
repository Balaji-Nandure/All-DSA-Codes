/*
Problem:
Intersection of Two Sorted Linked Lists

Given two singly linked lists sorted in increasing order,
create and return a NEW linked list that represents the intersection
of the two lists.

Important Rules:
- The resulting list must use its OWN memory.
- The original lists must NOT be modified.
- The resulting list should also be sorted.
- If an element appears x times in both lists,
  it should appear min(x1, x2) times in the result.

Examples:
Input:
List1: 1 -> 2 -> 3 -> 4 -> 6
List2: 2 -> 4 -> 6 -> 8
Output:
2 -> 4 -> 6

Input:
List1: 1 -> 2 -> 3 -> 4 -> 5
List2: 2 -> 3 -> 4
Output:
2 -> 3 -> 4


-----------------------------------
Approach (Expected / Optimal – Two Pointer Technique):
-----------------------------------
1. Use two pointers:
   - p1 pointing to head1
   - p2 pointing to head2
2. Create a dummy node to build the result list easily.
3. Traverse both lists simultaneously:
   - If p1->data == p2->data:
       • Add this value to the result list (new node)
       • Move both pointers forward
   - If p1->data < p2->data:
       • Move p1 forward
   - Else:
       • Move p2 forward
4. Continue until either list ends.
5. Return dummy->next as the head of the intersection list.

Why this works:
- Lists are sorted, so comparison decides pointer movement.
- Each element is visited at most once.
- Ensures O(n + m) time complexity.
- New nodes ensure original lists remain unchanged.

Time Complexity:
O(n + m)

Space Complexity:
O(1) auxiliary space
(O(k) for output list where k = size of intersection)


GeeksforGeeks:
https://www.geeksforgeeks.org/intersection-of-two-sorted-linked-lists/

LeetCode:
No direct equivalent problem.
(Related concept but different definition)
*/


// Definition for singly linked list node
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


Node* findIntersection(Node* head1, Node* head2) {

    // Dummy node for result list
    Node* dummy = new Node(-1);
    Node* tail = dummy;

    Node* p1 = head1;
    Node* p2 = head2;

    while (p1 != NULL && p2 != NULL) {

        if (p1->data == p2->data) {
            // Create new node (do NOT reuse original nodes)
            tail->next = new Node(p1->data);
            tail = tail->next;

            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->data < p2->data) {
            p1 = p1->next;
        }
        else {
            p2 = p2->next;
        }
    }

    return dummy->next;
}
