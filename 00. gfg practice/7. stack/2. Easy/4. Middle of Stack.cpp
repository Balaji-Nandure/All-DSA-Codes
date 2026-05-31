/*
GeeksforGeeks: Middle of Stack
Difficulty: Easy

Problem:
Given a stack st[] of size n, find the middle element of the stack.
Note: In case of even elements, return the middle at the bottom.

Example 1:
Input: st[] = [1, 2, 3, 4, 5]
Output: 3
Explanation: The middle elements is 3.

Example 2:
Input: st[] = [1, 2, 3, 4]
Output: 2
Explanation: The two middle elements are 2 and 3. Since we need the middle element closer to the bottom, the answer is 2.

Core Idea:
To find the middle element of a stack using standard stack operations (pop, top, push), we can determine how many elements to pop to reach the middle.
For a stack of size `n`, the middle element from the bottom is at index `(n - 1) / 2` (0-indexed). 
Since we access from the top, the number of elements we need to pop is `n - 1 - (n - 1) / 2`, which simplifies to `n / 2` (integer division).
We pop `n / 2` elements, store them temporarily, read the top element (which is the middle), and then push the popped elements back to restore the original stack.

Approach:
1. Get the size of the stack: `n = st.size()`.
2. Calculate the number of elements to remove to reach the middle: `popCount = n / 2`.
3. Create a temporary container (like a vector or another stack) to hold the popped elements.
4. Loop `popCount` times:
   - Push `st.top()` to the temporary container.
   - `st.pop()`
5. The `st.top()` is now the middle element. Store it in a variable `midElement`.
6. Restore the stack by pushing the elements from the temporary container back into `st` in reverse order.
7. Return `midElement`.

Time Complexity: O(N) where N is the number of elements in the stack, as we pop and push N/2 elements.
Space Complexity: O(N) for the temporary container to store the popped elements.

GFG Link:
https://www.geeksforgeeks.org/problems/middle-of-stack/1
*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int getMiddle(stack<int>& st) {
        if (st.empty()) return -1; // Edge case, though constraints say size >= 1
        
        int n = st.size();
        int popCount = n / 2;
        vector<int> temp;
        
        // Pop elements to reach the middle
        for (int i = 0; i < popCount; i++) {
            temp.push_back(st.top());
            st.pop();
        }
        
        // The middle element is now at the top
        int midElement = st.top();
        
        // Restore the stack
        for (int i = temp.size() - 1; i >= 0; i--) {
            st.push(temp[i]);
        }
        
        return midElement;
    }
};

/*
Dry Run — Example 2:
Input: st = [1, 2, 3, 4] (bottom is 1, top is 4)

Initial State:
st = [1, 2, 3, 4] (size n = 4)
popCount = 4 / 2 = 2
temp = []

Step 1: Pop popCount elements
i = 0: temp.push_back(4), st.pop() -> st = [1, 2, 3], temp = [4]
i = 1: temp.push_back(3), st.pop() -> st = [1, 2], temp = [4, 3]

Step 2: Get middle element
st.top() is 2.
midElement = 2

Step 3: Restore stack
i = 1 (temp.size() - 1): st.push(temp[1] -> 3) -> st = [1, 2, 3]
i = 0: st.push(temp[0] -> 4) -> st = [1, 2, 3, 4]

Final Output: 2
*/
