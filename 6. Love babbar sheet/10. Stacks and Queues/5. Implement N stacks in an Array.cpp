/**
 * Problem: Implement "N" (or K) Stacks in a Single Array
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Implement 2 stack in an array", two stacks grew toward each other from extremes (indices 0 and N-1).
 * - But with K >= 3 stacks, bidirectional collision no longer works. Static partitioning (N/K each) wastes
 *   space if one stack overflows while another is empty.
 * - Here, we share a single array among K stacks dynamically with zero memory waste.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Free List + Next Pointer Tracking:
 *   - `arr[N]`: Stores actual stack elements.
 *   - `top[K]`: Stores index of the top element for each of the K stacks (initialized to -1).
 *   - `next[N]`: Dual-purpose array:
 *       1. If slot `i` is part of a stack, `next[i]` stores the index of the element beneath it.
 *       2. If slot `i` is free, `next[i]` points to the next available free slot in the array.
 *   - `free`: Tracks the head of the free linked list (initialized to 0).
 * - This provides true O(1) push and pop for all K stacks with NO wasted slots.
 * 
 * TIME COMPLEXITY:
 * - push(x, sn): O(1)
 * - pop(sn): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N + K) auxiliary memory for `top` and `next` arrays.
 */

#include <iostream>
#include <vector>

class KStacks {
private:
    int* arr;   // Size n: stores actual contents
    int* top;   // Size k: stores index of top element of stack i
    int* next;  // Size n: stores next item or next free slot
    int n, k;
    int freeSpot; // Beginning of free list

public:
    KStacks(int kStacks, int capacity) : k(kStacks), n(capacity) {
        arr = new int[n];
        top = new int[k];
        next = new int[n];

        // Initialize all stacks as empty
        for (int i = 0; i < k; i++) top[i] = -1;

        // Initialize free list: 0 -> 1 -> 2 -> ... -> n-1 -> -1
        freeSpot = 0;
        for (int i = 0; i < n - 1; i++) next[i] = i + 1;
        next[n - 1] = -1; // End of free list
    }

    ~KStacks() {
        delete[] arr;
        delete[] top;
        delete[] next;
    }

    // Push 'x' into stack number 'sn' (0 to k-1)
    bool push(int x, int sn) {
        if (freeSpot == -1) {
            std::cout << "Stack Overflow across all stacks!\n";
            return false;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 1. Grab index from free list, advance freeSpot, link to stack top, update top.
        int i = freeSpot;
        freeSpot = next[i];
        next[i] = top[sn];
        top[sn] = i;
        arr[i] = x;

        return true;
    }

    // Pop element from stack number 'sn'
    int pop(int sn) {
        if (top[sn] == -1) {
            std::cout << "Stack Underflow in stack " << sn << "!\n";
            return -1;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 2. Extract top item index, revert top to previous item, attach freed index to free list.
        int i = top[sn];
        top[sn] = next[i];
        next[i] = freeSpot;
        freeSpot = i;

        return arr[i];
    }

    bool isEmpty(int sn) const {
        return top[sn] == -1;
    }
};

int main() {
    int k = 3, n = 10;
    KStacks ks(k, n);

    ks.push(15, 2);
    ks.push(45, 2);

    ks.push(17, 1);
    ks.push(49, 1);
    ks.push(39, 1);

    ks.push(11, 0);
    ks.push(9, 0);
    ks.push(7, 0);

    std::cout << "Popped from stack 2: " << ks.pop(2) << "\n"; // 45
    std::cout << "Popped from stack 1: " << ks.pop(1) << "\n"; // 39
    std::cout << "Popped from stack 0: " << ks.pop(0) << "\n"; // 7

    return 0;
}
