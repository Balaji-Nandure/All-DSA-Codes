class Solution {
public:
    int dfs(int i, int j, vector<vector<int>>& grid){
        int m = grid.size();
        int n = grid[0].size();
        if(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == 0) return 0;

        int gold = grid[i][j];
        grid[i][j] = 0;
        int maxGold = 0;
        maxGold = max(maxGold, dfs(i - 1, j, grid)); // UP
        maxGold = max(maxGold, dfs(i + 1, j, grid)); // DOWN
        maxGold = max(maxGold, dfs(i, j - 1, grid)); // LEFT
        maxGold = max(maxGold, dfs(i, j + 1, grid)); // RIGHT

        grid[i][j] = gold;
        return gold + maxGold;

    }
    int getMaximumGold(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int maxGold = 0;


        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // if(grid[i][j] != 0){
                    maxGold = max(maxGold, dfs(i, j, grid));
                // }
            }
        }

        return maxGold;
    }
};