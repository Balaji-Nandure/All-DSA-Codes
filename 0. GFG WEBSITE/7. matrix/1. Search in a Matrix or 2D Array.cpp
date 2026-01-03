bool matrixSearch(vector<vector<int>>& mat, int x)
{
    int n = mat.size(), m = mat[0].size();

    // Compare each element one by one
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == x)
                return true;
    return false;
}