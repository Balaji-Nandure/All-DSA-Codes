/**
 * Problem: Implement Queue using Stacks
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Implement Stack using Queue", we simulated LIFO using FIFO.
 * - Here, we perform the exact dual: simulating FIFO queue using LIFO stacks.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Two Stacks (Input and Output Stacks - Amortized O(1)):
 *   - Maintain two stacks: `sIn` (for enqueue) and `sOut` (for dequeue).
 *   - `enqueue(x)`:
 *     - Directly push onto `sIn` in strictly O(1) time.
 *   - `dequeue()` / `peek()`:
 *     - If `sOut` is NOT empty, its top element is already the oldest element! Pop directly.
 *     - If `sOut` IS empty:
 *       - Pour all elements from `sIn` into `sOut`. This single reversal flips the LIFO order
 *         into the exact FIFO arrival order!
 *       - Then pop from `sOut`.
 *   - Amortized Analysis:
 *     - Every element is pushed into `sIn` once, moved to `sOut` once, and popped from `sOut` once.
 *     - Hence, each element experiences exactly 3 operations over its lifetime -> Amortized O(1)!
 * 
 * TIME COMPLEXITY:
 * - push(x): O(1)
 * - pop(): O(1) amortized, O(N) worst-case
 * - peek(): O(1) amortized
 * 
 * SPACE COMPLEXITY:
 * - O(N) total across the two stacks.
 */

#include <iostream>
#include <stack>

class MyQueue {
private:
    std::stack<int> sIn;
    std::stack<int> sOut;

    void transfer() {
        if (sOut.empty()) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Dumping sIn into sOut reverses the order once, preserving FIFO access for all future pops.
            while (!sIn.empty()) {
                sOut.push(sIn.top());
                sIn.pop();
            }
        }
    }

public:
    void push(int x) {
        sIn.push(x);
    }

    int pop() {
        if (empty()) return -1;
        transfer();
        int val = sOut.top();
        sOut.pop();
        return val;
    }

    int peek() {
        if (empty()) return -1;
        transfer();
        return sOut.top();
    }

    bool empty() const {
        return sIn.empty() && sOut.empty();
    }
};

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "Front element: " << q.peek() << "\n"; // 1
    std::cout << "Popped: " << q.pop() << "\n";         // 1
    q.push(4);
    std::cout << "Popped: " << q.pop() << "\n";         // 2
    std::cout << "Popped: " << q.pop() << "\n";         // 3
    std::cout << "Popped: " << q.pop() << "\n";         // 4
    std::cout << "Is empty: " << (q.empty() ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
