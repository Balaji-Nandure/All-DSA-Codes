/**
 * Problem: Left View of a Binary Tree
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Level order traversed all nodes at every level.
 * - Left View requires filtering each horizontal level to pick ONLY the very FIRST node encountered
 *   from the left perspective.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Level Order Traversal (BFS):
 *   - At each level of the tree (captured using `queue.size()`), the first node processed (`i == 0`)
 *     is the leftmost node visible from the exterior.
 * - Method 2: Recursive Preorder (Root -> Left -> Right):
 *   - Pass `currentLevel` and track `maxLevel` reached so far.
 *   - If `currentLevel > maxLevel`, this is the first time we are reaching this depth!
 *   - Record `root->data` and update `maxLevel = currentLevel`.
 *   - Recurse left first, then right.
 * 
 * TIME COMPLEXITY:
 * - O(N): Visits each node at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(H) for recursion stack, or O(W) for BFS queue.
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
std::vector<int> leftViewBFS(Node* root) {
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
            // The first node (i == 0) processed at each level is visible from the left view!
            if (i == 0) {
                res.push_back(curr->data);
            }

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    return res;
}

// Recursive Approach
void leftViewDFS(Node* root, int level, int& maxLevel, std::vector<int>& res) {
    if (!root) return;

    if (level > maxLevel) {
        res.push_back(root->data);
        maxLevel = level;
    }

    leftViewDFS(root->left, level + 1, maxLevel, res);
    leftViewDFS(root->right, level + 1, maxLevel, res);
}

std::vector<int> leftView(Node* root) {
    std::vector<int> res;
    int maxLevel = 0;
    leftViewDFS(root, 1, maxLevel, res);
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

    std::vector<int> res = leftView(root);
    std::cout << "Left view of tree: ";
    for (int x : res) std::cout << x << " ";
    std::cout << "\n"; // 1 2 4 6

    return 0;
}
