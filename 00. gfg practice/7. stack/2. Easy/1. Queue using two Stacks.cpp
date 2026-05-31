/*
GeeksforGeeks: Queue using two Stacks
Difficulty: Easy

Problem:
Implement a Queue using 2 stacks s1 and s2.
A Query q is of 2 Types
(i) 1 x (a query of this type means pushing 'x' into the queue)
(ii) 2 (a query of this type means to pop element from queue and print the poped element)
Note : If there is no element return -1 as answer while popping.

Example 1:
Input: q=5, queries[][]=[[1, 2], [1, 3], [2], [1, 4], [2]]
Output: [2, 3]
Explanation: 
[1 2] the queue will be [2]
[1 3] the queue will be [2 3]
[2]   poped element will be 2 the queue will be [3]
[1 4] the queue will be [3 4]
[2 ]  poped element will be 3.

Example 2:
Input: q = 4, queries[][] = [[1, 2], [2], [2], [1, 4]]
Output: [2, -1]

Core Idea:
A queue follows FIFO (First-In-First-Out) while a stack follows LIFO (Last-In-First-Out).
To implement a queue using two stacks (`s1` and `s2`), we can make either the `push` operation or the `pop` operation costly.
Making `pop` costly (amortized O(1)) is generally more efficient:
1. `push(x)`: Simply push `x` onto `s1`. This takes O(1) time.
2. `pop()`: A queue needs to pop the oldest element. If `s2` is not empty, the top of `s2` is the oldest element, so we pop and return it.
   If `s2` is empty, we transfer all elements from `s1` to `s2`. Because stacks are LIFO, moving elements from one stack to another reverses their order, perfectly aligning them in FIFO order on `s2`. Then, pop and return from `s2`.

Approach (Method 2 - Amortized O(1) pop):
- `push(x)`:
  - `s1.push(x)`
- `pop()`:
  - If both `s1` and `s2` are empty, return -1.
  - If `s2` is empty, while `s1` is not empty, `s2.push(s1.top())` and `s1.pop()`.
  - Store the top of `s2` in a variable `res`.
  - `s2.pop()`.
  - Return `res`.

Time Complexity:
- Push: O(1)
- Pop: Amortized O(1). In the worst case (when `s2` is empty), it is O(N) to transfer elements, but each element is moved at most twice (once to `s2`, once popped from `s2`).
Space Complexity: O(N) where N is the number of elements in the queue, to store the elements in stacks.

GFG Link:
https://www.geeksforgeeks.org/problems/queue-using-two-stacks/1
*/

#include <iostream>
#include <stack>

using namespace std;

class StackQueue {
private:
    stack<int> s1;
    stack<int> s2;

public:
    // Function to push an element in queue by using 2 stacks.
    void push(int B) {
        // Push element onto s1
        s1.push(B);
    }

    // Function to pop an element from queue by using 2 stacks.
    int pop() {
        // If both stacks are empty, queue is empty
        if (s1.empty() && s2.empty()) {
            return -1;
        }

        // If s2 is empty, transfer all elements from s1 to s2
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        // Pop the top element from s2, which represents the front of the queue
        int topElement = s2.top();
        s2.pop();
        return topElement;
    }
};

/*
Dry Run — Example 1:
Queries: [[1, 2], [1, 3], [2], [1, 4], [2]]

State 0: 
s1 = [], s2 = []

Query 1: [1, 2] -> push(2)
s1 = [2], s2 = []

Query 2: [1, 3] -> push(3)
s1 = [2, 3] (top is 3), s2 = []

Query 3: [2] -> pop()
s2 is empty. Transfer s1 to s2.
s1 top (3) -> s2, s1 pop.
s1 top (2) -> s2, s1 pop.
s1 = [], s2 = [3, 2] (top is 2).
Pop from s2. Result = 2.
s1 = [], s2 = [3].

Query 4: [1, 4] -> push(4)
s1 = [4], s2 = [3]

Query 5: [2] -> pop()
s2 is not empty. Top of s2 is 3.
Pop from s2. Result = 3.
s1 = [4], s2 = [].

Output: [2, 3]
*/
