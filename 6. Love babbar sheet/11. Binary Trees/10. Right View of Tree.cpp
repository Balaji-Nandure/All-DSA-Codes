/**
 * Problem: Right View of Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Left View, the first node at each depth level was visible.
 * - In Right View, we mirror the observer's perspective: picking the LAST node at each depth level.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Level Order Traversal (BFS):
 *   - At each level `sz = q.size()`, the last node processed (`i == sz - 1`) is the rightmost visible node.
 * - Method 2: Reverse Preorder DFS (Root -> Right -> Left):
 *   - Visit right subtree BEFORE left subtree!
 *   - The first node to arrive at any `level` is guaranteed to be the rightmost node at that horizontal depth.
 * 
 * TIME COMPLEXITY:
 * - O(N): Traverses all nodes once.
 * 
 * SPACE COMPLEXITY:
 * - O(H) for recursion stack or O(W) for BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// BFS Approach
std::vector<int> rightViewBFS(Node* root) {
    std::vector<int> res;
    if (!root) return res;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node* curr = q.front();
            q.pop();

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The last node (i == sz - 1) processed at each level is visible from the right view!
            if (i == sz - 1) {
                res.push_back(curr->data);
            }

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    return res;
}

// DFS Reverse Preorder Approach
void rightViewDFS(Node* root, int level, int& maxLevel, std::vector<int>& res) {
    if (!root) return;

    if (level > maxLevel) {
        res.push_back(root->data);
        maxLevel = level;
    }

    // Right child visited before left child
    rightViewDFS(root->right, level + 1, maxLevel, res);
    rightViewDFS(root->left, level + 1, maxLevel, res);
}

std::vector<int> rightView(Node* root) {
    std::vector<int> res;
    int maxLevel = 0;
    rightViewDFS(root, 1, maxLevel, res);
    return res;
}

int main() {
    //        1
    //      /   \
    //     2     3
    //      \     \
    //       4     5
    //      /
    //     6
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->right = new Node(5);
    root->left->right->left = new Node(6);

    std::vector<int> res = rightView(root);
    std::cout << "Right view of tree: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 1 3 5 6

    return 0;
}
