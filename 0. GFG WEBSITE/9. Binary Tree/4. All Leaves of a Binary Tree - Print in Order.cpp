void printLeafNodes(Node* root) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        cout << root->data << " ";
        return;
    }

    if (root->left)
        printLeafNodes(root->left);

    if (root->right)
        printLeafNodes(root->right);
}