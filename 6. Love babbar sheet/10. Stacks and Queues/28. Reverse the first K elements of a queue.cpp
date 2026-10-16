/**
 * Problem: Reverse the first "K" elements of a queue
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Reverse a Queue using recursion", ALL N elements of the queue were reversed.
 * - Here, ONLY the first K elements must be reversed, while the remaining (N - K) elements
 *   must strictly maintain their original relative order.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Three-Step Stack + Queue Shift:
 *   1. Dequeue the first K elements from the queue and push them onto an auxiliary stack `st`.
 *   2. Pop all K elements from `st` and enqueue them back to the rear of the queue.
 *      - Now, the first K elements are reversed, but they are currently sitting behind the (N - K) original elements!
 *   3. Dequeue (N - K) elements from the front of the queue and enqueue them back to the rear one by one.
 *      - This rotates the reversed K elements to the front and restores the (N - K) elements to their proper place.
 * 
 * TIME COMPLEXITY:
 * - O(N): K pushes/pops with stack, plus (N - K) rotations.
 * 
 * SPACE COMPLEXITY:
 * - O(K) auxiliary space for the stack.
 */

#include <iostream>
#include <queue>
#include <stack>

std::queue<int> modifyQueue(std::queue<int> q, int k) {
    if (q.empty() || k <= 0 || k > (int)q.size()) return q;

    std::stack<int> st;

    // Step 1: Dequeue first k elements and push onto stack
    for (int i = 0; i < k; i++) {
        st.push(q.front());
        q.pop();
    }

    // Step 2: Enqueue stack elements back into queue (now reversed at the rear)
    while (!st.empty()) {
        q.push(st.top());
        st.pop();
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Step 3: Dequeue (n - k) remaining front elements and push them to the back to rotate reversed elements to front.
    int remaining = q.size() - k;
    for (int i = 0; i < remaining; i++) {
        q.push(q.front());
        q.pop();
    }

    return q;
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
    for (int i = 1; i <= 5; i++) q.push(i * 10); // 10 20 30 40 50

    int k = 3;
    std::cout << "Original queue: ";
    printQueue(q);

    std::queue<int> res = modifyQueue(q, k);
    std::cout << "After reversing first " << k << " elements: ";
    printQueue(res); // 30 20 10 40 50

    return 0;
}
