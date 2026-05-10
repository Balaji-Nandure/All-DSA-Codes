/*
Problem: Combination Sum Without Repetition

GFG: https://www.geeksforgeeks.org/problems/combination-sum-ii/1

Description:
Given an array arr[] and a target, your task is to find all unique combinations in the array where the sum of elements is equal to target. Each element in arr[] can be used at most once in a combination.

Note: You can return your answer in any order, driver code will print them in sorted order. Test cases are generated such that number of unique combination does not exceed 10^6.

Examples:

Input: arr[] = [1, 2, 3], target = 5
Output: [[2, 3]]
Explanation: There is only one unique combinations whose sum is equal to target.

Input: arr[] = [1, 3, 2, 2, 2], target = 4
Output: [[1, 3], [2, 2]]
Explanation: There are two unique possible combinations whose sum is equal to target.

Constraints:
1 ≤ arr.size() ≤ 100
1 ≤ arr[i] ≤ 50
1 ≤ target ≤ 30

Approach (Backtracking with Sorting):
This is a combination generation problem where we need to find all unique combinations that sum to target.

Key insight:
- Sort the array to handle duplicates efficiently
- Use backtracking to explore all combinations
- Skip duplicates to avoid duplicate combinations
- Each element can be used at most once

Algorithm:
1. Sort the array to group duplicates together
2. Use backtracking to build combinations
3. At each step, either include current element or skip it
4. Skip duplicates when they would create same combinations
5. Add combinations when sum equals target

Time Complexity: O(2^n) in worst case
Space Complexity: O(n) for recursion stack

Pattern: Backtracking + Sorting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
BACKTRACKING WITH DUPLICATE HANDLING
=====================================================

TC: O(2^n)
SC: O(n)

🔥 BACKTRACKING APPROACH
- Sort array to handle duplicates
- Build combinations recursively
- Skip duplicates to avoid repeated results

🧠 KEY INSIGHT:
To avoid duplicate combinations:
- Sort the array first
- When encountering duplicates, skip them appropriately
- This ensures each unique combination appears once

🎯 ALGORITHM:
1. Sort array to group duplicates
2. Use backtracking to explore combinations
3. At each position: include or skip current element
4. Skip duplicates when they would create same combination
5. Add result when sum equals target

⚡ DUPLICATE SKIPPING:
if(i > start && arr[i] == arr[i-1])
    continue;
This skips duplicate starting points.
*/

class Solution {
public:

    void backtrack(vector<int>& arr,
                int target,
                int start,
                vector<int>& current,
                vector<vector<int>>& result) {

        // Base case: target reached
        if(target == 0) {
            result.push_back(current);
            return;
        }

        // Base case: no solution possible
        if(start >= arr.size() || target < 0) {
            return;
        }

        for(int i = start; i < arr.size(); i++) {

            // Skip duplicates
            if(i > start && arr[i] == arr[i-1]) {
                continue;
            }

            // Include current element
            current.push_back(arr[i]);

            // Recurse with reduced target
            backtrack(arr, target - arr[i], i + 1, current, result);

            // Backtrack
            current.pop_back();
        }
    }

    // TC: O(2^n)
    // SC: O(n)

    vector<vector<int>> CombinationSum2(vector<int>& arr, int sum) {

        sort(arr.begin(), arr.end());

        vector<vector<int>> result;

        vector<int> current;

        backtrack(arr, sum, 0, current, result);

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    COMBINATION GENERATION
    + DUPLICATE HANDLING
    + SUM TO TARGET

Think immediately:
    BACKTRACKING + SORTING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Sorting helps handle duplicates efficiently
2. Backtracking explores all possibilities
3. Skip duplicates to avoid repeated combinations
4. Each element used at most once (move to next index)

-----------------------------------------------------

COMMON MISTAKES:

1. Not sorting array first
2. Wrong duplicate skipping condition
3. Forgetting to backtrack (pop_back)
4. Not handling negative target properly
5. Using same element multiple times

-----------------------------------------------------

SIMILAR PROBLEMS

- Combination Sum problems
- Subset sum with duplicates
- Backtracking with pruning

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Find combinations that sum to target
- Handle duplicates in results
- Each element used once

Think:
Backtracking + Sorting

Key steps:
1. Sort array
2. Backtrack with include/skip
3. Skip duplicates appropriately
4. Add result when target reached

Duplicate condition:
if(i > start && arr[i] == arr[i-1])
    continue;

-----------------------------------------------------
*/
