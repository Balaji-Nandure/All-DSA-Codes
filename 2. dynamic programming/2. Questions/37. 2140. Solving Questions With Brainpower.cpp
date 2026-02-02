


/*
Problem:
2140. Solving Questions With Brainpower

Description:
You are given a 0-indexed 2D integer array questions where questions[i] = [points_i, brainpower_i].

The array describes the questions of an exam, where you have to process the questions in order 
(i.e., starting from question 0) and make a decision whether to solve or skip each question. 
Solving question i will earn you points_i points but you will be unable to solve each of the 
next brainpower_i questions. If you skip question i, you get to make the decision on the next question.

For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
- If question 0 is solved, you will earn 3 points but you will be unable to solve questions 1 and 2.
- If instead, question 0 is skipped and question 1 is solved, you will earn 4 points but you will 
  be unable to solve questions 2 and 3.

Return the maximum points you can earn for the exam.

Approach:
Recursion + Memoization (Top-Down DP)

State:
solve(i) = maximum points from questions[i..n-1]

Transition:
At each question i, we have two choices:
1. Solve it: earn points[i] + solve(i + brainpower[i] + 1)
2. Skip it: solve(i + 1)

Take the maximum of both choices.

Base case:
If i >= n, return 0 (no more questions)

LeetCode:
https://leetcode.com/problems/solving-questions-with-brainpower/

Time Complexity:
O(n) where n is the number of questions

Space Complexity:
O(n) for dp array and recursion stack
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    long long solve(int i, vector<vector<int>>& questions, vector<long long>& dp) {
        // Base case: no more questions
        if (i >= questions.size()) {
            return 0;
        }
        
        // Check memoized result
        if (dp[i] != -1) {
            return dp[i];
        }
        
        int points = questions[i][0];
        int brainpower = questions[i][1];
        
        // Option 1: Solve current question
        long long solve_current = points + solve(i + brainpower + 1, questions, dp);
        
        // Option 2: Skip current question
        long long skip_current = solve(i + 1, questions, dp);
        
        // Take maximum of both options
        return dp[i] = max(solve_current, skip_current);
    }
    
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n, -1);
        
        return solve(0, questions, dp);
    }
};

// Time Complexity: O(n)
// Space Complexity: O(n)

// Alternative: Bottom-Up DP (Tabulation)
class Solution2 {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1, 0);
        
        // Process questions from right to left
        for (int i = n - 1; i >= 0; i--) {
            int points = questions[i][0];
            int brainpower = questions[i][1];
            int next_question = i + brainpower + 1;
            
            // Option 1: Solve current question
            long long solve_current = points + (next_question < n ? dp[next_question] : 0);
            
            // Option 2: Skip current question
            long long skip_current = dp[i + 1];
            
            dp[i] = max(solve_current, skip_current);
        }
        
        return dp[0];
    }
};

//  solving form 0 to n 
class Solution2 {
    public:
        long long mostPoints(vector<vector<int>>& questions) {
            int n = questions.size();
            vector<long long> dp(n + 1, 0);
            
            // Process questions from left to right
            for (int i = 0; i < n; i++) {
                int points = questions[i][0];
                int brainpower = questions[i][1];
                int next_question = i + brainpower + 1;
                
                // Option 1: Skip current question - carry forward previous max
                dp[i + 1] = max(dp[i + 1], dp[i]);
                
                // Option 2: Solve current question - add points to dp[i] and update future position
                if (next_question <= n) {
                    dp[next_question] = max(dp[next_question], dp[i] + points);
                }
            }
            
            return dp[n];
        }
    };

// Time Complexity: O(n)
// Space Complexity: O(n)





