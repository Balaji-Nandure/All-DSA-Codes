/**
 * Problem: Count pairs from 2 BST whose sum is equal to given value "X" (Brothers From Different Roots)
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A 2-Sum problem on two arrays uses two pointers moving from opposite ends.
 * - Here, we perform the Two-Pointer 2-Sum technique DIRECTLY ON TWO BSTs IN REAL-TIME without
 *   flattening them into arrays, using two stacks to emulate forward and reverse iterators.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Simultaneous Forward & Reverse Inorder Iterators:
 *   - Stack `s1`: Performs forward Inorder on BST 1 (ascending stream).
 *   - Stack `s2`: Performs reverse Inorder on BST 2 (descending stream).
 *   - At each step:
 *     - `val1 = s1.top()->data`, `val2 = s2.top()->data`.
 *     - If `val1 + val2 == X`:
 *       - Valid pair found! Increment `count`.
 *       - Advance BOTH iterators (`s1` and `s2`).
 *     - If `val1 + val2 < X`:
 *       - Sum is too small; advance `s1` (increasing iterator) to a larger value.
 *     - If `val1 + val2 > X`:
 *       - Sum is too large; advance `s2` (decreasing iterator) to a smaller value.
 *   - Terminates when either stack becomes empty.
 * 
 * TIME COMPLEXITY:
 * - O(N1 + N2): Each node is pushed and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(H1 + H2): Stacks store only nodes along active paths (minimal memory).
 */

#include <iostream>
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int countPairs(Node* root1, Node* root2, int x) {
    if (!root1 || !root2) return 0;

    std::stack<Node*> s1, s2;
    Node* top1 = nullptr;
    Node* top2 = nullptr;
    int count = 0;

    while (true) {
        // Advance s1 to next smallest element in BST 1 (forward inorder)
        while (root1 != nullptr) {
            s1.push(root1);
            root1 = root1->left;
        }

        // Advance s2 to next largest element in BST 2 (reverse inorder)
        while (root2 != nullptr) {
            s2.push(root2);
            root2 = root2->right;
        }

        if (s1.empty() || s2.empty()) break;

        top1 = s1.top();
        top2 = s2.top();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Two-pointer comparison on live BST iterators: advance smallest on < X, largest on > X, both on == X.
        if (top1->data + top2->data == x) {
            count++;
            s1.pop();
            s2.pop();
            root1 = top1->right;
            root2 = top2->left;
        } else if (top1->data + top2->data < x) {
            s1.pop();
            root1 = top1->right; // Seek larger value in BST 1
        } else {
            s2.pop();
            root2 = top2->left;  // Seek smaller value in BST 2
        }
    }

    return count;
}

int main() {
    // BST 1:
    //      5
    //     / \
    //    3   7
    //   / \ / \
    //  2  4 6  8
    Node* root1 = new Node(5);
    root1->left = new Node(3);
    root1->right = new Node(7);
    root1->left->left = new Node(2);
    root1->left->right = new Node(4);
    root1->right->left = new Node(6);
    root1->right->right = new Node(8);

    // BST 2:
    //      10
    //     /  \
    //    6    15
    //   / \   / \
    //  3   8 11 18
    Node* root2 = new Node(10);
    root2->left = new Node(6);
    root2->right = new Node(15);
    root2->left->left = new Node(3);
    root2->left->right = new Node(8);
    root2->right->left = new Node(11);
    root2->right->right = new Node(18);

    int x = 16;
    // Pairs summing to 16: (5, 11), (6, 10), (8, 8) -> 3 pairs
    std::cout << "Pairs with sum " << x << ": " << countPairs(root1, root2, x) << "\n"; // 3

    return 0;
}
