/*
GeeksforGeeks: Get min at pop
Difficulty: Easy

Problem:
You are given an integer array arr[]. You need to first push the elements of the array into a stack and then print minimum in the stack at each pop until stack becomes empty.

Example 1:
Input: arr[] = [1, 2, 3, 4, 5]
Output: [1, 1, 1, 1, 1]

Example 2:
Input: arr[] = [1, 6, 43, 1, 2, 0, 5]
Output: [0, 0, 1, 1, 1, 1, 1]

Core Idea:
Instead of just pushing the elements themselves onto the stack, we can push the *minimum* element seen so far.
When we insert a new element, the new minimum for the entire stack up to that point is simply `min(current_element, minimum_of_elements_below_it)`.
Since a stack is LIFO, when we pop elements, the top of our stack will naturally hold the minimum value among all elements currently "in" the stack.

Approach:
1. `_push(arr, n)`:
   - Create a `stack<int> s`.
   - Iterate through the array `arr`.
   - For the first element, push it directly onto the stack.
   - For subsequent elements, push `min(arr[i], s.top())`.
   - Return the stack `s`.
2. `_getMinAtPop(s)`:
   - While the stack is not empty, print `s.top()` followed by a space.
   - Pop the top element.

Time Complexity: O(N) for pushing all elements, and O(N) for popping them.
Space Complexity: O(N) for the stack.

GFG Link:
https://www.geeksforgeeks.org/problems/get-min-at-pop/1
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    // Function to push all the elements into the stack.
    stack<int> _push(int arr[], int n) {
        stack<int> s;
        for (int i = 0; i < n; i++) {
            if (s.empty()) {
                s.push(arr[i]);
            } else {
                // Push the minimum of the current element and the top of the stack
                s.push(min(arr[i], s.top()));
            }
        }
        return s;
    }

    // Function to print minimum value in stack each time while popping.
    void _getMinAtPop(stack<int> s) {
        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
    }
};

/*
Dry Run — Example 2:
Input: arr[] = [1, 6, 43, 1, 2, 0, 5], n = 7

Step 1: _push
i = 0, arr[0] = 1: s is empty, so s.push(1). s = [1]
i = 1, arr[1] = 6: min(6, 1) = 1. s.push(1). s = [1, 1]
i = 2, arr[2] = 43: min(43, 1) = 1. s.push(1). s = [1, 1, 1]
i = 3, arr[3] = 1: min(1, 1) = 1. s.push(1). s = [1, 1, 1, 1]
i = 4, arr[4] = 2: min(2, 1) = 1. s.push(1). s = [1, 1, 1, 1, 1]
i = 5, arr[5] = 0: min(0, 1) = 0. s.push(0). s = [1, 1, 1, 1, 1, 0]
i = 6, arr[6] = 5: min(5, 0) = 0. s.push(0). s = [1, 1, 1, 1, 1, 0, 0]

Step 2: _getMinAtPop
s = [1, 1, 1, 1, 1, 0, 0] (top is 0)
- pop: prints 0. s = [1, 1, 1, 1, 1, 0]
- pop: prints 0. s = [1, 1, 1, 1, 1]
- pop: prints 1. s = [1, 1, 1, 1]
- pop: prints 1. s = [1, 1, 1]
- pop: prints 1. s = [1, 1]
- pop: prints 1. s = [1]
- pop: prints 1. s = []

Final Output: 0 0 1 1 1 1 1
*/
