/*
    Problem Name: Construct Binary Tree from String with bracket representation
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Construct a binary tree from a string consisting of parenthesis and integers. The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure. Always construct the left child first.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the string, as each character is processed exactly once.
    Space Complexity: O(N), for the recursion stack space in the worst case of a skewed tree.

    Love Babbar Style Approach:
    1. Recursive Parsing: Since a tree's structure is inherently recursive (a root, followed by a left subtree in brackets, and then a right subtree in brackets), we can use a recursive function to parse the string.
    2. Reference Index: We pass the index `i` by reference to our recursive function so that parsing progress is maintained across recursive calls.
    3. Extracting the Root: At any step, we first extract the integer (accounting for potential negative signs) which forms the root of the current subtree.
    4. Left Child: After the integer, if the next character is `(`, it means the left child subtree is starting. We increment `i` to skip the `(`, recursively build the left subtree, and then increment `i` again to skip the closing `)`.
    5. Right Child: After processing the left child, if we immediately encounter another `(`, it denotes the start of the right child subtree. We repeat the same process to build the right subtree.
    6. Return Root: Once both potential subtrees are parsed, we return the constructed `root`.

    Dry Run:
    Input: "4(2)(6)"
    - Initial call `solve`, i = 0.
    - Parse integer '4'. Node(4) created. i = 1.
    - Next char is `(`. i = 2. Call `solve` for left child.
      - Parse integer '2'. Node(2) created. i = 3.
      - Next char is `)`. No left or right child. Return Node(2).
    - `solve(left)` returns. Skip `)`. i = 4.
    - Next char is `(`. i = 5. Call `solve` for right child.
      - Parse integer '6'. Node(6) created. i = 6.
      - Next char is `)`. Return Node(6).
    - `solve(right)` returns. Skip `)`. i = 7.
    - Return Node(4).
    Tree:
        4
       / \
      2   6
*/

#include <iostream>
#include <string>

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
    Node* solve(const string& s, int& i) {
        if (i >= s.length()) return NULL;
        
        bool isNeg = false;
        if (s[i] == '-') {
            isNeg = true;
            i++;
        }
        
        int num = 0;
        while (i < s.length() && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            i++;
        }
        
        if (isNeg) num = -num;
        
        Node* root = new Node(num);
        
        // Check for left child
        if (i < s.length() && s[i] == '(') {
            i++; // skip '('
            if (s[i] == ')') {
                root->left = NULL;
            } else {
                root->left = solve(s, i);
            }
            i++; // skip ')'
        }
        
        // Check for right child
        if (i < s.length() && s[i] == '(') {
            i++; // skip '('
            if (s[i] == ')') {
                root->right = NULL;
            } else {
                root->right = solve(s, i);
            }
            i++; // skip ')'
        }
        
        return root;
    }

  public:
    Node* treeFromString(string str) {
        int i = 0;
        return solve(str, i);
    }
};

// Helper function to print inorder traversal for testing
void printInorder(Node* root) {
    if (root == NULL) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            Solution ob;
            Node* root = ob.treeFromString(s);
            printInorder(root);
            cout << "\n";
        }
    }
    return 0;
}
