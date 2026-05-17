/*
Problem: Queue using Linked List

GFG: https://www.geeksforgeeks.org/problems/queue-using-linked-list/1

Description:
Implement queue operations using linked list:
1) enqueue(x)  -> insert at rear
2) dequeue()   -> remove from front
3) getFront()  -> return front element else -1
4) isEmpty()   -> true if queue empty
5) size()      -> current number of elements

Approach:
Maintain:
- front pointer
- rear pointer
- count of elements

enqueue:
- Create new node
- If queue is empty, front = rear = new node
- Else rear->next = new node, rear = new node
- count++

dequeue:
- If empty, do nothing
- Remove front node
- Move front to front->next
- If front becomes NULL, rear = NULL
- count--

All operations are O(1).

Time Complexity:
enqueue: O(1), dequeue: O(1), getFront: O(1), isEmpty: O(1), size: O(1)
Space Complexity: O(N)

Pattern: Linked List Implementation of Queue
*/

#include <bits/stdc++.h>
using namespace std;

class QueueNode {
  public:
    int data;
    QueueNode* next;

    QueueNode(int x) {
        data = x;
        next = nullptr;
    }
};

class MyQueue {
  private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int cnt;

  public:
    MyQueue() {
        frontNode = nullptr;
        rearNode = nullptr;
        cnt = 0;
    }

    void enqueue(int x) {
        QueueNode* node = new QueueNode(x);

        if (rearNode == nullptr) {
            frontNode = rearNode = node;
        } else {
            rearNode->next = node;
            rearNode = node;
        }

        cnt++;
    }

    void dequeue() {
        if (frontNode == nullptr) {
            return;
        }

        QueueNode* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;

        if (frontNode == nullptr) {
            rearNode = nullptr;
        }

        cnt--;
    }

    int getFront() {
        if (frontNode == nullptr) {
            return -1;
        }
        return frontNode->data;
    }

    bool isEmpty() {
        return frontNode == nullptr;
    }

    int size() {
        return cnt;
    }
};

