/**
 * Problem: Construct Binary Tree from String with Bracket Representation
 * Category: Binary Trees
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previously, we serialized/deserialized arrays or traversed existing pointer graphs.
 * - Here, we parse a structured string with recursive nested delimiters: `Root(LeftSubtree)(RightSubtree)`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Descent Parsing:
 *   - The first token is always the root's value (handling multi-digit or negative numbers).
 *   - Allocate node: `Node* root = new Node(val)`.
 *   - Check next character:
 *     - If `s[index] == '('`:
 *       - Consume `(`, recursively construct the left subtree, and consume matching `)`.
 *     - If another `s[index] == '('` follows immediately:
 *       - Consume `(`, recursively construct the right subtree, and consume matching `)`.
 *   - Single pass index advancement parses the entire grammar in strictly O(N) time without stack lookups.
 * 
 * TIME COMPLEXITY:
 * - O(N): Where N is string length (each character processed once).
 * 
 * SPACE COMPLEXITY:
 * - O(H): Recursion depth proportional to tree height.
 */

#include <iostream>
#include <string>
#include <cctype>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* parseTree(const std::string& s, int& i) {
    if (i >= (int)s.length() || s[i] == ')') return nullptr;

    // Parse integer (including negative signs)
    int sign = 1;
    if (s[i] == '-') {
        sign = -1;
        i++;
    }

    int val = 0;
    while (i < (int)s.length() && isdigit(s[i])) {
        val = val * 10 + (s[i] - '0');
        i++;
    }
    val *= sign;

    Node* root = new Node(val);

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // First '(' opens the left subtree; once it closes, the second '(' opens the right subtree.
    if (i < (int)s.length() && s[i] == '(') {
        i++; // skip '('
        root->left = parseTree(s, i);
        i++; // skip ')'
    }

    if (i < (int)s.length() && s[i] == '(') {
        i++; // skip '('
        root->right = parseTree(s, i);
        i++; // skip ')'
    }

    return root;
}

Node* treeFromString(const std::string& s) {
    int i = 0;
    return parseTree(s, i);
}

void preOrder(Node* root) {
    if (!root) return;
    std::cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    std::string s = "4(2(3)(1))(6(5))";
    Node* root = treeFromString(s);

    std::cout << "Preorder of constructed tree: ";
    preOrder(root); // 4 2 3 1 6 5
    std::cout << "\n";

    return 0;
}
