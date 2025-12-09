#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Ninja's Training
A ninja has N days of training. Each day, he can perform one of three activities:
- Activity 0: Training type 0
- Activity 1: Training type 1
- Activity 2: Training type 2

Each activity gives different merit points. The ninja cannot perform the same activity
on two consecutive days. Find the maximum merit points the ninja can earn.

Given:
- points[N][3]: points[i][j] = merit points for day i, activity j

Example:
points = [[1, 2, 5],
          [3, 1, 1],
          [3, 3, 3]]
Day 0: Activity 2 -> 5 points
Day 1: Activity 0 -> 3 points (can't do activity 2 again)
Day 2: Activity 1 or 2 -> 3 points
Maximum = 5 + 3 + 3 = 11
*/

// recursive approach
int ninjaTraining(int day, int lastActivity, vector<vector<int>> &points){
    // if(day == 0){
    //     int maxPoints = 0;
    //     for(int activity = 0; activity < 3; activity++){
    //         if(activity != lastActivity){
    //             maxPoints = max(maxPoints, points[0][activity]);
    //         }
    //     }
    //     return maxPoints;
    // }

    if(day < 0) return 0;
    
    int maxPoints = 0;
    for(int activity = 0; activity < 3; activity++){
        if(activity != lastActivity){
            int currentPoints = points[day][activity] + ninjaTraining(day - 1, activity, points);
            maxPoints = max(maxPoints, currentPoints);
        }
    }
    
    return maxPoints;
}

// memoization approach
int ninjaTrainingMemoization(int day, int lastActivity, vector<vector<int>> &points, vector<vector<int>> &dp){
    // if(day == 0){
    //     int maxPoints = 0;
    //     for(int activity = 0; activity < 3; activity++){
    //         if(activity != lastActivity){
    //             maxPoints = max(maxPoints, points[0][activity]);
    //         }
    //     }
    //     return maxPoints;
    // }

    if(day < 0) return 0;
    if(dp[day][lastActivity] != -1) return dp[day][lastActivity];
    
    int maxPoints = 0;
    for(int activity = 0; activity < 3; activity++){
        if(activity != lastActivity){
            int currentPoints = points[day][activity] + ninjaTrainingMemoization(day - 1, activity, points, dp);
            maxPoints = max(maxPoints, currentPoints);
        }
    }
    
    return dp[day][lastActivity] = maxPoints;
}

// tabulation approach
int ninjaTrainingTabulation(int n, vector<vector<int>> &points){
    // dp[day][lastActivity] = max points from day 0 to day, ending with lastActivity
    vector<vector<int>> dp(n, vector<int>(4, 0));
    
    // Base case: day 0
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]});
    
    for(int day = 1; day < n; day++){
        for(int last = 0; last < 4; last++){
            dp[day][last] = 0;
            for(int activity = 0; activity < 3; activity++){
                if(activity != last){
                    int currentPoints = points[day][activity] + dp[day - 1][activity];
                    dp[day][last] = max(dp[day][last], currentPoints);
                }
            }
        }
    }
    
    return dp[n - 1][3]; // lastActivity = 3 means no restriction on last day
}

// space optimization approach
int ninjaTrainingSpaceOptimization(int n, vector<vector<int>> &points){
    // We only need previous day's results
    vector<int> prev(4, 0);
    
    // Base case: day 0
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]});
    
    for(int day = 1; day < n; day++){
        vector<int> curr(4, 0);
        for(int last = 0; last < 4; last++){
            curr[last] = 0;
            for(int activity = 0; activity < 3; activity++){
                if(activity != last){
                    int currentPoints = points[day][activity] + prev[activity];
                    curr[last] = max(curr[last], currentPoints);
                }
            }
        }
        prev = curr;
    }
    
    return prev[3];
}

signed main() {
    vector<vector<int>> points = {{1, 2, 5},
                                   {3, 1, 1},
                                   {3, 3, 3}};
    int n = points.size();
    
    int recursive = ninjaTraining(n - 1, 3, points); // 3 means no previous activity
    
    vector<vector<int>> dp1(n, vector<int>(4, -1));
    int memoization = ninjaTrainingMemoization(n - 1, 3, points, dp1);
    
    int tabulation = ninjaTrainingTabulation(n, points);
    int spaceOptimization = ninjaTrainingSpaceOptimization(n, points);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

