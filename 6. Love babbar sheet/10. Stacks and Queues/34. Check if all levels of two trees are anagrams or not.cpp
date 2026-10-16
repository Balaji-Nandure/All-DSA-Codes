/**
 * Problem: Check if all levels of two trees are anagrams or not
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Two trees may have completely different structural topologies (e.g. left-skewed vs balanced),
 *   yet possess identical multi-sets of node values at every horizontal depth level.
 * - Here, we perform synchronous Level-Order Traversal using two Queues to compare tree levels as anagram multi-sets.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Synchronous BFS with Frequency Hash Map:
 *   - Initialize `q1` with root of Tree 1 and `q2` with root of Tree 2.
 *   - While both queues are non-empty:
 *     - If `q1.size() != q2.size()`, level sizes differ -> NOT anagrams!
 *     - Create a frequency map `unordered_map<int, int> freq`.
 *     - For each node at this level:
 *       - Increment frequency for nodes from `q1`, push children to `q1`.
 *       - Decrement frequency for nodes from `q2`, push children to `q2`.
 *     - If any count in `freq` is non-zero, this level is NOT an anagram -> return false!
 *   - If one tree is taller than the other, return false.
 * 
 * TIME COMPLEXITY:
 * - O(N): Every node in both trees is visited exactly once.
 * 
 * SPACE COMPLEXITY:
 * - O(W): Where W is maximum width of the trees (queue memory).
 */

#include <iostream>
#include <queue>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool areAnagrams(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;

    std::queue<TreeNode*> q1, q2;
    q1.push(root1);
    q2.push(root2);

    while (!q1.empty() && !q2.empty()) {
        int n1 = q1.size();
        int n2 = q2.size();

        if (n1 != n2) return false;

        std::unordered_map<int, int> freq;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Count values across Tree 1's level and subtract values across Tree 2's level simultaneously.
        for (int i = 0; i < n1; i++) {
            TreeNode* node1 = q1.front(); q1.pop();
            freq[node1->val]++;

            if (node1->left) q1.push(node1->left);
            if (node1->right) q1.push(node1->right);
        }

        for (int i = 0; i < n2; i++) {
            TreeNode* node2 = q2.front(); q2.pop();
            freq[node2->val]--;

            if (node2->left) q2.push(node2->left);
            if (node2->right) q2.push(node2->right);
        }

        // Verify that all frequencies balanced out to 0
        for (const auto& [val, count] : freq) {
            if (count != 0) return false;
        }
    }

    return q1.empty() && q2.empty();
}

int main() {
    // Tree 1:
    //       1
    //      / \
    //     3   2
    //        / \
    //       5   4
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(2);
    root1->right->left = new TreeNode(5);
    root1->right->right = new TreeNode(4);

    // Tree 2:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);

    std::cout << "Levels are anagrams: " << (areAnagrams(root1, root2) ? "Yes" : "No") << "\n"; // Yes

    return 0;
}
