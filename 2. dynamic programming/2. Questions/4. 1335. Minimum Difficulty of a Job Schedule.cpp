#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Minimum Difficulty of a Job Schedule
LeetCode 1335: https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

You want to schedule a list of jobs in d days. Jobs are dependent (i.e., to work on the 
i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the 
sum of difficulties of each day of the d days. The difficulty of a day is the maximum 
difficulty of a job done on that day.

You are given an integer array jobDifficulty and an integer d. The difficulty of the 
i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the 
jobs return -1.

Constraints:
- 1 <= jobDifficulty.length <= 300
- 0 <= jobDifficulty[i] <= 1000
- 1 <= d <= 10

Example:
jobDifficulty = [6, 5, 4, 3, 2, 1], d = 2
Day 1: [6, 5, 4, 3, 2] -> max = 6
Day 2: [1] -> max = 1
Total difficulty = 6 + 1 = 7

Day 1: [6, 5, 4, 3] -> max = 6
Day 2: [2, 1] -> max = 2
Total difficulty = 6 + 2 = 8

Minimum = 7

Key Insight:
- We need to partition the array into exactly d contiguous subarrays
- Each day must have at least one job
- We want to minimize the sum of maximums of each subarray
- This is a partition DP problem: dp[i][d] = min difficulty to schedule jobs[0..i] in d days

DP State: 
- dp[i][d] = minimum difficulty to schedule jobs from index 0 to i (inclusive) in d days

Recurrence:
- dp[i][d] = min(dp[j][d-1] + max(jobs[j+1..i])) for all j from d-2 to i-1
- We partition at position j: jobs[0..j] in d-1 days, jobs[j+1..i] in 1 day
- The last day (d-th day) contains jobs[j+1..i], its difficulty is max(jobs[j+1..i])
- We need at least d-1 jobs for first d-1 days, so j >= d-2
- We need at least 1 job for last day, so j < i

Base Cases:
- dp[i][1] = max(jobs[0..i]) for all i (single day, difficulty is max of all jobs)
- dp[i][d] = INF if i < d-1 (not enough jobs for d days)

Time Complexity: O(n^2 * d) where n is number of jobs
Space Complexity: O(n * d) for memoization/tabulation, O(n) for space optimization
*/

// 1. Recursive DFS approach (Continue day / End day decision)
class MinimumDifficultyRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int dfs(int i, int d, int curMax, const vector<int>& job, int n) {
        // All jobs processed
        if (i == n) {
            return (d == 0) ? 0 : (int)1e9;
        }

        // If no days left but jobs remain, invalid
        if (d == 0) return (int)1e9;

        // Update the current day's max difficulty with this job
        int newMax = max(curMax, job[i]);

        // Option 1: Continue adding jobs to the current day
        int cont = dfs(i + 1, d, newMax, job, n);

        // Option 2: End the current day here, start a new day with next job
        int endDay = newMax + dfs(i + 1, d - 1, -1, job, n);

        // Return the minimum difficulty between the two options
        return min(cont, endDay);
    }

    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = (int)jobDifficulty.size();
        if (n < d) return -1;
        return dfs(0, d, -1, jobDifficulty, n);
    }
};

// 2. Memoization approach (Top-down DP with 3D dp)
class MinimumDifficultyMemoization3D {
public:
    // TC: O(n * d * max_job), SC: O(n * d * max_job) for dp array + O(n) recursion stack
    int dfs(int i, int d, int curMax,
            const vector<int>& job,
            vector<vector<vector<int>>>& dp, int n) {
        // All jobs processed
        if (i == n) {
            return (d == 0) ? 0 : (int)1e9;
        }

        // No days left but jobs remain
        if (d == 0) return (int)1e9;

        // curMax ranges from -1..1000 → shift by +1
        int &res = dp[i][d][curMax + 1];
        if (res != -1) return res;

        int newMax = max(curMax, job[i]);

        // Option 1: continue current day
        int cont = dfs(i + 1, d, newMax, job, dp, n);

        // Option 2: end current day here
        int endDay = newMax + dfs(i + 1, d - 1, -1, job, dp, n);

        return res = min(cont, endDay);
    }

    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = (int)jobDifficulty.size();
        if (n < d) return -1;

        // dp[i][d][curMax+1]
        vector<vector<vector<int>>> dp(
            n,
            vector<vector<int>>(d + 1, vector<int>(1002, -1))
        );

        return dfs(0, d, -1, jobDifficulty, dp, n);
    }
};

// 3. Memoization approach (Top-down DP with 2D dp - more efficient)
class MinimumDifficultyMemoization2D {
public:
    // TC: O(n^2 * d), SC: O(n * d) for dp array + O(n) recursion stack
    int dfs(int i, int days, const vector<int>& job, vector<vector<int>>& dp) {
        int n = job.size();
        // If we've finished all days
        if (days == 0 && i == n) return 0;
        // If either out of days or jobs, not valid
        if (days == 0 || n - i < days) return 1e9;

        if (dp[i][days] != -1) return dp[i][days];

        int curMax = 0, ans = 1e9;
        // At least one job per day, try all splits for current day
        // End job for today is j (from i to n-days)
        for (int j = i; j <= n - days; ++j) {
            curMax = max(curMax, job[j]);
            int next = dfs(j + 1, days - 1, job, dp);
            if (next != 1e9)
                ans = min(ans, curMax + next);
        }
        return dp[i][days] = ans;
    }
    
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        vector<vector<int>> dp(n, vector<int>(d + 1, -1));
        int res = dfs(0, d, jobDifficulty, dp);
        return res >= 1e9 ? -1 : res;
    }
};

// 4. Tabulation approach (Bottom-up DP)
class MinimumDifficultyTabulation {
public:
    // TC: O(n^2 * d), SC: O(n * d) for dp array
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        
        // dp[i][days] = minimum difficulty to schedule jobs[0..i] in 'days' days
        vector<vector<int>> dp(n, vector<int>(d + 1, 1e9));
        
        // Base case: single day - difficulty is max of all jobs from 0 to i
        int maxSoFar = 0;
        for (int i = 0; i < n; i++) {
            maxSoFar = max(maxSoFar, jobDifficulty[i]);
            dp[i][1] = maxSoFar;
        }
        
        // Fill dp for 2 to d days
        for (int days = 2; days <= d; days++) {
            for (int i = days - 1; i < n; i++) { // Need at least 'days' jobs
                int curMax = 0;
                // Try all possible partitions
                for (int j = i; j >= days - 1; j--) {
                    curMax = max(curMax, jobDifficulty[j]);
                    // jobs[0..j-1] in (days-1) days, jobs[j..i] in 1 day
                    if (j > 0) {
                        dp[i][days] = min(dp[i][days], dp[j - 1][days - 1] + curMax);
                    } else {
                        dp[i][days] = min(dp[i][days], curMax);
                    }
                }
            }
        }
        
        return dp[n - 1][d] >= 1e9 ? -1 : dp[n - 1][d];
    }
};

// 5. Optimized Solution (2D Memoization - Best approach)
class Solution {
public:
    // TC: O(n^2 * d), SC: O(n * d) for dp array + O(n) recursion stack
    int dfs(int i, int days, const vector<int>& job, vector<vector<int>>& dp) {
        int n = job.size();
        // If we've finished all days
        if (days == 0 && i == n) return 0;
        // If either out of days or jobs, not valid
        if (days == 0 || n - i < days) return 1e9;

        if (dp[i][days] != -1) return dp[i][days];

        int curMax = 0, ans = 1e9;
        // At least one job per day, try all splits for current day
        // End job for today is j (from i to n-days)
        for (int j = i; j <= n - days; ++j) {
            curMax = max(curMax, job[j]);
            int next = dfs(j + 1, days - 1, job, dp);
            if (next != 1e9)
                ans = min(ans, curMax + next);
        }
        return dp[i][days] = ans;
    }
    
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        vector<vector<int>> dp(n, vector<int>(d + 1, -1));
        int res = dfs(0, d, jobDifficulty, dp);
        return res >= 1e9 ? -1 : res;
    }
};
