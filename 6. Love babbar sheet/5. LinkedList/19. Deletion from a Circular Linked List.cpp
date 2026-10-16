/**
 * ============================================================================
 * Problem: Deletion from a Circular Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a Circular Linked List and a target key. Delete the first node with data 
 * equal to `key` from the circular linked list.
 * Return the updated head pointer of the modified circular linked list.
 * 
 * Example 1:
 * Input:  2 -> 5 -> 7 -> 8 -> 10 -> (back to 2), Key = 5
 * Output: 2 -> 7 -> 8 -> 10 -> (back to 2)
 * 
 * Example 2:
 * Input:  2 -> 5 -> 7 -> 8 -> 10 -> (back to 2), Key = 2 (Head deletion)
 * Output: 5 -> 7 -> 8 -> 10 -> (back to 5)
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Head Deletion in Circular Lists requires Updating the Tail:
 *    - In a linear singly linked list, deleting the head only requires `head = head->next`.
 *    - In a circular linked list, the TAIL points to the old head!
 *    - If the head node is deleted, the tail's `next` pointer MUST be updated to point
 *      to the NEW head to preserve circularity.
 * 2. Cycle-Aware Termination Condition:
 *    - Because there is no NULL pointer, loops terminate when `curr == head` after
 *      at least one step, preventing infinite traversal when key is absent.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Edge Case: List is Empty:
 *    - Return nullptr.
 * 2. Edge Case: Single Node List:
 *    - If `head->data == key`: delete head, return nullptr.
 *    - Else: return head.
 * 3. Case A: Deleting the Head Node (`head->data == key`):
 *    - Find the tail node: `while (tail->next != head) tail = tail->next;`
 *    - Update tail pointer: `tail->next = head->next;`
 *    - Save old head: `Node* toDelete = head;`
 *    - Advance head: `head = head->next;`
 *    - Deallocate: `delete toDelete;`
 * 4. Case B: Deleting a Non-Head Node:
 *    - Maintain `prev = head`, `curr = head->next`.
 *    - Search while `curr != head`:
 *        If `curr->data == key`:
 *          `prev->next = curr->next;`
 *          `delete curr;`
 *          break;
 *        `prev = curr;`
 *        `curr = curr->next;`
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Deletes a node with the given key from a circular linked list.
     * @param head Pointer to the head of the circular linked list.
     * @param key Value to be deleted.
     * @return New head pointer of the circular list.
     */
    Node* deleteNode(Node* head, int key) {
        // Case 1: Empty list
        if (head == nullptr) return nullptr;

        // Case 2: Only one node in the list
        if (head->next == head) {
            if (head->data == key) {
                delete head;
                return nullptr;
            }
            return head;
        }

        // Case 3: Deleting the head node
        if (head->data == key) {
            // Find the tail node
            Node* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When deleting the head in a circular list, the tail's next pointer
            // must be updated to point to the new head (head->next) before destroying the old head.
            tail->next = head->next;
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return head;
        }

        // Case 4: Deleting an internal or tail node
        Node* prev = head;
        Node* curr = head->next;

        while (curr != head) {
            if (curr->data == key) {
                prev->next = curr->next;
                delete curr;
                return head;
            }
            prev = curr;
            curr = curr->next;
        }

        return head; // Key was not found in the list
    }
};

void printCircularList(Node* head) {
    if (head == nullptr) {
        cout << "Empty\n";
        return;
    }
    Node* temp = head;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to " << head->data << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Delete middle node (key = 5)
    // 2 -> 5 -> 7 -> 8 -> 10 -> (back to 2)
    Node* head1 = new Node(2);
    head1->next = new Node(5);
    head1->next->next = new Node(7);
    head1->next->next->next = new Node(8);
    head1->next->next->next->next = new Node(10);
    head1->next->next->next->next->next = head1;

    cout << "Original List:         ";
    printCircularList(head1);

    head1 = solver.deleteNode(head1, 5);
    cout << "After Deleting 5:      ";
    printCircularList(head1); // Expected: 2 -> 7 -> 8 -> 10 -> back to 2

    // Test Case 2: Delete head node (key = 2)
    head1 = solver.deleteNode(head1, 2);
    cout << "After Deleting Head 2: ";
    printCircularList(head1); // Expected: 7 -> 8 -> 10 -> back to 7

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - At most N nodes are visited to locate the key or the tail node.
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Head deletion in circular linked lists has an O(N) cost because finding
 *    the predecessor (the tail) requires traversing the entire loop.
 */
