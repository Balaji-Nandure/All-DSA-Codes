/**
 * Problem: Find Inorder Successor and Inorder Predecessor in a BST
 * Category: Binary Search Tree
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A naive method performs an Inorder traversal, storing all nodes in an array (O(N) time and O(N) space).
 * - By utilizing BST search branching, we track the tightest upper and lower ancestor bounds,
 *   finding both predecessor and successor in O(H) time and O(1) auxiliary space.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - BST Guided Ancestor Tracking:
 *   - While searching for `key`:
 *     - If `curr->data > key`:
 *       - `curr` is strictly greater than `key`, making it a potential candidate for SUCCESSOR.
 *       - Record `suc = curr`, then branch left (`curr = curr->left`) to seek a tighter (smaller) successor.
 *     - If `curr->data < key`:
 *       - `curr` is strictly smaller than `key`, making it a potential candidate for PREDECESSOR.
 *       - Record `pre = curr`, then branch right (`curr = curr->right`) to seek a tighter (larger) predecessor.
 *     - If `curr->data == key`:
 *       - Predecessor = Maximum element in `curr->left` (if left child exists).
 *       - Successor = Minimum element in `curr->right` (if right child exists).
 *       - Break!
 * 
 * TIME COMPLEXITY:
 * - O(H): Traverses down a single path of height H.
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space (iterative).
 */

#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

void findPreSuc(Node* root, Node*& pre, Node*& suc, int key) {
    pre = nullptr;
    suc = nullptr;
    Node* curr = root;

    while (curr != nullptr) {
        if (curr->data == key) {
            // Predecessor is the maximum in the left subtree
            if (curr->left) {
                Node* temp = curr->left;
                while (temp->right) temp = temp->right;
                pre = temp;
            }

            // Successor is the minimum in the right subtree
            if (curr->right) {
                Node* temp = curr->right;
                while (temp->left) temp = temp->left;
                suc = temp;
            }
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // When branching left, current node is a potential successor; when branching right, it is a potential predecessor.
        if (key < curr->data) {
            suc = curr;
            curr = curr->left;
        } else {
            pre = curr;
            curr = curr->right;
        }
    }
}

int main() {
    //        50
    //       /  \
    //      30   70
    //     /  \  / \
    //    20 40 60 80
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    Node* pre = nullptr;
    Node* suc = nullptr;

    findPreSuc(root, pre, suc, 60);

    std::cout << "For key 60:\n";
    std::cout << "Predecessor: " << (pre ? pre->data : -1) << "\n"; // 50
    std::cout << "Successor: " << (suc ? suc->data : -1) << "\n";   // 70

    return 0;
}
