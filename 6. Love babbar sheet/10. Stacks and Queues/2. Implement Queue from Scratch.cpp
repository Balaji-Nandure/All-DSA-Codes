/**
 * Problem: Implement Queue from Scratch
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Stack is Last-In-First-Out (LIFO), whereas Queue is First-In-First-Out (FIFO).
 * - Implementing a queue on an array requires managing two pointers (front and rear) and handling the "drift"
 *   problem where dequeueing wastes initial slots unless a circular array indexing scheme is used.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Circular Array Approach: Wrapping around `(rear + 1) % capacity` and `(front + 1) % capacity` prevents
 *   memory waste and retains O(1) time complexity for enqueue and dequeue without shifting elements.
 * - Linked List Approach: Doubly-ended pointers (`front` and `rear`) enable O(1) append at tail and O(1) drop at head.
 * 
 * TIME COMPLEXITY:
 * - push / enqueue: O(1)
 * - pop / dequeue: O(1)
 * - frontElement: O(1)
 * - isEmpty / isFull: O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N) where N is queue capacity / number of elements.
 */

#include <iostream>

class CircularArrayQueue {
private:
    int* arr;
    int frontIndex;
    int rearIndex;
    int capacity;
    int count;

public:
    CircularArrayQueue(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~CircularArrayQueue() {
        delete[] arr;
    }

    void enqueue(int x) {
        if (isFull()) {
            std::cout << "Queue Overflow!\n";
            return;
        }
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Circular modulo wrap-around prevents index out-of-bounds while reclaiming dequeued slots.
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = x;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            std::cout << "Queue Underflow!\n";
            return -1;
        }
        int val = arr[frontIndex];
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Move front forward with modulo wrap-around rather than shifting any array elements.
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return val;
    }

    int getFront() const {
        if (isEmpty()) return -1;
        return arr[frontIndex];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int size() const {
        return count;
    }
};

// Linked List Queue Implementation
struct QNode {
    int data;
    QNode* next;
    QNode(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue {
private:
    QNode* frontNode;
    QNode* rearNode;
    int count;

public:
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~LinkedListQueue() {
        while (frontNode) {
            QNode* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }

    void enqueue(int x) {
        QNode* node = new QNode(x);
        if (!rearNode) {
            frontNode = rearNode = node;
        } else {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Link existing rear to new node and advance rear pointer in O(1).
            rearNode->next = node;
            rearNode = node;
        }
        count++;
    }

    int dequeue() {
        if (!frontNode) {
            std::cout << "Queue Underflow!\n";
            return -1;
        }
        QNode* temp = frontNode;
        int val = temp->data;
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Advance front; if front becomes null, rear must also be reset to null.
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        count--;
        return val;
    }

    int getFront() const {
        if (!frontNode) return -1;
        return frontNode->data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

int main() {
    CircularArrayQueue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    std::cout << "Front: " << q.getFront() << "\n"; // 10
    std::cout << "Dequeued: " << q.dequeue() << "\n"; // 10
    std::cout << "New Front: " << q.getFront() << "\n"; // 20
    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(60); // uses circularly freed slot
    std::cout << "Size: " << q.size() << "\n"; // 4

    return 0;
}
