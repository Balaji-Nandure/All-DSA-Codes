/**
 * Problem: Reverse a Queue using Recursion
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Reverse a stack using recursion", pushing an element to the bottom was non-trivial because stacks
 *   only push to the top.
 * - In a Queue, `push()` natively inserts at the REAR!
 * - By recursively popping elements from the front, storing them in the execution call stack,
 *   and pushing them back as the recursion unwinds, the queue is naturally reversed in O(N) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Call Stack Inversion:
 *   - Base Case: If the queue is empty, simply return.
 *   - Recursive Step:
 *     1. Extract front element: `val = q.front(); q.pop();`
 *     2. Recursively reverse the remaining queue: `reverseQueue(q);`
 *     3. Push `val` back into the queue: `q.push(val);`
 *   - Since the deepest recursive call finishes first, the last element popped from the front
 *     is the very first to be pushed back into the empty queue, achieving full inversion!
 * 
 * TIME COMPLEXITY:
 * - O(N): Each element is dequeued and reenqueued exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) call stack recursion depth.
 */

#include <iostream>
#include <queue>

void reverseQueue(std::queue<int>& q) {
    // Base Case
    if (q.empty()) return;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Hold front element in the call frame, reverse the remainder, then enqueue held element to the rear.
    int val = q.front();
    q.pop();

    reverseQueue(q);

    q.push(val);
}

void printQueue(std::queue<int> q) {
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
}

int main() {
    std::queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    std::cout << "Original queue: ";
    printQueue(q); // 10 20 30 40

    reverseQueue(q);

    std::cout << "Reversed queue: ";
    printQueue(q); // 40 30 20 10

    return 0;
}
