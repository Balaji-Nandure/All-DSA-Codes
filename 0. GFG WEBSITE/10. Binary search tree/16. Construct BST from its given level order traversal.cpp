/*
Problem:
Construct BST from its Given Level Order Traversal

Approach (Optimal – Queue + Range Validation):
- First element is the root.
- Maintain a queue of nodes with valid (low, high) ranges.
- For each element in level order:
  - Insert as left or right child only if it falls in range.
- Each element is processed exactly once.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

// Builds a BST from given level order traversal using queue + range checking.
// For each value, assign it as left/right child only if it fits the subtree range.
// Each node in queue holds: (node_ptr, allowed_min, allowed_max).

class Solution {
public:
    Node* constructBST(vector<int>& level) {
        if (level.empty()) return NULL;

        Node* root = new Node(level[0]);
        // Queue holds: (Node pointer, min allowed value, max allowed value)
        queue<tuple<Node*, int, int>> q;
        q.push({root, INT_MIN, INT_MAX});

        int i = 1; // Index in level order array

        while (i < level.size()) {
            // Get (node, min, max) for placement
            auto [node, low, high] = q.front();
            q.pop();

            // Place as left child if it fits in (low, node->data)
            if (i < level.size() && level[i] > low && level[i] < node->data) {
                node->left = new Node(level[i]);
                q.push({node->left, low, node->data});
                i++;
            }

            // Place as right child if it fits in (node->data, high)
            if (i < level.size() && level[i] > node->data && level[i] < high) {
                node->right = new Node(level[i]);
                q.push({node->right, node->data, high});
                i++;
            }
        }

        return root;
    }
};