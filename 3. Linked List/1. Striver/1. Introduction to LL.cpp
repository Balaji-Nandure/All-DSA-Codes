/*
 * Problem: Introduction to Linked List
 *
 * Basic operations on singly linked list:
 * - Create linked list from array
 * - Insert/Delete operations
 * - Search and traversal
 * - Reverse linked list
 *
 * Time: O(n) for most operations
 * Space: O(1) for operations, O(n) for storage
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
class Node {
public:
    int data;     // Data value stored in node
    Node* next;   // Pointer to next node

    // Constructor with data and next pointer
    Node(int data, Node* next) {
        this->data = data;
        this->next = next;
    }

    // Constructor with only data (next defaults to nullptr)
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Convert array to linked list
Node* arrayToLinkedList(const vector<int>& arr) {
    // Edge case: empty array
    if (arr.size() == 0) return nullptr;
    // Create head node with first element
    Node* head = new Node(arr[0]);
    Node* curr = head; // Pointer to traverse and build list
    // Create and link remaining nodes
    for (int i = 1; i < arr.size(); ++i) {
        curr->next = new Node(arr[i]); // Link new node
        curr = curr->next; // Move to next node
    }
    return head; // Return head of linked list
}

// Print all elements of linked list
void printLinkedList(Node* head) {
    Node* curr = head;
    // Traverse and print each node
    while(curr) {
        cout << curr->data << " ";
        curr = curr->next; // Move to next node
    }
    cout << endl;
}

// Calculate length of linked list
int lengthOfLinkedList(Node* head) {
    int length = 0;
    Node* curr = head;
    // Count nodes while traversing
    while(curr) {
        length++;
        curr = curr->next;
    }
    return length;
}

// Search for a key in linked list
bool searchInLinkedList(Node* head, int key) {
    Node* curr = head;
    // Traverse and check each node
    while(curr) {
        if(curr->data == key) return true; // Found
        curr = curr->next;
    }
    return false; // Not found
}

// Delete first node with given value
Node* deleteNode(Node* head, int value) {
    if (!head) return nullptr;

    // Special case: delete head node
    if (head->data == value) {
        Node* temp = head->next;
        delete head;
        return temp; // Return new head
    }

    Node* curr = head;
    // Find node before the target node
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }

    // Delete target node if found
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = temp->next; // Bypass target node
        delete temp;
    }

    return head;
}

// Delete head node
Node* deleteHead(Node* head) {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next; // Move head to next node
    delete temp;
    return head; // Return new head
}

// Delete last node (tail)
Node* deleteLast(Node* head) {
    // Edge cases: empty list or single node
    if (!head || !head->next) return nullptr;
    Node* curr = head;
    // Traverse to second last node
    while(curr->next->next) {
        curr = curr->next;
    }
    delete curr->next; // Delete last node
    curr->next = nullptr; // Set new tail
    return head;
}

// Delete node at given position (0-indexed)
Node* deleteNodeAtPosition(Node* head, int position) {
    if (!head) return nullptr;
    Node* curr = head;
    // Traverse to node before target position
    for(int i = 0; i < position - 1 && curr->next; i++) {
        curr = curr->next;
    }
    // Delete node at position
    Node* temp = curr->next;
    curr->next = temp->next;
    delete temp;
    return head;
}

// Insert at head (beginning)
Node* insertAtHead(Node* head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head; // New node points to old head
    return newNode; // Return new head
}

// Insert at tail (end)
Node* insertAtTail(Node* head, int value) {
    Node* newNode = new Node(value);
    // Edge case: empty list
    if (!head) return newNode;
    Node* curr = head;
    // Traverse to last node
    while(curr->next) {
        curr = curr->next;
    }
    curr->next = newNode; // Link new node at end
    return head;
}

// Insert at given position (0-indexed)
Node* insertAtPosition(Node* head, int value, int position) {
    Node* newNode = new Node(value);
    // Special case: insert at head
    if (position == 0) return insertAtHead(head, value);
    Node* curr = head;
    // Traverse to node before target position
    for(int i = 0; i < position - 1 && curr->next; i++) {
        curr = curr->next;
    }
    // Insert new node
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

// Reverse linked list iteratively
Node* reverseLinkedList(Node* head) {
    Node* prev = nullptr; // Previous node (starts as null)
    Node* curr = head; // Current node
    while(curr) {
        Node* next = curr->next; // Save next node
        curr->next = prev; // Reverse the link
        prev = curr; // Move prev forward
        curr = next; // Move curr forward
    }
    return prev; // prev is now the new head
}

int main() {
    // Create an array
    vector<int> arr = {2, 5, 8, 7};
    Node* head = arrayToLinkedList(arr);
    printLinkedList(head);
    return 0;
}
