#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Minimum Difficulty of a Job Schedule
LeetCode 1335: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

You want to schedule a list of jobs in d days. Jobs are dependent (i.e., to work on the i-th job, 
you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of 
difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a 
job done on that day.

Given an array jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot schedule a job for more than d days, return -1.

Constraints:
- 1 <= jobDifficulty.length <= 300
- 0 <= jobDifficulty[i] <= 1000
- 1 <= d <= 10

Example:
jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7

Key Insight:
- We need to partition the array into exactly d segments
- Each segment's difficulty is the maximum value in that segment
- We want to minimize the sum of all segment difficulties
- Each day must have at least one job

DP State:
- dp[i][day] = minimum difficulty to schedule jobs from index i to end in 'day' days remaining
- OR: dp[i][day] = minimum difficulty to schedule first i jobs in 'day' days

Recurrence Relation (for dp[i][day]):
- For each possible end position j (from i to n-1):
  - maxDiff = maximum difficulty from job i to j (inclusive)
  - dp[i][day] = min(dp[i][day], maxDiff + dp[j+1][day-1])
- We try all possible ways to split jobs for the current day

Base Cases:
- If day == 1: dp[i][1] = max(jobDifficulty[i] to jobDifficulty[n-1])
- If i >= n: return 0 (no jobs left)
- If day > remaining jobs: return INF (impossible)

Time Complexity: O(n^2 * d) - for each position and day, we check all possible splits
Space Complexity: O(n * d) for memoization/tabulation
*/

// 1. Recursion
// TC: O(n^2 * d) exponential, SC: O(n) recursion stack
class Solution {
public:
    int solve(int idx, int d, vector<int>& jd){
        // if only one day left, we need to schedule all the jobs for that day
        if(d == 1) return *max_element(jd.begin() + idx, jd.end());
        int n = jd.size();
        
        int maxDiff = jd[idx];
        int ans = INT_MAX;
        for(int i = idx; i <= n - d; i++){
            maxDiff = max(maxDiff, jd[i]);
            int temp = solve(i + 1, d - 1, jd);
            ans = min(ans, maxDiff + temp);
        }

        return ans;
    }
    
    int minDifficulty(vector<int>& jd, int d) {
        int n = jd.size();
        if(n < d) return -1;
        return solve(0, d, jd);
    }
};

// 2. Memoization

class Solution {
public:
    int solve(int idx, int d, vector<int>& jd, vector<vector<int>>& dp){
        // if only one day left, we need to schedule all the jobs for that day
        if(d == 1) return *max_element(jd.begin() + idx, jd.end());
        if(dp[idx][d] != -1) return dp[idx][d];
        int n = jd.size();
        
        int maxDiff = jd[idx];
        int ans = INT_MAX;
        // going upto onlly n - d is very important.
        // if we go till n, then we will be going out of bounds.
        for(int i = idx; i <= n - d; i++){
            maxDiff = max(maxDiff, jd[i]);
            int temp = solve(i + 1, d - 1, jd, dp);
            ans = min(ans, maxDiff + temp);
        }

        return dp[idx][d] = ans;
    }
    
    int minDifficulty(vector<int>& jd, int d) {
        int n = jd.size();
        if(n < d) return -1;
        vector<vector<int>> dp(n, vector<int>(d + 1, -1));
        return solve(0, d, jd, dp);
    }
};
