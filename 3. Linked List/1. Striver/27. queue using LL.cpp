/*
 * Problem: Implement Queue using Linked List (Adapter Pattern)
 *
 * Implement a queue data structure using a linked list as the underlying
 * container. The queue should support the following operations:
 * - push(x) / enqueue(x): Insert element x at the back of the queue
 * - pop() / dequeue(): Remove and return the front element
 * - front(): Return the front element without removing it
 * - empty(): Check if the queue is empty
 * - size(): Return the number of elements in the queue
 *
 * Time Complexity: O(1) for all operations
 * Space Complexity: O(n) where n is the number of elements
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
class Node {
public:
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Queue class implemented using linked list
class QueueLL {
private:
    Node* frontNode;   // Front of the queue
    Node* rearNode;    // Rear of the queue
    int qSize;         // Number of elements

public:
    // Constructor
    QueueLL() {
        frontNode = nullptr;
        rearNode = nullptr;
        qSize = 0;
    }

    // Destructor to free memory
    ~QueueLL() {
        while (!empty()) {
            pop();
        }
    }

    // Insert element x at the back of the queue
    void push(int x) {
        Node* newNode = new Node(x);
        if (empty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        qSize++;
    }

    // Remove and return the front element
    int pop() {
        if (empty()) {
            cout << "Queue is empty! Cannot pop." << endl;
            return -1; // or throw an exception
        }
        Node* temp = frontNode;
        int value = frontNode->data;
        frontNode = frontNode->next;
        delete temp;
        qSize--;
        if (qSize == 0) rearNode = nullptr;
        return value;
    }

    // Return the front element without removing it
    int front() {
        if (empty()) {
            cout << "Queue is empty! No front element." << endl;
            return -1; // or throw an exception
        }
        return frontNode->data;
    }

    // Check if the queue is empty
    bool empty() {
        return frontNode == nullptr;
    }

    // Return the number of elements in the queue
    int size() {
        return qSize;
    }

    // Display the queue (for debugging/testing)
    void display() {
        if (empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node* curr = frontNode;
        cout << "Queue (front to rear): ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {
    QueueLL q;

    cout << "=== Testing Queue Operations ===" << endl;

    cout << "\n1. Pushing elements: 10, 20, 30, 40" << endl;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.display();
    cout << "Queue size: " << q.size() << endl;
    cout << "Front element: " << q.front() << endl;

    cout << "\n2. Popping elements:" << endl;
    cout << "Popped: " << q.pop() << endl;
    q.display();
    cout << "Queue size: " << q.size() << endl;
    cout << "Front element: " << q.front() << endl;

    cout << "\n3. Popping more elements:" << endl;
    cout << "Popped: " << q.pop() << endl;
    cout << "Popped: " << q.pop() << endl;
    q.display();
    cout << "Queue size: " << q.size() << endl;

    cout << "\n4. Checking empty():" << endl;
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;
    cout << "Popped: " << q.pop() << endl;
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    cout << "\n5. Trying to pop from empty queue:" << endl;
    q.pop();

    cout << "\n6. Pushing more elements:" << endl;
    q.push(100);
    q.push(200);
    q.push(300);
    q.display();
    cout << "Queue size: " << q.size() << endl;
    cout << "Front element: " << q.front() << endl;

    return 0;
}
