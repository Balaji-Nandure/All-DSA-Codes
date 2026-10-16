/**
 * Problem: Find the Median of BST in O(N) Time and O(1) Space
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Storing nodes in an array or using recursion takes O(N) or O(H) auxiliary space.
 * - Here, we are strictly required to compute the Median in TRUE O(1) AUXILIARY SPACE (no recursion, no stack),
 *   necessitating Morris Inorder Traversal (threaded binary tree simulation).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Morris Inorder Traversal (Threaded Inorder):
 *   - By temporarily establishing right-child "threads" from the Inorder predecessor back to the current node,
 *     we traverse the tree in Inorder without maintaining any stack!
 *   - Pass 1 (Count Nodes):
 *     - Run Morris Inorder Traversal to count total nodes `N` in O(N) time and O(1) space.
 *   - Pass 2 (Locate Median):
 *     - If `N` is odd: Median is the `(N + 1) / 2`-th node.
 *     - If `N` is even: Median is the average of `(N / 2)`-th and `(N / 2 + 1)`-th nodes.
 *     - Run Morris Inorder Traversal again until the target node counts are reached, then restore all threads.
 * 
 * TIME COMPLEXITY:
 * - O(N): Two passes of Morris traversal, each edge traversed at most 4 times.
 * 
 * SPACE COMPLEXITY:
 * - O(1): Strictly constant auxiliary memory.
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Morris Inorder Traversal to count nodes
int countNodesMorris(Node* root) {
    int count = 0;
    Node* curr = root;

    while (curr != nullptr) {
        if (curr->left == nullptr) {
            count++;
            curr = curr->right;
        } else {
            // Find inorder predecessor
            Node* pre = curr->left;
            while (pre->right != nullptr && pre->right != curr) {
                pre = pre->right;
            }

            if (pre->right == nullptr) {
                pre->right = curr; // Make thread
                curr = curr->left;
            } else {
                pre->right = nullptr; // Remove thread
                count++;
                curr = curr->right;
            }
        }
    }

    return count;
}

float findMedian(Node* root) {
    if (!root) return 0;

    int n = countNodesMorris(root);
    int currCount = 0;
    Node* prevNode = nullptr;
    float median = 0;

    Node* curr = root;
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            currCount++;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if current Inorder count matches the median position(s)
            if (n % 2 != 0 && currCount == (n + 1) / 2) {
                median = curr->data;
            } else if (n % 2 == 0) {
                if (currCount == n / 2) prevNode = curr;
                else if (currCount == (n / 2) + 1) {
                    median = (prevNode->data + curr->data) / 2.0f;
                }
            }

            curr = curr->right;
        } else {
            Node* pre = curr->left;
            while (pre->right != nullptr && pre->right != curr) {
                pre = pre->right;
            }

            if (pre->right == nullptr) {
                pre->right = curr; // Create thread
                curr = curr->left;
            } else {
                pre->right = nullptr; // Sever thread
                currCount++;

                if (n % 2 != 0 && currCount == (n + 1) / 2) {
                    median = curr->data;
                } else if (n % 2 == 0) {
                    if (currCount == n / 2) prevNode = curr;
                    else if (currCount == (n / 2) + 1) {
                        median = (prevNode->data + curr->data) / 2.0f;
                    }
                }

                curr = curr->right;
            }
        }
    }

    return median;
}

int main() {
    // Odd count BST:
    //          6
    //        /   \
    //       3     8
    //      / \   / \
    //     1   4 7   9
    // Inorder: 1 3 4 6 7 8 9 (N = 7, median is 4th element = 6)
    Node* root = new Node(6);
    root->left = new Node(3);
    root->right = new Node(8);
    root->left->left = new Node(1);
    root->left->right = new Node(4);
    root->right->left = new Node(7);
    root->right->right = new Node(9);

    std::cout << "Median of odd BST: " << findMedian(root) << "\n"; // 6

    return 0;
}
