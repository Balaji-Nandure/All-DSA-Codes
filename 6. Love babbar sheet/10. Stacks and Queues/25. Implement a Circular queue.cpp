/**
 * Problem: Implement a Circular Queue (Ring Buffer)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A linear array queue suffers from the "false overflow" problem: once the rear reaches index N-1,
 *   no new items can be enqueued even if elements have been dequeued from the front.
 * - Here, we wrap indices circularly `(index + 1) % capacity` to reuse vacant slots efficiently in fixed memory.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Circular Index Arithmetic:
 *   - `front`: Points to the front element.
 *   - `rear`: Points to the rear element.
 *   - `size`: Tracks the current number of elements (simplifies full/empty condition).
 *   - `enQueue`: Increment `rear = (rear + 1) % capacity`, write `arr[rear] = value`.
 *   - `deQueue`: Increment `front = (front + 1) % capacity`.
 *   - Reclaiming slots via modulo arithmetic prevents memory fragmentation without any element shifts.
 * 
 * TIME COMPLEXITY:
 * - enQueue, deQueue, Front, Rear, isEmpty, isFull: all O(1) time.
 * 
 * SPACE COMPLEXITY:
 * - O(N) fixed capacity array.
 */

#include <iostream>

class MyCircularQueue {
private:
    int* arr;
    int front;
    int rear;
    int capacity;
    int count;

public:
    MyCircularQueue(int k) {
        capacity = k;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~MyCircularQueue() {
        delete[] arr;
    }

    bool enQueue(int value) {
        if (isFull()) return false;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Modulo arithmetic wraps rear to 0 when it hits capacity - 1, reusing dequeued slots.
        rear = (rear + 1) % capacity;
        arr[rear] = value;
        count++;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Advance front forward circularly without shifting array elements.
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    int Front() const {
        if (isEmpty()) return -1;
        return arr[front];
    }

    int Rear() const {
        if (isEmpty()) return -1;
        return arr[rear];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }
};

int main() {
    MyCircularQueue cq(3);
    cq.enQueue(1);
    cq.enQueue(2);
    cq.enQueue(3);
    std::cout << "Is full: " << (cq.isFull() ? "Yes" : "No") << "\n"; // Yes
    std::cout << "Rear: " << cq.Rear() << "\n"; // 3
    cq.deQueue(); // removes 1
    cq.enQueue(4); // enqueues at index 0 (wrapped around)
    std::cout << "Rear after wrap: " << cq.Rear() << "\n"; // 4
    std::cout << "Front: " << cq.Front() << "\n"; // 2

    return 0;
}
