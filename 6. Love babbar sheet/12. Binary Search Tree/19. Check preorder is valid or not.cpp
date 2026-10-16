/**
 * Problem: Check if Given Array can represent Preorder Traversal of Binary Search Tree
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Construct BST from preorder traversal", we assumed the input was valid and built the tree.
 * - Here, we perform an ADMISSIBILITY VALIDATION on an arbitrary integer array to determine if
 *   there exists ANY valid BST that produces this exact preorder sequence.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Monotonic Decreasing Stack with Ancestral Lower Bound:
 *   - In Preorder traversal: Root -> Left Subtree -> Right Subtree.
 *   - As long as elements decrease, they are consecutive left children: push onto stack.
 *   - The moment an element `x > st.top()` appears:
 *     - It signifies that the left subtree of one or more ancestors is finished, and `x` begins a RIGHT subtree.
 *     - Pop all smaller elements from the stack; the LAST popped element was the parent whose right subtree
 *       we are now entering! Update `rootBound = lastPopped`.
 *     - By BST definition, ALL future elements in this right subtree MUST BE STRICTLY GREATER than `rootBound`!
 *     - If any future element `val < rootBound` is seen -> Immediately return false!
 * 
 * TIME COMPLEXITY:
 * - O(N): Each element is pushed and popped from stack at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for stack.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

bool canRepresentBST(const std::vector<int>& pre, int n) {
    std::stack<int> s;
    int rootBound = INT_MIN;

    for (int i = 0; i < n; i++) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If current element lies in the right subtree of rootBound, it can NEVER be smaller than rootBound!
        if (pre[i] < rootBound) {
            return false;
        }

        // Pop elements smaller than pre[i]; the last popped element becomes the new rootBound
        while (!s.empty() && s.top() < pre[i]) {
            rootBound = s.top();
            s.pop();
        }

        s.push(pre[i]);
    }

    return true;
}

int main() {
    std::vector<int> pre1 = {2, 4, 3};
    std::cout << "pre1 is valid BST preorder: " 
              << (canRepresentBST(pre1, pre1.size()) ? "Yes" : "No") << "\n"; // Yes

    std::vector<int> pre2 = {2, 4, 1};
    // 2 is root, 4 is right child -> all subsequent elements must be > 2. But 1 < 2 -> INVALID!
    std::cout << "pre2 is valid BST preorder: " 
              << (canRepresentBST(pre2, pre2.size()) ? "Yes" : "No") << "\n"; // No

    std::vector<int> pre3 = {40, 30, 35, 80, 100};
    std::cout << "pre3 is valid BST preorder: " 
              << (canRepresentBST(pre3, pre3.size()) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
