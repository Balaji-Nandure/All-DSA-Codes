bool dfs(Node *root, unordered_set<int> &st, int target){
  
    if (root == nullptr)
        return false;

    // Check if the complement (target - current node's value)
    // exists in the set
    if (st.find(target - root->data) != st.end())
        return true;

    // Insert the current node's value into the set
    st.insert(root->data);

    // Continue the search in the left and right subtrees
    return dfs(root->left, st, target) || dfs(root->right, st, target);
}

// Main function to check if two elements
// in the BST target to target
bool findTarget(Node *root, int target){
  
    // To store visited nodes' values
    unordered_set<int> st;

    // Start DFS from the root
    return dfs(root, st, target);
}