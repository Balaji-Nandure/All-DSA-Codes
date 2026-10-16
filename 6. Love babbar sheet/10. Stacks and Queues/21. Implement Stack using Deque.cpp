/**
 * Problem: Implement Stack and Queue using Deque
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A Deque (double-ended queue) is a generalization that allows insertion and deletion at BOTH ends in O(1).
 * - Here, we show how Stack (LIFO) and Queue (FIFO) are both specializations/subsets of a Deque.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Stack using Deque:
 *   - LIFO means elements enter and exit from the SAME end.
 *   - `push(x)` -> `deque.insert_last(x)`
 *   - `pop()`   -> `deque.delete_last()`
 *   - `top()`   -> `deque.get_last()`
 * - Queue using Deque:
 *   - FIFO means elements enter at one end and exit from the OPPOSITE end.
 *   - `enqueue(x)` -> `deque.insert_last(x)`
 *   - `dequeue()`   -> `deque.delete_first()`
 *   - `front()`     -> `deque.get_first()`
 * 
 * TIME COMPLEXITY:
 * - All operations (push, pop, top, enqueue, dequeue, front): O(1) time.
 * 
 * SPACE COMPLEXITY:
 * - O(N) where N is number of elements stored.
 */

#include <iostream>
#include <deque>

// Stack implementation over Deque
class StackWithDeque {
private:
    std::deque<int> dq;

public:
    void push(int x) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Stack pushes and pops from the same end (the back)
        dq.push_back(x);
    }

    int pop() {
        if (dq.empty()) return -1;
        int val = dq.back();
        dq.pop_back();
        return val;
    }

    int top() const {
        if (dq.empty()) return -1;
        return dq.back();
    }

    bool empty() const {
        return dq.empty();
    }

    int size() const {
        return dq.size();
    }
};

// Queue implementation over Deque
class QueueWithDeque {
private:
    std::deque<int> dq;

public:
    void enqueue(int x) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Queue inserts at back and extracts from front (opposite ends)
        dq.push_back(x);
    }

    int dequeue() {
        if (dq.empty()) return -1;
        int val = dq.front();
        dq.pop_front();
        return val;
    }

    int front() const {
        if (dq.empty()) return -1;
        return dq.front();
    }

    bool empty() const {
        return dq.empty();
    }

    int size() const {
        return dq.size();
    }
};

int main() {
    StackWithDeque s;
    s.push(1);
    s.push(2);
    std::cout << "Stack top: " << s.top() << "\n"; // 2
    std::cout << "Stack pop: " << s.pop() << "\n"; // 2

    QueueWithDeque q;
    q.enqueue(1);
    q.enqueue(2);
    std::cout << "Queue front: " << q.front() << "\n"; // 1
    std::cout << "Queue dequeue: " << q.dequeue() << "\n"; // 1

    return 0;
}
