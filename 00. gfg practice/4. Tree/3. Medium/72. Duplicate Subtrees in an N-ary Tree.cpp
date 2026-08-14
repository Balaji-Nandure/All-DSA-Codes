/*
    Problem Name: Duplicate Subtrees in an N-ary Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the root of an N-ary tree, return the number of distinct subtrees that appear more than once in the tree.
    - Two subtrees are duplicates if they have identical structures and node values.
    - A duplicate subtree is counted only once, regardless of how many times it appears.
    - A subtree consists of a node and all of its descendants.

    Examples:
    Input: root = [1, N, 2, 2, 3, N, 4, N, 4, 4, 3, N, N, N, N]
    Output: 2
    Explanation: The duplicate subtrees are [4] and [3]. Total count = 2.

    Input: root = [1, N, 2, 3, N, 4, 5, 6, N, N, N, N]
    Output: 0
    Explanation: No duplicate subtrees found.

    Constraints:
    1 <= n <= 10^5
    1 <= node.data <= 10^5

    Expected Complexities:
    Time Complexity: O(N), postorder serialization of N-ary tree.
    Space Complexity: O(N), for hash map storing subtree serialized strings.

    Love Babbar Style Approach:
    Tree Serialization + Hash Map Frequency Counting:

    1. INTUITION:
       - To detect duplicate subtrees in an N-ary tree, we need a unique representation (serialization)
         for every subtree rooted at each node.
       - A subtree serialization string can be formatted as:
         `data(child1_str,child2_str,...)`
       - By performing a Postorder DFS:
         * Recursively serialize all children of `root`.
         * Concatenate `root->data` and serialized strings of its children.
         * Store the serialized string in an `unordered_map<string, int> subtrees`.
         * When `subtrees[str]` reaches exactly `2` (the FIRST time a duplicate structure is detected),
           increment our `ans++` counter.
       - This ensures each distinct duplicate subtree is counted PRECISELY ONCE.

    2. ALGORITHM:
       - `serialize(root, subtrees, ans)`:
         * `if (!root) return "";`
         * `string s = to_string(root->data) + "(";`
         * For each `child` in `root->children`:
           - `s += serialize(child, subtrees, ans) + ",";`
         * `s += ")";`
         * `subtrees[s]++;`
         * `if (subtrees[s] == 2) ans++;`
         * Return `s`.
       - Main `duplicateSubtreeNaryTree(root)`:
         * `unordered_map<string, int> subtrees;`
         * `int ans = 0;`
         * `serialize(root, subtrees, ans);`
         * Return `ans`.

    Dry Run:
    Leaf nodes with data = 4:
    - First node 4: s = "4()", subtrees["4()"] = 1.
    - Second node 4: s = "4()", subtrees["4()"] = 2 -> ans = 1.
    - Third node 4: s = "4()", subtrees["4()"] = 3 -> ans stays 1.

    Leaf nodes with data = 3:
    - First node 3: s = "3()", subtrees["3()"] = 1.
    - Second node 3: s = "3()", subtrees["3()"] = 2 -> ans = 2.

    Result: 2 ✓
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Definition for an N-ary tree node.
struct Node {
    int data;
    vector<Node*> children;

    Node(int val) {
        data = val;
    }
};

class Solution {
private:
    // Helper function to serialize subtrees and track frequency
    string serialize(Node* root, unordered_map<string, int>& subtrees, int& ans) {
        if (!root) return "";

        string s = to_string(root->data) + "(";
        for (Node* child : root->children) {
            s += serialize(child, subtrees, ans) + ",";
        }
        s += ")";

        subtrees[s]++;

        // Count only once when frequency becomes 2
        if (subtrees[s] == 2) {
            ans++;
        }

        return s;
    }

public:
    // GFG Signature
    int duplicateSubtreeNaryTree(Node* root) {
        unordered_map<string, int> subtrees;
        int ans = 0;

        serialize(root, subtrees, ans);

        return ans;
    }
};

int main() {
    Solution ob;

    // Example 1:
    //            1
    //         /  |  \
    //        2   2   3
    //       /   / \
    //      4   4   4
    // Subtree [4] occurs 3 times -> counted once (1)
    // Subtree [3] occurs 1 time
    // Node 2 with child 4 occurs 2 times -> counted once (2)
    Node* root1 = new Node(1);

    Node* child1 = new Node(2);
    child1->children.push_back(new Node(4));

    Node* child2 = new Node(2);
    child2->children.push_back(new Node(4));
    child2->children.push_back(new Node(4));

    Node* child3 = new Node(3);

    root1->children.push_back(child1);
    root1->children.push_back(child2);
    root1->children.push_back(child3);

    cout << "Example 1 Duplicate Subtrees Count: " << ob.duplicateSubtreeNaryTree(root1) << "\n";

    return 0;
}
