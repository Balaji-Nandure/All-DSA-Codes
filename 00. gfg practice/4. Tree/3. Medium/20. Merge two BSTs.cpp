/*
    Problem Name: Merge two BST's
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the roots of two BSTs, merge them and return the inorder traversal of the
    merged BST as a sorted vector.

    Expected Complexities:
    Time Complexity: O(N + M), where N and M are the number of nodes in the two BSTs.
                     Inorder traversal of each BST is O(N) and O(M), merging two sorted
                     arrays is O(N + M).
    Space Complexity: O(N + M), for storing the two inorder arrays and the merged result.

    Love Babbar Style Approach:
    The KEY insight — the inorder traversal of a BST is ALWAYS SORTED!
    So this problem is just "Merge Two Sorted Arrays" in disguise!

    Step 1: Get the inorder traversal of BST1 → sorted array A.
    Step 2: Get the inorder traversal of BST2 → sorted array B.
    Step 3: Merge A and B using the classic two-pointer merge technique!

    The two-pointer merge:
    - Use pointer i for array A, pointer j for array B.
    - Compare A[i] and B[j] — take the SMALLER one and move that pointer forward.
    - When one array is exhausted, dump all remaining elements from the other.

    This is the SAME merge step from Merge Sort — simple, elegant, and O(N + M)!

    Dry Run:
    BST1:     3          BST2:     4
             / \                  / \
            1   5                2   6

    Step 1: Inorder(BST1) → [1, 3, 5]
    Step 2: Inorder(BST2) → [2, 4, 6]
    Step 3: Merge [1, 3, 5] and [2, 4, 6]:
        i=0, j=0: A[0]=1 < B[0]=2 → take 1, i++
        i=1, j=0: A[1]=3 > B[0]=2 → take 2, j++
        i=1, j=1: A[1]=3 < B[1]=4 → take 3, i++
        i=2, j=1: A[2]=5 > B[1]=4 → take 4, j++
        i=2, j=2: A[2]=5 < B[2]=6 → take 5, i++
        i=3: A exhausted → take remaining B: 6
    Result: [1, 2, 3, 4, 5, 6] ✓

    Dry Run 2:
    BST1:     8          BST2:     5
             / \                  /
            2   10               3
           /                    /
          1                    0

    Step 1: Inorder(BST1) → [1, 2, 8, 10]
    Step 2: Inorder(BST2) → [0, 3, 5]
    Step 3: Merge:
        0 < 1 → take 0
        1 < 3 → take 1
        2 < 3 → take 2
        3 < 8 → take 3
        5 < 8 → take 5
        B exhausted → take remaining A: 8, 10
    Result: [0, 1, 2, 3, 5, 8, 10] ✓
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
private:
    // Helper: Standard inorder traversal → fills a sorted vector
    void inorder(Node* root, vector<int>& result) {
        if (root == NULL) return;

        inorder(root->left, result);
        result.push_back(root->data);
        inorder(root->right, result);
    }

    // Helper: Merge two sorted arrays using the classic two-pointer technique
    vector<int> mergeSorted(vector<int>& a, vector<int>& b) {
        vector<int> merged;
        int i = 0, j = 0;

        // Compare elements from both arrays and take the smaller one
        while (i < a.size() && j < b.size()) {
            if (a[i] <= b[j]) {
                merged.push_back(a[i++]);
            } else {
                merged.push_back(b[j++]);
            }
        }

        // One array might have leftovers — dump them all
        while (i < a.size()) merged.push_back(a[i++]);
        while (j < b.size()) merged.push_back(b[j++]);

        return merged;
    }

public:
    // GFG Signature
    vector<int> merge(Node* root1, Node* root2) {
        // Step 1: Get sorted arrays from both BSTs via inorder traversal
        vector<int> inorder1, inorder2;
        inorder(root1, inorder1);
        inorder(root2, inorder2);

        // Step 2: Merge the two sorted arrays — just like the merge step of Merge Sort!
        return mergeSorted(inorder1, inorder2);
    }
};

int main() {
    // Example 1:
    //  BST1:    3        BST2:    4
    //          / \               / \
    //         1   5             2   6
    // Expected: [1, 2, 3, 4, 5, 6]

    Node* r1 = new Node(3);
    r1->left  = new Node(1);
    r1->right = new Node(5);

    Node* r2 = new Node(4);
    r2->left  = new Node(2);
    r2->right = new Node(6);

    Solution ob;
    vector<int> ans1 = ob.merge(r1, r2);

    // Output: 1 2 3 4 5 6
    cout << "Merged BST (Example 1): ";
    for (int val : ans1) cout << val << " ";
    cout << "\n";

    // Example 2:
    //  BST1:     8        BST2:    5
    //           / \               /
    //          2   10            3
    //         /                 /
    //        1                 0
    // Expected: [0, 1, 2, 3, 5, 8, 10]

    Node* r3 = new Node(8);
    r3->left       = new Node(2);
    r3->right      = new Node(10);
    r3->left->left = new Node(1);

    Node* r4 = new Node(5);
    r4->left       = new Node(3);
    r4->left->left = new Node(0);

    vector<int> ans2 = ob.merge(r3, r4);

    // Output: 0 1 2 3 5 8 10
    cout << "Merged BST (Example 2): ";
    for (int val : ans2) cout << val << " ";
    cout << "\n";

    return 0;
}
