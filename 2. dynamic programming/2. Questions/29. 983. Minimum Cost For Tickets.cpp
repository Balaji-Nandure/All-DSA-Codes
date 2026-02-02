/*
Problem:
983. Minimum Cost For Tickets

Approach:
Recursion + Memoization

State:
solve(i) = minimum cost to cover travel days from index i onward

At each index i, try:
- 1-day pass
- 7-day pass
- 30-day pass

LeetCode:
https://leetcode.com/problems/minimum-cost-for-tickets/

Time Complexity:
O(n)

Space Complexity:
O(n)
*/

class Solution {
private:
    int solve(int i,
              vector<int>& days,
              vector<int>& costs,
              vector<int>& dp) {

        // Base case: all days covered
        if (i >= days.size())
            return 0;

        // Memoized result
        if (dp[i] != -1)
            return dp[i];

        int n = days.size();
        int j;

        // 1-day pass
        j = i;
        while (j < n && days[j] < days[i] + 1) j++;
        int cost1 = costs[0] + solve(j, days, costs, dp);

        // 7-day pass
        j = i;
        while (j < n && days[j] < days[i] + 7) j++;
        int cost7 = costs[1] + solve(j, days, costs, dp);

        // 30-day pass
        j = i;
        while (j < n && days[j] < days[i] + 30) j++;
        int cost30 = costs[2] + solve(j, days, costs, dp);

        return dp[i] = min({cost1, cost7, cost30});
    }

public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {

        int n = days.size();
        vector<int> dp(n, -1);

        return solve(0, days, costs, dp);
    }
};


class Solution2 {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        
        int n = days.size();
        vector<int> dp(n+1, 0);
        
        for(int i = n-1; i>=0; i--){
            int opt1 = costs[0] + dp[i+1];

            int j = i;
            while(j<n && days[j] <= days[i]+6){
                j++;
            }       

            int opt2 = costs[1] + dp[j];  


            j = i;
            while(j<n && days[j] <= days[i]+29){
                j++;
            }       

            int opt3 = costs[2] + dp[j];

            dp[i] =  min(opt1, min(opt2, opt3));
        }

        return dp[0];
    }
};