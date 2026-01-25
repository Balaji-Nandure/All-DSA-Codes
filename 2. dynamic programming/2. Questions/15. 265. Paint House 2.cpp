#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Paint House II
LeetCode 265: https://leetcode.com/problems/paint-house-ii/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/paint-house-ii/1

There are a row of n houses, each house can be painted with one of k colors. 
The cost of painting each house with a certain color is represented by an n x k cost matrix.
For example, costs[0][0] is the cost of painting house 0 with color 0; 
costs[1][2] is the cost of painting house 1 with color 2, and so on.

Find the minimum cost to paint all houses such that no two adjacent houses have the same color.

Constraints:
- n == costs.length
- k == costs[i].length
- 1 <= n <= 100
- 1 <= k <= 20
- 1 <= costs[i][j] <= 20

Example:
costs = [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. 
Minimum cost: 1 + 4 = 5; or paint house 0 into color 2, paint house 1 into color 0. 
Minimum cost: 3 + 2 = 5.

DP State:
- dp[i][j] = minimum cost to paint houses [0...i] such that house i is painted with color j

Recurrence Relation:
- For each house i and color j:
  dp[i][j] = costs[i][j] + min(dp[i-1][c]) for all colors c != j

Base Cases:
- dp[0][j] = costs[0][j] for all colors j (first house can be any color)

Time Complexity: O(n * k^2) for naive, O(n * k) optimized
Space Complexity: O(n * k) for tabulation, O(k) for space optimized
*/

// Approach 1: Pure Recursion (take/not take method)
class Solution1_Recursion {
public:
    // TC: O(k * 2^n) exponential, SC: O(n) recursion stack
    int solve(int houseIdx, int prevColor, int n, int k, vector<vector<int>>& costs) {
        // Base case: all houses painted
        if (houseIdx == n) return 0;
        
        int minCost = INF;
        // Try each color for current house
        for (int color = 0; color < k; color++) {
            // Skip if same color as previous house
            if (color == prevColor) continue;
            // Take current color and recurse
            minCost = min(minCost, costs[houseIdx][color] + 
                         solve(houseIdx + 1, color, n, k, costs));
        }
        
        return minCost;
    }
    
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        return solve(0, -1, n, k, costs);
    }
};

// Approach 1.0: Pure Recursion (for loop method)
class Solution1_Recursion_ForLoop {
public:
    // TC: O(k * 2^n) exponential, SC: O(n) recursion stack
    int solve(int houseIdx, int prevColor, int n, int k, vector<vector<int>>& costs) {
        if (houseIdx == n) return 0;
        
        int minCost = INF;
        for (int color = 0; color < k; color++) {
            if (color != prevColor) {
                minCost = min(minCost, costs[houseIdx][color] + 
                             solve(houseIdx + 1, color, n, k, costs));
            }
        }
        return minCost;
    }
    
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        return solve(0, -1, n, k, costs);
    }
};

// Approach 2: Memoization (Top-down DP)
class Solution2_Memoization {
public:
    // TC: O(n * k^2), SC: O(n * k) for dp + O(n) recursion stack
    int solve(int houseIdx, int prevColor, int n, int k, 
              vector<vector<int>>& costs, vector<vector<int>>& dp) {
        if (houseIdx == n) return 0;
        
        // Use -1 as sentinel for uninitialized (since prevColor can be -1 initially)
        // Adjust index: prevColor ranges from -1 to k-1, so shift by 1
        int dpIdx = prevColor + 1;
        if (dp[houseIdx][dpIdx] != -1) return dp[houseIdx][dpIdx];
        
        int minCost = INF;
        for (int color = 0; color < k; color++) {
            if (color != prevColor) {
                minCost = min(minCost, costs[houseIdx][color] + 
                             solve(houseIdx + 1, color, n, k, costs, dp));
            }
        }
        
        return dp[houseIdx][dpIdx] = minCost;
    }
    
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        // dp[i][j+1] stores result for house i with previous color j (j=-1 to k-1)
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solve(0, -1, n, k, costs, dp);
    }
};

// Approach 3: Tabulation (Bottom-up DP)
class Solution3_Tabulation {
public:
    // TC: O(n * k^2), SC: O(n * k) for dp array
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        
        // dp[i][j] = minimum cost to paint houses [0...i] with house i painted color j
        vector<vector<int>> dp(n, vector<int>(k, INF));
        
        // Base case: first house can be any color
        for (int color = 0; color < k; color++) {
            dp[0][color] = costs[0][color];
        }
        
        // For each house
        for (int i = 1; i < n; i++) {
            // For each color for current house
            for (int j = 0; j < k; j++) {
                // Find minimum cost from previous house (excluding same color)
                for (int prevColor = 0; prevColor < k; prevColor++) {
                    if (prevColor != j) {
                        dp[i][j] = min(dp[i][j], dp[i-1][prevColor] + costs[i][j]);
                    }
                }
            }
        }
        
        // Answer is minimum cost for last house with any color
        int result = INF;
        for (int color = 0; color < k; color++) {
            result = min(result, dp[n-1][color]);
        }
        
        return result;
    }
};

// Approach 4: Space Optimization (O(k) space)
class Solution4_SpaceOptimized {
public:
    // TC: O(n * k^2), SC: O(k) - only track previous house costs
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        
        // prev[i] = minimum cost to paint previous house with color i
        vector<int> prev(k);
        
        // Base case: first house
        for (int color = 0; color < k; color++) {
            prev[color] = costs[0][color];
        }
        
        // For each house
        for (int i = 1; i < n; i++) {
            vector<int> curr(k, INF);
            
            // For each color for current house
            for (int j = 0; j < k; j++) {
                // Find minimum from previous house (excluding same color)
                for (int prevColor = 0; prevColor < k; prevColor++) {
                    if (prevColor != j) {
                        curr[j] = min(curr[j], prev[prevColor] + costs[i][j]);
                    }
                }
            }
            
            prev = curr; // Update for next iteration
        }
        
        // Answer is minimum cost for last house
        return *min_element(prev.begin(), prev.end());
    }
};

// Approach 4.1: Space Optimization with O(k) time optimization
// Track min and second min to avoid O(k^2) inner loop
class Solution {
public:
    // TC: O(n * k), SC: O(k) - optimized with min tracking
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        
        // prev[i] = minimum cost to paint previous house with color i
        vector<int> prev(k);
        for (int color = 0; color < k; color++) {
            prev[color] = costs[0][color];
        }
        
        for (int i = 1; i < n; i++) {
            // Find min and second min from previous house
            int min1 = INF, min2 = INF;
            int minIdx = -1;
            
            for (int j = 0; j < k; j++) {
                if (prev[j] < min1) {
                    min2 = min1;
                    min1 = prev[j];
                    minIdx = j;
                } else if (prev[j] < min2) {
                    min2 = prev[j];
                }
            }
            
            vector<int> curr(k);
            // For each color, use min if different color, else use second min
            for (int j = 0; j < k; j++) {
                if (j != minIdx) {
                    curr[j] = costs[i][j] + min1; // Use minimum
                } else {
                    curr[j] = costs[i][j] + min2; // Use second minimum
                }
            }
            
            prev = curr;
        }
        
        return *min_element(prev.begin(), prev.end());
    }
};
