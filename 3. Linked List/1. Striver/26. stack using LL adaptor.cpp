/*
 * Problem: Implement Stack using Linked List (Adapter Pattern)
 * 
 * Implement a stack data structure using a linked list as the underlying
 * container. The stack should support the following operations:
 * - push(x): Insert element x at the top of the stack
 * - pop(): Remove and return the top element
 * - top(): Return the top element without removing it
 * - empty(): Check if the stack is empty
 * - size(): Return the number of elements in the stack
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

// Stack class implemented using linked list
class Stack {
private:
    Node* head;  // Top of the stack (head of linked list)
    int stackSize;  // Number of elements in the stack

public:
    // Constructor
    Stack() {
        head = nullptr;
        stackSize = 0;
    }

    // Destructor to free memory
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    // Push element x onto the stack
    void push(int x) {
        Node* newNode = new Node(x);
        newNode->next = head;
        head = newNode;
        stackSize++;
    }

    // Pop the top element from the stack
    int pop() {
        if (empty()) {
            cout << "Stack is empty! Cannot pop." << endl;
            return -1;  // or throw an exception
        }
        Node* temp = head;
        int value = head->data;
        head = head->next;
        delete temp;
        stackSize--;
        return value;
    }

    // Return the top element without removing it
    int top() {
        if (empty()) {
            cout << "Stack is empty! No top element." << endl;
            return -1;  // or throw an exception
        }
        return head->data;
    }

    // Check if the stack is empty
    bool empty() {
        return head == nullptr;
    }

    // Return the number of elements in the stack
    int size() {
        return stackSize;
    }

    // Display the stack (for debugging/testing)
    void display() {
        if (empty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        Node* curr = head;
        cout << "Stack (top to bottom): ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};