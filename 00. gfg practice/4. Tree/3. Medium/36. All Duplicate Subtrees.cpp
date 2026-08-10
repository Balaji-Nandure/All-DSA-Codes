/*
    Problem Name: All Duplicate Subtrees
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of a binary tree, find all duplicate subtrees present in the tree.
    Two subtrees are considered duplicates if they have the same structure and identical node values at corresponding positions.
    Return the root node of each duplicate subtree.

    Examples:
    Input: root = [1, 2, 3, 4, N, 2, 4, N, N, 4]
    Output: Roots of duplicate subtrees (e.g. Subtree 4 and Subtree 2->4)

    Input: root = [5, 4, 6, 3, 4, N, N, N, N, 3, 6]
    Output: Subtree rooted at 3 and Subtree rooted at 6.

    Constraints:
    1 <= height of binary tree <= 10^3

    Expected Complexities:
    Time Complexity: O(N^2) or O(N) depending on string serialization length.
    Space Complexity: O(N) for hash map storing subtree serialization strings and recursion stack.

    Love Babbar Style Approach:
    Tree Serialization via Postorder DFS + Hash Map Frequency Tracking:

    1. INTUITION:
       - How do we uniquely identify the structure and values of a subtree?
       - We serialize each subtree into a string representation using Postorder DFS:
         `curr = to_string(root->data) + "," + left_string + "," + right_string`
       - We use an `unordered_map<string, int>` to store the frequency of each serialized subtree string.
       - IMPORTANT: When `mp[curr] == 2` (i.e. exactly the second time we see this identical subtree string),
         we push `root` into `ans`!
       - Why `mp[curr] == 2` instead of `mp[curr] > 1`?
         * If a duplicate subtree appears 3 or 4 times, we ONLY want to add its root ONCE to `ans`!

    2. ALGORITHM:
       - Helper `solve(root, mp, ans)`:
         * Base Case: `if (root == NULL)` return `"#"` (null marker).
         * `string left = solve(root->left, mp, ans);`
         * `string right = solve(root->right, mp, ans);`
         * `string curr = to_string(root->data) + "," + left + "," + right;`
         * Increment frequency: `mp[curr]++;`
         * If `mp[curr] == 2`, push `root` into `ans`.
         * Return `curr`.

    Dry Run:
            1
           / \
          2   3
         /   / \
        4   2   4
           /
          4

    Subtree rooted at 4: string = "4,#,#"
    - First Node 4 (left of 2): mp["4,#,#"] = 1
    - Second Node 4 (left of second 2): mp["4,#,#"] = 2 -> Add Node 4 to ans!
    - Third Node 4 (right of 3): mp["4,#,#"] = 3 -> (already added, don't add again)

    Subtree rooted at 2: string = "2,4,#,#,#"
    - Left Node 2: mp["2,4,#,#,#"] = 1
    - Right Node 2: mp["2,4,#,#,#"] = 2 -> Add Node 2 to ans!

    Resulting duplicate roots: {Node 4, Node 2} ✓
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
    string solve(Node* root, unordered_map<string, int>& mp, vector<Node*>& ans) {
        if (root == NULL)
            return "#";

        string left = solve(root->left, mp, ans);
        string right = solve(root->right, mp, ans);

        string curr = to_string(root->data) + "," + left + "," + right;

        mp[curr]++;

        // Add root to ans ONLY when count hits 2 (to avoid duplicate additions)
        if (mp[curr] == 2)
            ans.push_back(root);

        return curr;
    }

public:
    // GFG Signature
    vector<Node*> printAllDups(Node* root) {
        unordered_map<string, int> mp;
        vector<Node*> ans;
        solve(root, mp, ans);
        return ans;
    }
};

// Helper function to print Preorder Traversal of a tree
void printPreorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    Solution ob;

    // Example 1:
    //            1
    //          /   \
    //         2     3
    //        /     / \
    //       4     2   4
    //            /
    //           4
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->left->left = new Node(4);
    root1->right->left = new Node(2);
    root1->right->right = new Node(4);
    root1->right->left->left = new Node(4);

    vector<Node*> dups1 = ob.printAllDups(root1);

    cout << "Example 1 Duplicate Subtrees (Preorder of each root):\n";
    for (Node* dupRoot : dups1) {
        cout << "Subtree (Root " << dupRoot->data << "): ";
        printPreorder(dupRoot);
        cout << "\n";
    }
    cout << "\n";

    // Example 2:
    //          5
    //        /   \
    //       4     6
    //      / \   / \
    //     3   4 N   N
    //        / \
    //       3   6
    Node* root2 = new Node(5);
    root2->left = new Node(4);
    root2->right = new Node(6);
    root2->left->left = new Node(3);
    root2->left->right = new Node(4);
    root2->left->right->left = new Node(3);
    root2->left->right->right = new Node(6);

    vector<Node*> dups2 = ob.printAllDups(root2);

    cout << "Example 2 Duplicate Subtrees (Preorder of each root):\n";
    for (Node* dupRoot : dups2) {
        cout << "Subtree (Root " << dupRoot->data << "): ";
        printPreorder(dupRoot);
        cout << "\n";
    }

    return 0;
}
