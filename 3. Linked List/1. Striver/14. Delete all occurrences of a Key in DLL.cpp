/*
 * Problem: Delete all occurrences of a Key in Doubly Linked List
 * 
 * Given a doubly linked list and a key, delete all occurrences of the given key 
 * from the doubly linked list.
 * 
 * Example 1:
 * Input: DLL: 2 <-> 2 <-> 10 <-> 8 <-> 4 <-> 2 <-> 5 <-> 2
 *        key = 2
 * Output: 10 <-> 8 <-> 4 <-> 5
 * Constraints:
 * - 1 <= number of nodes <= 10^5
 * - 0 <= Node->data <= 10^5
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in a doubly linked list
class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;

    // Constructor with data, next, prev
    DNode(int data, DNode* next = nullptr, DNode* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

// Convert array to doubly linked list
DNode* arrayToDoublyLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    DNode* head = new DNode(arr[0]);
    DNode* curr = head;
    for (int i = 1; i < arr.size(); ++i) {
        DNode* newNode = new DNode(arr[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    return head;
}

// Print doubly linked list forwards
void printDoublyLinkedList(DNode* head) {
    DNode* curr = head;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

// Print doubly linked list backwards
void printDoublyLinkedListReverse(DNode* tail) {
    DNode* curr = tail;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << endl;
}

/*
 * Problem: Delete all occurrences of a Key in Doubly Linked List
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/delete-all-occurrences-of-a-given-key-in-a-doubly-linked-list/1
 *
 * Delete all nodes with given key from doubly linked list.
 * Example: DLL: 2<->2<->10<->8<->4<->2<->5<->2, key=2 -> 10<->8<->4<->5
 *
 * Time: O(n) - single pass
 * Space: O(1)
 */

// Method 1: Using Dummy Node (Optimal)
DNode* deleteAllOccurrences(DNode* head, int key) {
    // Dummy node simplifies deletion at head
    DNode* dummy = new DNode(-1);
    dummy->next = head;
    if (head) head->prev = dummy;

    DNode* curr = dummy->next;
    while (curr) {
        if (curr->data == key) {
            DNode* nextNode = curr->next; // Save next before deletion
            // Remove curr from DLL: update prev and next pointers
            curr->prev->next = curr->next; // Bypass curr from prev side
            if (curr->next) {
                curr->next->prev = curr->prev; // Bypass curr from next side
            }
            delete curr;
            curr = nextNode; // Move to next node
        } else {
            curr = curr->next; // Move forward
        }
    }
    // Get new head and cleanup dummy
    DNode* newHead = dummy->next;
    if (newHead) newHead->prev = nullptr; // Remove dummy's link
    delete dummy;
    return newHead;
}

// ========== METHOD 2: Recursive Approach ==========
// Time Complexity: O(n), Space Complexity: O(n) due to recursion
DNode* deleteAllOccurrencesRecursive(DNode* head, int key) {
    if (!head) return nullptr;
    
    // Recursively delete from rest of list
    head->next = deleteAllOccurrencesRecursive(head->next, key);
    
    // If current node matches key, delete it
    if (head->data == key) {
        DNode* nextNode = head->next;
        if (nextNode) {
            nextNode->prev = head->prev;
        }
        delete head;
        return nextNode;
    }
    
    return head;
}

int main() {
    cout << "========== METHOD 1: Delete All Occurrences ==========" << endl;
    
    // Test case 1: [2,2,10,8,4,2,5,2], key = 2 -> [10,8,4,5]
    vector<int> arr1 = {2, 2, 10, 8, 4, 2, 5, 2};
    DNode* head1 = arrayToDoublyLinkedList(arr1);
    
    cout << "\nTest case 1:" << endl;
    cout << "Original DLL: ";
    printDoublyLinkedList(head1);
    head1 = deleteAllOccurrences(head1, 2);
    cout << "After deleting all 2s: ";
    printDoublyLinkedList(head1);
    cout << "Expected: 10 8 4 5" << endl;
    
    return 0;
}
