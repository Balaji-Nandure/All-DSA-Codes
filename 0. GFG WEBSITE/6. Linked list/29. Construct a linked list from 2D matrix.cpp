class Solution {
    public:
    Node *solve(vector<vector<int>> &mat, int i, int j){
        
        if(i >= mat.size() || j >= mat[0].size()){
            return nullptr;
        }
        
        Node *curr = new Node(mat[i][j]);
        curr->right = solve(mat, i, j + 1);
        curr->down = solve(mat, i + 1, j);
        
        return curr;
    }

    Node* constructLinkedMatrix(vector<vector<int>>& mat) {
        // code Here
        return solve(mat, 0, 0);
    }
  };