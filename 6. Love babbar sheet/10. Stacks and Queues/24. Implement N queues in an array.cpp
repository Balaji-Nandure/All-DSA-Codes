/**
 * Problem: Implement "N" (or K) Queues in a Single Array
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Implement N stacks in an Array", each stack only maintained a single `top` index.
 * - Here, each queue requires BOTH a `front` AND a `rear` index to uphold FIFO access while
 *   dynamically sharing the underlying contiguous array via free-list chaining.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Shared Array with Linked Lists via `next[]`:
 *   - `arr[N]`: Actual data elements.
 *   - `front[K]`: Front index for each of the K queues (initialized to -1).
 *   - `rear[K]`: Rear index for each of the K queues (initialized to -1).
 *   - `next[N]`:
 *     - When slot is occupied: points to the next element in the queue.
 *     - When slot is free: points to the next free slot in the free list.
 *   - `free`: Head of free list.
 * - Enqueue:
 *   - Grab free index `i`.
 *   - If queue is empty, `front[qn] = i`; else `next[rear[qn]] = i`.
 *   - Update `rear[qn] = i` and `next[i] = -1`.
 * - Dequeue:
 *   - Extract `i = front[qn]`.
 *   - Advance `front[qn] = next[i]`.
 *   - Reclaim `i` by adding back to free list.
 * 
 * TIME COMPLEXITY:
 * - enqueue(x, qn): O(1)
 * - dequeue(qn): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N + K) auxiliary memory.
 */

#include <iostream>
#include <vector>

class KQueues {
private:
    int* arr;
    int* front;
    int* rear;
    int* next;
    int n, k;
    int freeSpot;

public:
    KQueues(int kQueues, int capacity) : k(kQueues), n(capacity) {
        arr = new int[n];
        front = new int[k];
        rear = new int[k];
        next = new int[n];

        for (int i = 0; i < k; i++) {
            front[i] = -1;
            rear[i] = -1;
        }

        // Initialize free list
        freeSpot = 0;
        for (int i = 0; i < n - 1; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }

    ~KQueues() {
        delete[] arr;
        delete[] front;
        delete[] rear;
        delete[] next;
    }

    bool enqueue(int x, int qn) {
        if (freeSpot == -1) {
            std::cout << "Queue Overflow across all queues!\n";
            return false;
        }

        // 1. Allocate from free list
        int i = freeSpot;
        freeSpot = next[i];

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If queue is empty, front points to i; else link previous rear's next to i.
        if (front[qn] == -1) {
            front[qn] = i;
        } else {
            next[rear[qn]] = i;
        }

        next[i] = -1;
        rear[qn] = i;
        arr[i] = x;

        return true;
    }

    int dequeue(int qn) {
        if (front[qn] == -1) {
            std::cout << "Queue Underflow in queue " << qn << "!\n";
            return -1;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Extract front, advance front to next[front], and return old front to free list.
        int i = front[qn];
        front[qn] = next[i];
        if (front[qn] == -1) {
            rear[qn] = -1; // Queue became empty
        }

        next[i] = freeSpot;
        freeSpot = i;

        return arr[i];
    }

    bool isEmpty(int qn) const {
        return front[qn] == -1;
    }
};

int main() {
    int k = 3, n = 10;
    KQueues kq(k, n);

    kq.enqueue(15, 2);
    kq.enqueue(45, 2);

    kq.enqueue(17, 1);
    kq.enqueue(49, 1);
    kq.enqueue(39, 1);

    kq.enqueue(11, 0);

    std::cout << "Dequeued from queue 2: " << kq.dequeue(2) << "\n"; // 15
    std::cout << "Dequeued from queue 1: " << kq.dequeue(1) << "\n"; // 17
    std::cout << "Dequeued from queue 0: " << kq.dequeue(0) << "\n"; // 11

    return 0;
}
