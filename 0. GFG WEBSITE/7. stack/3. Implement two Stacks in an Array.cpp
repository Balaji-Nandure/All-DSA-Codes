/*
Problem:
Implement Two Stacks in an Array

Design a data structure that supports two stacks using a single array of size S.

Requirements:
- Stack1 grows from left to right.
- Stack2 grows from right to left.
- Overflow occurs when both stacks collide.

Operations:
- push1(x)
- push2(x)
- pop1()
- pop2()

Return -1 on pop if the respective stack is empty.

Example:
push1(2)
push2(3)
push1(4)
pop1() → 4
pop2() → 3

Approach:
- Use an array arr[] of size S.
- Initialize:
  top1 = 0
  top2 = S - 1
- Stack1 occupies indices [0 ... top1-1]
- Stack2 occupies indices [top2+1 ... S-1]
- Overflow when top1 > top2

GeeksforGeeks:
https://www.geeksforgeeks.org/implement-two-stacks-in-an-array/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(1) for all operations

Space Complexity:
O(S)
*/

class twoStacks {
private:
    int *arr;
    int top1, top2, size;

public:
    twoStacks(int S) {
        size = S;
        arr = new int[S];
        top1 = 0;
        top2 = S - 1;
    }

    void push1(int x) {
        if (top1 > top2) return;
        arr[top1++] = x;
    }

    void push2(int x) {
        if (top1 > top2) return;
        arr[top2--] = x;
    }

    int pop1() {
        if (top1 == 0) return -1;
        return arr[--top1];
    }

    int pop2() {
        if (top2 == size - 1) return -1;
        return arr[++top2];
    }
};
        