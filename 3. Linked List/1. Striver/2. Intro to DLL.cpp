/*
 * Problem: Introduction to Doubly Linked List
 *
 * Basic operations on doubly linked list:
 * - Insert/Delete at head, tail, position
 * - Traverse forward and backward
 * - Search operations
 *
 * Time: O(n) for most operations
 * Space: O(1) for operations, O(n) for storage
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in a doubly linked list
class DNode {
public:
    int data;     // Data value
    DNode* next;  // Pointer to next node
    DNode* prev;  // Pointer to previous node

    // Constructor with data, next, and prev pointers
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

// Get length of DLL
int lengthOfDoublyLinkedList(DNode* head) {
    int length = 0;
    DNode* curr = head;
    while (curr) {
        length++;
        curr = curr->next;
    }
    return length;
}

// Search value in DLL
bool searchInDoublyLinkedList(DNode* head, int key) {
    DNode* curr = head;
    while (curr) {
        if (curr->data == key) return true;
        curr = curr->next;
    }
    return false;
}

// Deletes the first node with specified value in the DLL. Returns new head.
DNode* deleteNode(DNode* head, int value) {
    if (!head) return nullptr;
    DNode* curr = head;

    // Delete head node
    if (curr->data == value) {
        DNode* next = curr->next;
        if (next) next->prev = nullptr;
        delete curr;
        return next;
    }

    while (curr) {
        if (curr->data == value) {
            if (curr->prev)
                curr->prev->next = curr->next;
            if (curr->next)
                curr->next->prev = curr->prev;
            delete curr;
            break;
        }
        curr = curr->next;
    }
    return head;
}

// Delete head node
DNode* deleteHead(DNode* head) {
    if (!head) return nullptr;
    DNode* next = head->next;
    if (next) next->prev = nullptr;
    delete head;
    return next;
}

// Delete last node
DNode* deleteLast(DNode* head) {
    if (!head || !head->next) {
        delete head;
        return nullptr;
    }
    DNode* curr = head;
    while (curr->next) curr = curr->next;
    if (curr->prev) curr->prev->next = nullptr;
    delete curr;
    return head;
}

// Delete node at position (0-indexed)
DNode* deleteNodeAtPosition(DNode* head, int position) {
    if (!head) return nullptr;
    if (position == 0) return deleteHead(head);
    DNode* curr = head;
    for (int i = 0; i < position && curr; i++) curr = curr->next;
    if (!curr) return head;
    if (curr->prev)
        curr->prev->next = curr->next;
    if (curr->next)
        curr->next->prev = curr->prev;
    delete curr;
    return head;
}

// Insert at head
DNode* insertAtHead(DNode* head, int value) {
    DNode* newNode = new DNode(value);
    newNode->next = head;
    if (head) head->prev = newNode;
    return newNode;
}

// Insert at tail
DNode* insertAtTail(DNode* head, int value) {
    DNode* newNode = new DNode(value);
    if (!head) return newNode;
    DNode* curr = head;
    while (curr->next) curr = curr->next;
    curr->next = newNode;
    newNode->prev = curr;
    return head;
}

// Insert at position (0-indexed)
DNode* insertAtPosition(DNode* head, int value, int position) {
    if (position == 0) return insertAtHead(head, value);
    DNode* curr = head;
    for (int i = 0; i < position - 1 && curr; i++) curr = curr->next;
    if (!curr) return head; // position too large
    DNode* newNode = new DNode(value);
    newNode->next = curr->next;
    newNode->prev = curr;
    if (curr->next) curr->next->prev = newNode;
    curr->next = newNode;
    return head;
}

// reverse doubly linked list
DNode* reverseDoublyLinkedList(DNode* head) {
    DNode* prev = nullptr;
    DNode* curr = head;

    while (curr) {
        DNode* next = curr->next;   // Store next
        curr->next = prev;          // Reverse next pointer
        curr->prev = next;          // Reverse prev pointer
        prev = curr;                // Move prev forward
        curr = next;                // Move curr forward
    }

    return prev;
}


int main() {
    // Example usage
    vector<int> arr = {2, 5, 8, 7};
    DNode* head = arrayToDoublyLinkedList(arr);
    printDoublyLinkedList(head);

    // Print in reverse
    // Go to tail
    DNode* tail = head;
    while (tail && tail->next) tail = tail->next;
    printDoublyLinkedListReverse(tail);

    return 0;
}
