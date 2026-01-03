void sortMatrix(vector<vector<int>>& mat) {
    vector<int> temp;
    
    // Collect all elements in a temporary vector
    for (auto& row : mat) {
        for (int x : row) {
            temp.push_back(x);
        }
    }
    
    // Sort the vector
    sort(temp.begin(), temp.end());
    
    // Put sorted values back into the matrix
    int k = 0;
    for (auto& row : mat) {
        // taking by ref
        for (int& x : row) {
            x = temp[k++];
        }
    }
}