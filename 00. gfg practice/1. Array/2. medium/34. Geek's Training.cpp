/*
PROBLEM: Geek's Training (GFG)

Geek is training for n days. Each day he can do one of 3 activities:
0 = Running
1 = Fighting
2 = Learning

Constraint: He cannot do the same activity on two consecutive days.

Given a matrix mat[n][3], where mat[i][j] = points for activity j on day i,
return the maximum total points he can earn.

Example:
mat = [[1,2,5],
       [3,1,1],
       [3,3,3]]

Output: 11

--------------------------------------------------

INTUITION / APPROACH:

This is a DP problem.

State:
dp[day][last] = maximum points we can earn till "day"
                if last activity done was "last"

Where last = 0,1,2,3
0 = running
1 = fighting
2 = learning
3 = no previous activity (start case)

Transition:
dp[day][last] = max over all activities except "last"

So for each day, we try all 3 activities but skip the last activity.

--------------------------------------------------

DP FLOW (Striver Style):

1. Recursion
2. Memoization
3. Tabulation
4. Space Optimization (BEST)

We will write Space Optimized because n can be up to 1e5.

--------------------------------------------------

TIME COMPLEXITY:
O(N * 3 * 3) ≈ O(N)

SPACE COMPLEXITY:
O(1)

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/geeks-training/1

--------------------------------------------------
*/

class Solution {
  public:
  
    int maximumPoints(vector<vector<int>>& mat, int n) {
        if(n == 0) return 0;

        // prev[a] = max points up to previous day ending with activity a
        // vector<int> prev(3);
        // prev[0] = mat[0][0];
        // prev[1] = mat[0][1];
        // prev[2] = mat[0][2];

        // or easy way is instead of above 4 lines, we can just do:
        vector<int> prev = mat[0];

        for(int day = 1; day < n; day++) {
            vector<int> curr(3, 0);
            curr[0] = mat[day][0] + max(prev[1], prev[2]);
            curr[1] = mat[day][1] + max(prev[0], prev[2]);
            curr[2] = mat[day][2] + max(prev[0], prev[1]);
            prev = curr;
        }

        return max({prev[0], prev[1], prev[2]});
    }
};


/*
---------------- DRY RUN ----------------

mat = [[1,2,5],
       [3,1,1],
       [3,3,3]]

Day 0:
prev[0] = max(2,5) = 5
prev[1] = max(1,5) = 5
prev[2] = max(1,2) = 2
prev[3] = max(1,2,5) = 5

Day 1:
Compute temp using prev

Day 2:
Compute temp using prev

Final Answer = prev[3] = 11

--------------------------------------------------

FINAL SUMMARY:

Pattern: DP on Days + Last Activity Restriction
State: dp[day][last]
Transition: choose any task except last
Optimization: Use space optimization

This is a VERY IMPORTANT DP pattern:
"DP with restriction on previous choice"
*/
