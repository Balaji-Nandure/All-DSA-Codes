/*
Problem:
Given n jobs with startTime[i], endTime[i], profit[i],
select a subset of non-overlapping jobs to maximize total profit.

Example:
start = [1,2,3,3]
end   = [3,4,5,6]
profit= [50,10,40,70]
Answer = 120

Approach (Optimal):
1) Create jobs = {start, end, profit}
2) Sort jobs by start time
3) dp[i] = max profit starting from job i to end
4) For each job i:
   - Option 1: skip job i → dp[i+1]
   - Option 2: take job i:
       profit[i] + dp[next_index]
     where next_index is the first job with start >= current job's end
     (found using binary search)
5) dp[n] = 0
6) Answer = dp[0]

Why it works:
At every job we decide pick / skip, and binary search ensures we
efficiently jump to the next compatible job.

GFG:
https://practice.geeksforgeeks.org/problems/maximum-profit-4657/1

LeetCode:
https://leetcode.com/problems/maximum-profit-in-job-scheduling/

Time Complexity:
O(n log n)

Space Complexity:
O(n)
*/

/*
Problem:
Given n jobs with startTime[i], endTime[i], profit[i],
select a subset of non-overlapping jobs to maximize total profit.

Example:
start = [1,2,3,3]
end   = [3,4,5,6]
profit= [50,10,40,70]
Answer = 120

Approach (Optimal):
1) Create jobs = {start, end, profit}
2) Sort jobs by start time
3) dp[i] = max profit starting from job i to end
4) For each job i:
   - Option 1: skip job i → dp[i+1]
   - Option 2: take job i:
       profit[i] + dp[next_index]
     where next_index is the first job with start >= current job's end
     (found using binary search)
5) dp[n] = 0
6) Answer = dp[0]

Why it works:
At every job we decide pick / skip, and binary search ensures we
efficiently jump to the next compatible job.

GFG:
https://practice.geeksforgeeks.org/problems/maximum-profit-4657/1

LeetCode:
https://leetcode.com/problems/maximum-profit-in-job-scheduling/

Time Complexity:
O(n log n)

Space Complexity:
O(n)
*/

class Solution {
public:
    int findNext(const vector<vector<int>>& jobs, int idx) {
        int n = jobs.size();
        int left = idx + 1, right = n - 1, res = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (jobs[mid][0] >= jobs[idx][1]) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }

    int solve(const vector<vector<int>>& jobs, int i, vector<int>& dp) {
        if (i >= jobs.size()) return 0;
        if (dp[i] != -1) return dp[i];
        int take = jobs[i][2];
        int ni = findNext(jobs, i);
        take += solve(jobs, ni, dp);
        int skip = solve(jobs, i + 1, dp);
        return dp[i] = max(take, skip);
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n, vector<int>(3));
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        sort(jobs.begin(), jobs.end());
        vector<int> dp(n, -1);
        return solve(jobs, 0, dp);
    }
};

// Tabulation version
class Solution_Tabulation {
public:
    int findNext(const vector<vector<int>>& jobs, int idx) {
        int n = jobs.size();
        int left = idx + 1, right = n - 1, res = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (jobs[mid][0] >= jobs[idx][1]) {
                res = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return res;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n, vector<int>(3));
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        sort(jobs.begin(), jobs.end());

        vector<int> dp(n + 1, 0); // dp[i] = max profit from i to end
        for (int i = n - 1; i >= 0; --i) {
            int ni = findNext(jobs, i);
            int take = jobs[i][2] + dp[ni];
            int skip = dp[i + 1];
            dp[i] = max(take, skip);
        }
        return dp[0];
    }
};