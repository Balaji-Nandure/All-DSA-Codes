/**
 * Problem: Interleave the first half of the queue with second half
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems rearranged elements monotonically or reversed subsequences.
 * - Here, we perform an alternating merge (interleaving) of two distinct halves of a FIFO stream:
 *   `q[0], q[N/2], q[1], q[N/2 + 1], ..., q[N/2 - 1], q[N - 1]`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Using an Auxiliary Queue:
 *   - Transfer the first half (size N/2) into helper queue `qHalf`.
 *   - Alternatingly take one from `qHalf` and one from the remaining front of `q`, pushing both to rear.
 * - Method 2: Using a Single Stack (Classic Stack manipulation):
 *   1. Push first half (N/2) into stack `st`.
 *   2. Enqueue stack elements back into `q` (they are now reversed at the rear).
 *   3. Dequeue first half from `q` and enqueue to rear.
 *   4. Push first half into `st` again (re-reversing them into original order!).
 *   5. Interleave one from stack top, one from queue front!
 * 
 * TIME COMPLEXITY:
 * - O(N): A constant number of passes over N elements.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space.
 */

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

void interleaveQueue(std::queue<int>& q) {
    int n = q.size();
    if (n % 2 != 0) return; // Only defined for even length
    int half = n / 2;

    std::queue<int> qHalf;

    // Step 1: Dequeue first half and store into helper queue
    for (int i = 0; i < half; i++) {
        qHalf.push(q.front());
        q.pop();
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Alternately push one element from first half (qHalf) and one element from second half (q front)
    while (!qHalf.empty()) {
        q.push(qHalf.front());
        qHalf.pop();

        q.push(q.front());
        q.pop();
    }
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
    std::vector<int> vals = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int v : vals) q.push(v);

    std::cout << "Original queue: ";
    printQueue(q);

    interleaveQueue(q);

    std::cout << "Interleaved queue: ";
    printQueue(q); // 11 16 12 17 13 18 14 19 15 20

    return 0;
}
