/*
GeeksforGeeks: Special Stack
Difficulty: Easy

Problem:
Design a data-structure SpecialStack that supports all the stack operations like push(), pop(), isEmpty(), isFull() and an additional operation getMin() which should return the minimum element from the SpecialStack. Your task is to complete all the functions, using a stack data structure.

Example 1:
Input: stack: 18 19 29 15 16
Output: 15
Explanation: The minimum element of the stack is 15.

Example 2:
Input: stack: 34 335 1814 86
Output: 34
Explanation: The minimum element of the stack is 34.

Core Idea:
To retrieve the minimum element in O(1) time, we can maintain an auxiliary stack (let's call it `min_stack`).
Whenever we push an element onto the main stack `s`, we also push the minimum between the new element and the current minimum (which is at the top of `min_stack`) onto `min_stack`.
When we pop from the main stack, we also pop from `min_stack`.
Since the problem requires us to complete global functions passing the main stack `s` by reference, we can use a global `min_stack`. 
To handle multiple test cases cleanly, we simply clear the `min_stack` whenever a `push` operation is called on an empty main stack.

Approach:
1. Define a global `stack<int> min_stack`.
2. `push(s, a)`: 
   - If `s` is empty, it means we are starting a new test case or sequence. We clear `min_stack` to prevent cross-testcase pollution, then push `a` to `min_stack`.
   - If `s` is not empty, push `min(a, min_stack.top())` to `min_stack`.
   - Finally, push `a` to `s`.
3. `isFull(s, n)`: Return `s.size() == n`.
4. `isEmpty(s)`: Return `s.empty()`.
5. `pop(s)`: 
   - Check if `s` is empty, return -1 if so.
   - Pop from both `s` and `min_stack`. Return the popped element from `s`.
6. `getMin(s)`: Return `min_stack.top()`.

Time Complexity: O(1) for all operations.
Space Complexity: O(N) extra space for the `min_stack`.

GFG Link:
https://www.geeksforgeeks.org/problems/special-stack/1
*/

#include <iostream>
#include <stack>

using namespace std;

// Global auxiliary stack to keep track of minimums
stack<int> min_stack;

void push(stack<int>& s, int a) {
    // If the main stack is empty, it implies a new test case or fresh start
    if (s.empty()) {
        // Clear the min_stack to avoid cross-testcase pollution
        while (!min_stack.empty()) {
            min_stack.pop();
        }
        min_stack.push(a);
    } else {
        // Push the minimum of the new element and the current minimum
        min_stack.push(min(a, min_stack.top()));
    }
    s.push(a);
}

bool isFull(stack<int>& s, int n) {
    return s.size() == n;
}

bool isEmpty(stack<int>& s) {
    return s.empty();
}

int pop(stack<int>& s) {
    if (s.empty()) {
        return -1;
    }
    int top_val = s.top();
    s.pop();
    min_stack.pop();
    return top_val;
}

int getMin(stack<int>& s) {
    if (min_stack.empty()) {
        return -1;
    }
    return min_stack.top();
}

/*
Dry Run — Example 1:
Input elements to push: 18, 19, 29, 15, 16

push(18):
s is empty. min_stack cleared.
min_stack.push(18) -> [18]
s.push(18) -> [18]

push(19):
min(19, 18) = 18.
min_stack.push(18) -> [18, 18]
s.push(19) -> [18, 19]

push(29):
min(29, 18) = 18.
min_stack.push(18) -> [18, 18, 18]
s.push(29) -> [18, 19, 29]

push(15):
min(15, 18) = 15.
min_stack.push(15) -> [18, 18, 18, 15]
s.push(15) -> [18, 19, 29, 15]

push(16):
min(16, 15) = 15.
min_stack.push(15) -> [18, 18, 18, 15, 15]
s.push(16) -> [18, 19, 29, 15, 16]

getMin():
Returns min_stack.top() which is 15.

Final Output: 15
*/
