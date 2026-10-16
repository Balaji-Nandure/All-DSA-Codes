/**
 * Problem: Implement 2 stack in an array
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Implement Stack from Scratch", an array accommodated exactly one stack.
 * - Dividing the array statically into two halves (0 to N/2-1 and N/2 to N-1) results in false overflow
 *   if stack 1 exceeds N/2 even when stack 2 is empty.
 * - Here, we share one contiguous buffer dynamically between two stacks from opposite ends.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Bidirectional Growth:
 *   - Stack 1 begins at index 0 and grows to the right (`top1++`).
 *   - Stack 2 begins at index N-1 and grows to the left (`top2--`).
 *   - Collision condition is strictly `top1 >= top2 - 1`.
 * - This maximizes memory utilization: overflow occurs IF AND ONLY IF total elements == N.
 * 
 * TIME COMPLEXITY:
 * - push1, push2: O(1)
 * - pop1, pop2: O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N) where N is array capacity. Zero wasted memory overhead.
 */

#include <iostream>

class TwoStacks {
private:
    int* arr;
    int size;
    int top1;
    int top2;

public:
    TwoStacks(int n = 100) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }

    ~TwoStacks() {
        delete[] arr;
    }

    // Push into Stack 1
    void push1(int x) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Space exists as long as top1 and top2 have at least one empty cell between them.
        if (top1 < top2 - 1) {
            arr[++top1] = x;
        } else {
            std::cout << "Stack Overflow in Stack 1!\n";
        }
    }

    // Push into Stack 2
    void push2(int x) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Stack 2 moves backwards towards top1.
        if (top1 < top2 - 1) {
            arr[--top2] = x;
        } else {
            std::cout << "Stack Overflow in Stack 2!\n";
        }
    }

    // Pop from Stack 1
    int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        } else {
            return -1; // Underflow
        }
    }

    // Pop from Stack 2
    int pop2() {
        if (top2 < size) {
            return arr[top2++];
        } else {
            return -1; // Underflow
        }
    }
};

int main() {
    TwoStacks ts(5);
    ts.push1(5);
    ts.push2(10);
    ts.push2(15);
    ts.push1(11);
    ts.push2(7);

    // Array is full: Stack 1 has {5, 11}, Stack 2 has {10, 15, 7}
    std::cout << "Popped from stack1: " << ts.pop1() << "\n"; // 11
    ts.push2(40); // Successfully pushes into newly available slot
    std::cout << "Popped from stack2: " << ts.pop2() << "\n"; // 40
    return 0;
}
