/*
Problem: Implement Stack using Array

GFG: https://www.geeksforgeeks.org/implement-stack-using-array/

Description: Implement a Stack using an Array, where the size of the array, n is given.
The Stack must support the following operations:

(i) push(x): Insert an element x at the top of the stack.
(ii) pop(): Remove the element from the top of the stack.
(iii) peek(): Return the top element if not empty, else -1.
(iv) isEmpty(): Return true if the stack is empty else return false.
(v) isFull(): Return true if the stack is full else return false.

Examples:

Input: n = 3, queries[][] = [[1, 5], [1, 3], [3], [2], [4], [5]]
Output: [3, false, false]
Explanation: Queries on stack are as follows:
push(5) : Insert 5 at the top of the stack.
push(3) : Insert 3 at the top of the stack.
peek() : Return the top element i.e. 3.
pop() : Remove the top element i.e. 3.
isEmpty() : return false as the stack is not empty.
isFull() : return false as the stack is not full. Capacity = 3.
Input: n = 1, queries[][] = [[2], [3], [4], [1, 9], [5]]
Output: [-1, -1, true, true]
Explanation: Queries on stack are as follows:
pop(): Since stack is empty, nothing is popped.
peek(): Return the top element. Since the stack is empty, return -1.
isEmpty(): Return true as the stack is empty.
push(9): Insert 9 at the top of the stack. The stack will be [9].
isFull(): Return true as the stack is full. Capacity = 1.

Constraints:
1 ≤ n ≤ 103
1 ≤ q ≤ 103
0 ≤ x ≤ 105

Striver Intuition:

Stack follows LIFO (Last In First Out).

We use:
arr[] → to store elements
top   → index of top element

Initially:
top = -1  → stack empty

Operations:
push:
    if top == n-1 → stack full
    else top++ and arr[top] = x

pop:
    if top == -1 → stack empty
    else top--

peek:
    if top == -1 → return -1
    else return arr[top]

isEmpty:
    top == -1

isFull:
    top == n - 1

Pattern:
Design Data Structure using Array + Pointer

Time Complexity:
push = O(1)
pop = O(1)
peek = O(1)
isEmpty = O(1)
isFull = O(1)

Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Stack {
    vector<int> arr;   // Vector to store elements
    int capacity;      // Maximum capacity of stack

public:
    // Constructor: Initialize stack with given capacity
    Stack(int n) {
        capacity = n;
        arr.reserve(n);   // Allocate capacity but size still 0
    }

    // Push element x to top of stack
    void push(int x) {
        if(arr.size() == capacity) {
            return; // Stack full, cannot push
        }
        arr.push_back(x); // Add element to vector
    }

    // Remove top element from stack
    void pop() {
        if(arr.empty()) {
            return; // Stack empty, cannot pop
        }
        arr.pop_back(); // Remove last element
    }

    // Return top element without removing it
    int peek() {
        if(arr.empty()) {
            return -1; // Stack empty
        }
        return arr.back(); // Return last element
    }

    // Check if stack is empty
    bool isEmpty() {
        return arr.empty(); // Empty if vector is empty
    }

    // Check if stack is full
    bool isFull() {
        return (arr.size() == capacity); // Full if size equals capacity
    }
};

/*
Final Summary (Interview Revision):

1. Stack follows LIFO.
2. Use array + top pointer.
3. top = -1 → empty stack.
4. push → increment top, insert element.
5. pop → decrement top.
6. peek → return arr[top].
7. isEmpty → top == -1
8. isFull → top == n-1

Memory Trick:
Push → top++
Pop  → top--
Peek → arr[top]
*/
