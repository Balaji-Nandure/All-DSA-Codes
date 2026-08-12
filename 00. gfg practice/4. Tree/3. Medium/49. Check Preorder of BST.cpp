/*
    Problem Name: Check Preorder of BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array arr[] consisting of distinct integers, check if the given array can represent
    the preorder traversal of a Binary Search Tree (BST).

    Examples:
    Input: arr[] = [2, 4, 3]
    Output: true
    Explanation: Preorder [2, 4, 3] forms a valid BST with root 2, left NULL, right 4 (left 3).

    Input: arr[] = [2, 4, 1]
    Output: false
    Explanation: After visiting 2 and then 4 (moving to right subtree of 2), any subsequent element
    must be > 2. Here 1 is < 2 (which is invalid for a BST right subtree!).

    Constraints:
    1 <= arr.size() <= 10^5
    0 <= arr[i] <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the size of arr[]. Each element is pushed and popped from stack at most once.
    Space Complexity: O(N), for the stack.

    Love Babbar Style Approach:
    Monotonic Decreasing Stack + Lower Bound Tracking:

    1. INTUITION:
       - In Preorder traversal of BST (Root -> Left -> Right):
         * As long as we keep encountering SMALLER elements, we are moving down the LEFT branch.
         * When we encounter an element `x` LARGER than the stack top `st.top()`:
           - It means we have finished exploring a left branch and are now moving into a RIGHT subtree!
           - The parent of this right subtree is the LAST popped element from the stack that was < `x`.
           - Every node in this right subtree MUST be strictly GREATER than this parent (`low` bound).
       - Therefore, we update `low = st.top()` for every popped element smaller than `x`.
       - If we ever see an element `x < low`, it breaks the BST property -> return `false`!

    2. ALGORITHM:
       - Maintain a `stack<int> st` and `int low = INT_MIN`.
       - For each element `x` in `arr`:
         * `if (x < low) return false;` (violates lower bound for current subtree).
         * `while (!st.empty() && x > st.top())`:
           - `low = st.top();`
           - `st.pop();`
         * `st.push(x);`
       - Return `true`.

    Dry Run:
    arr[] = [2, 4, 1], low = INT_MIN

    - x = 2: 2 >= low. st=[2]
    - x = 4: 4 > st.top()(2) -> low = 2, pop 2. st=[4]
    - x = 1: 1 < low (1 < 2) -> VIOLATION! Returns false ✓
*/

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    // GFG Signature
    bool canRepresentBST(vector<int>& arr) {
        stack<int> st;
        int low = INT_MIN;

        for (int x : arr) {
            // If current element is smaller than the lower bound, it cannot form a valid BST
            if (x < low) return false;

            // When encountering a larger element x, we unwind the stack
            // and update low to the parent node whose right subtree we are entering
            while (!st.empty() && x > st.top()) {
                low = st.top();
                st.pop();
            }

            // Push current element onto stack
            st.push(x);
        }

        return true;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // arr[] = [2, 4, 3] -> Expected: true
    vector<int> arr1 = {2, 4, 3};
    cout << "Example 1 [2, 4, 3] Can Represent BST: " << (ob.canRepresentBST(arr1) ? "true" : "false") << "\n";

    // Example 2:
    // arr[] = [2, 4, 1] -> Expected: false
    vector<int> arr2 = {2, 4, 1};
    cout << "Example 2 [2, 4, 1] Can Represent BST: " << (ob.canRepresentBST(arr2) ? "true" : "false") << "\n";

    // Example 3:
    // arr[] = [40, 30, 35, 80, 100] -> Expected: true
    vector<int> arr3 = {40, 30, 35, 80, 100};
    cout << "Example 3 [40, 30, 35, 80, 100] Can Represent BST: " << (ob.canRepresentBST(arr3) ? "true" : "false") << "\n";

    return 0;
}
