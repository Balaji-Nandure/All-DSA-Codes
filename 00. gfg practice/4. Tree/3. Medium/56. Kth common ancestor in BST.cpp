/*
    Problem Name: Kth common ancestor in BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Search Tree (BST) with n (n >= 2) nodes and two distinct nodes x and y,
    find their k-th common ancestor.
    - Common ancestors are counted starting from the Lowest Common Ancestor (LCA) upwards towards the root:
      * 1st common ancestor = LCA
      * 2nd common ancestor = Parent of LCA
      * k-th common ancestor = k-th node counting upwards from LCA to root.
    - If fewer than k common ancestors exist, return -1.

    Examples:
    Input:
               50
             /    \
           30      70
          /  \    /  \
         20  40  60  80
    k = 2, x = 20, y = 40
    Output: 50
    Explanation: Path of common ancestors from root to LCA is [50, 30].
    1st common ancestor = 30 (LCA), 2nd common ancestor = 50. Output = 50.

    Input:
               50
             /    \
           30      70
          /  \    /  \
         20  40  60  80
    k = 2, x = 40, y = 60
    Output: -1
    Explanation: LCA of 40 and 60 is 50. Total common ancestors = 1 ([50]).
    Since k = 2 > 1, 2nd common ancestor does not exist -> return -1.

    Constraints:
    1 <= n, k <= 10^5
    1 <= node->data, x, y <= 10^9

    Expected Complexities:
    Time Complexity: O(H), where H is the height of the BST. In worst case O(N) for skewed BST.
    Space Complexity: O(H), to store the path of common ancestors.

    Love Babbar Style Approach:
    BST Search Traversal + Path Vector:

    1. INTUITION:
       - Leveraging BST properties (left < root < right), we can trace the common ancestor path from root:
         * If both `x` and `y` are smaller than `root->data`: move to `root->left`.
         * If both `x` and `y` are larger than `root->data`: move to `root->right`.
         * Otherwise (`x` and `y` split across `root` or one equals `root`): `root` is the LCA!
       - Store every visited common ancestor node in a vector `path`.
       - `path` will contain common ancestors in order: `[root, ..., LCA]`.
       - Let `m = path.size()`.
         * If `k > m`: return `-1`.
         * Otherwise, the `k`-th common ancestor counting upwards from LCA is at index `m - k`.

    2. ALGORITHM:
       - `vector<int> path;`
       - While `root != NULL`:
         * `path.push_back(root->data);`
         * `if (x < root->data && y < root->data) root = root->left;`
         * `else if (x > root->data && y > root->data) root = root->right;`
         * `else break;`
       - `int m = path.size();`
       - `if (k > m) return -1;`
       - `return path[m - k];`

    Dry Run:
    Tree root = 50, k = 2, x = 20, y = 40
    - at 50: 20 < 50 and 40 < 50 -> path = [50], move left to 30
    - at 30: 20 < 30 and 40 > 30 -> path = [50, 30], break! (LCA = 30)
    - m = 2, k = 2.
    - m >= k (2 >= 2) -> return path[2 - 2] = path[0] = 50.

    Output: 50 ✓
*/

#include <iostream>
#include <vector>

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
public:
    // GFG Signature
    int kthCommonAncestor(Node *root, int k, int x, int y) {
        vector<int> path;

        // Traverse BST to collect all common ancestors from root down to LCA
        while (root) {
            path.push_back(root->data);

            if (x < root->data && y < root->data) {
                root = root->left;
            } else if (x > root->data && y > root->data) {
                root = root->right;
            } else {
                break; // Found LCA
            }
        }

        int m = path.size();

        // If total common ancestors is less than k, no k-th common ancestor exists
        if (k > m) {
            return -1;
        }

        // k-th common ancestor counting upwards from LCA (path[m - k])
        return path[m - k];
    }
};

int main() {
    Solution ob;

    // Example Tree:
    //            50
    //          /    \
    //        30      70
    //       /  \    /  \
    //      20  40  60  80
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    // Example 1:
    // k = 2, x = 20, y = 40 -> Expected: 50
    cout << "Example 1 (k=2, x=20, y=40): " << ob.kthCommonAncestor(root, 2, 20, 40) << "\n";

    // Example 2:
    // k = 2, x = 40, y = 60 -> Expected: -1 (LCA is 50, only 1 common ancestor exists)
    cout << "Example 2 (k=2, x=40, y=60): " << ob.kthCommonAncestor(root, 2, 40, 60) << "\n";

    // Example 3:
    // k = 1, x = 20, y = 40 -> Expected: 30 (LCA itself)
    cout << "Example 3 (k=1, x=20, y=40): " << ob.kthCommonAncestor(root, 1, 20, 40) << "\n";

    return 0;
}
