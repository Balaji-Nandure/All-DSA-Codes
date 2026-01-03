void rowMajor(vector<vector<int>>& arr) {
    int rows = arr.size();
    int cols = arr[0].size();

    // Accessing elements row-wise
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j]++;
        }
    }
}

void colMajor(vector<vector<int>>& arr) {
    int rows = arr.size();
    int cols = arr[0].size();

    // Accessing elements column-wise
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            arr[j][i]++;
        }
    }
}