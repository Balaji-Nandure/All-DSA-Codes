/*
    Problem Name: Construct a Full Binary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays pre[] and preMirror[] of size n containing unique elements, where pre[]
    represents the preorder traversal of a Full Binary Tree and preMirror[] represents the preorder
    traversal of its mirror tree, construct the original full binary tree and return its root.

    Note:
    - A Full Binary Tree is a binary tree where every node has either 0 or 2 children.
    - All elements are unique.

    Examples:
    Input: pre[] = [0, 1, 2], preMirror[] = [0, 2, 1]
    Output: [0, 1, 2]
    Explanation:
           0
         /   \
        1     2

    Input: pre[] = [1, 2, 4, 5, 3, 6, 7], preMirror[] = [1, 3, 7, 6, 2, 5, 4]
    Output: [1, 2, 4, 5, 3, 6, 7]

    Constraints:
    1 <= pre.size() <= 10^5
    0 <= pre[i] <= 10^9
    1 <= preMirror.size() <= 10^5
    0 <= preMirror[i] <= 10^9

    Expected Complexities:
    Time Complexity: O(N), using unordered_map for O(1) index lookups of preMirror[].
    Space Complexity: O(N), for hash map and recursion stack.

    Love Babbar Style Approach:
    Preorder + Mirror Preorder Range Partitioning:

    1. INTUITION:
       - Preorder of Original Tree: `[Root, Left_Subtree, Right_Subtree]`
       - Preorder of Mirror Tree:   `[Root, Right_Subtree_Mirrored, Left_Subtree_Mirrored]`
       - Notice:
         * The first element of `pre[]` is the `root`.
         * The next element `val = pre[preIndex]` is the root of the LEFT subtree.
         * In `preMirror[]`, `val` marks the START of the Left Subtree range (`[mirrorIndex, mirrorHigh]`).
         * Consequently, elements in `preMirror[]` BEFORE `mirrorIndex` (`[mirrorLow + 1, mirrorIndex - 1]`)
           belong to the RIGHT Subtree!

    2. ALGORITHM:
       - Maintain `preIndex` initialized to 0 and `unordered_map<int, int> mp` mapping `preMirror[i]` to `i`.
       - Helper `solve(pre, preMirror, preIndex, mirrorLow, mirrorHigh, size, mp)`:
         * `if (preIndex >= size || mirrorLow > mirrorHigh) return NULL;`
         * Create `Node* root = new Node(pre[preIndex++]);`
         * `if (mirrorLow == mirrorHigh || preIndex >= size) return root;`
         * Find `mirrorIndex = mp[pre[preIndex]];`
         * `if (mirrorIndex <= mirrorHigh)`:
           - `root->left = solve(pre, preMirror, preIndex, mirrorIndex, mirrorHigh, size, mp);`
           - `root->right = solve(pre, preMirror, preIndex, mirrorLow + 1, mirrorIndex - 1, size, mp);`
         * Return `root`.

    Dry Run:
    pre[] = [0, 1, 2], preMirror[] = [0, 2, 1]
    - root = 0. preIndex = 1.
    - val = 1. mp[1] = 2.
    - Left child range in preMirror: [2, 2] -> returns Node(1).
    - Right child range in preMirror: [1, 1] -> returns Node(2).
    - Resulting tree: Root 0 with Left 1 and Right 2 ✓
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
private:
    Node* solve(vector<int>& pre, vector<int>& preMirror, int& preIndex, int mirrorLow, int mirrorHigh, int size, unordered_map<int, int>& mp) {
        if (preIndex >= size || mirrorLow > mirrorHigh) return NULL;

        // Step 1: Create root node from current preIndex element
        Node* root = new Node(pre[preIndex++]);

        // If sub-array has only 1 element or all nodes processed, return root
        if (mirrorLow == mirrorHigh || preIndex >= size) {
            return root;
        }

        // Step 2: Search for next element in preMirror array
        int mirrorIndex = mp[pre[preIndex]];

        // Step 3: Partition preMirror array into Left and Right subtrees
        if (mirrorIndex <= mirrorHigh) {
            // Construct Left subtree from range [mirrorIndex, mirrorHigh]
            root->left = solve(pre, preMirror, preIndex, mirrorIndex, mirrorHigh, size, mp);

            // Construct Right subtree from range [mirrorLow + 1, mirrorIndex - 1]
            root->right = solve(pre, preMirror, preIndex, mirrorLow + 1, mirrorIndex - 1, size, mp);
        }

        return root;
    }

public:
    // GFG Signature (vector<int>& pre, vector<int>& preMirror)
    Node* constructBinaryTree(vector<int>& pre, vector<int>& preMirror) {
        int size = pre.size();
        int preIndex = 0;

        // Hash map for O(1) lookup of elements in preMirror
        unordered_map<int, int> mp;
        for (int i = 0; i < size; i++) {
            mp[preMirror[i]] = i;
        }

        return solve(pre, preMirror, preIndex, 0, size - 1, size, mp);
    }
};

// Helper function to print level order traversal
void printLevelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr) {
            cout << curr->data << " ";
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    cout << "\n";
}

int main() {
    Solution ob;

    // Example 1:
    // pre[] = [0, 1, 2], preMirror[] = [0, 2, 1]
    // Expected Output Level Order: 0 1 2
    vector<int> pre1 = {0, 1, 2};
    vector<int> preMirror1 = {0, 2, 1};

    Node* root1 = ob.constructBinaryTree(pre1, preMirror1);
    cout << "Example 1 Constructed Tree (Level Order): ";
    printLevelOrder(root1);

    // Example 2:
    // pre[] = [1, 2, 4, 5, 3, 6, 7], preMirror[] = [1, 3, 7, 6, 2, 5, 4]
    // Expected Output Level Order: 1 2 3 4 5 6 7
    vector<int> pre2 = {1, 2, 4, 5, 3, 6, 7};
    vector<int> preMirror2 = {1, 3, 7, 6, 2, 5, 4};

    Node* root2 = ob.constructBinaryTree(pre2, preMirror2);
    cout << "Example 2 Constructed Tree (Level Order): ";
    printLevelOrder(root2);

    return 0;
}
