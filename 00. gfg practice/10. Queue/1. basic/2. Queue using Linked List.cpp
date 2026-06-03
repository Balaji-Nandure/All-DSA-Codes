/*
Problem: Queue using Linked List

GFG: https://www.geeksforgeeks.org/problems/queue-using-linked-list/1

Description:
Implement queue operations using linked list:
- enqueue(x): insert at rear
- dequeue(): remove from front
- getFront(): return front value else -1
- isEmpty(): true if queue empty
- size(): current number of elements

Approach:
Maintain front, rear pointers and a size counter.
All operations are O(1).
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
  public:
    int data;
    Node* next;

    Node(int new_data) {
        data = new_data;
        next = nullptr;
    }
};

class myQueue {
  private:
    Node* front;
    Node* rear;
    int sz;

  public:
    myQueue() {
        front = nullptr;
        rear = nullptr;
        sz = 0;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int x) {
        Node* newNode = new Node(x);

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        sz++;
    }

    void dequeue() {
        if (front == nullptr) return;

        Node* temp = front;
        front = front->next;

        if (front == nullptr) rear = nullptr;

        delete temp;
        sz--;
    }

    int getFront() {
        if (front == nullptr) return -1;
        return front->data;
    }

    int size() {
        return sz;
    }
};

