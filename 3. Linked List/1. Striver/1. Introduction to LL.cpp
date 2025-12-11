#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
class Node {
public:
    int data;     // Data value
    Node* next;   // Pointer to next node

    // Constructor with data and next
    Node(int data, Node* next) {
        this->data = data;
        this->next = next;
    }

    // Constructor with only data
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

Node* arrayToLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr; // Return null for empty array
    Node* head = new Node(arr[0]);       // Create head node
    Node* curr = head;                   // Current pointer to traverse
    for (int i = 1; i < arr.size(); ++i) {
        curr->next = new Node(arr[i]);   // Link new node to the list
        curr = curr->next;               // Move to the new node
    }
    return head;                         // Return the head of the list
}

void printLinkedList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int lengthOfLinkedList(Node* head) {
    int length = 0;
    Node* curr = head;
    while(curr) {
        length++;
        curr = curr->next;
    }
    return length;
}

bool searchInLinkedList(Node* head, int key) {
    Node* curr = head;
    while(curr) {
        if(curr->data == key) return true;
        curr = curr->next;
    }
    return false;
}

// Deletes the first node with specified value in the linked list.
// Returns the new head of the list (in case the head was deleted).
Node* deleteNode(Node* head, int value) {
    if (!head) return nullptr;

    // Delete head
    if (head->data == value) {
        Node* temp = head->next;
        delete head;
        return temp;
    }

    Node* curr = head;

    // Find node before the one we want to delete
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }

    // Delete target node if found
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }

    return head;
}

// delete head node
Node* deleteHead(Node* head) {
    if (!head) return nullptr;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

// delete last node
Node* deleteLast(Node* head) {
    if (!head || !head->next) return nullptr;
    Node* curr = head;
    while(curr->next->next) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return head;
}

// delete node at position
Node* deleteNodeAtPosition(Node* head, int position) {
    if (!head) return nullptr;
    Node* curr = head;
    for(int i = 0; i < position - 1 && curr->next; i++) {
        curr = curr->next;
    }
    Node* temp = curr->next;
    curr->next = temp->next;
    delete temp;
    return head;
}

// iinsert at head
Node* insertAtHead(Node* head, int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    return newNode;
}

// insert at tail
Node* insertAtTail(Node* head, int value) {
    Node* newNode = new Node(value);
    if (!head) return newNode;
    Node* curr = head;
    while(curr->next) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}

// insert at position
Node* insertAtPosition(Node* head, int value, int position) {
    Node* newNode = new Node(value);
    if (position == 0) return insertAtHead(head, value);
    Node* curr = head;
    for(int i = 0; i < position - 1 && curr->next; i++) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

// reverse linked list
Node* reverseLinkedList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while(curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main() {
    // Create an array
    vector<int> arr = {2, 5, 8, 7};
    Node* head = arrayToLinkedList(arr);
    printLinkedList(head);
    return 0;
}
