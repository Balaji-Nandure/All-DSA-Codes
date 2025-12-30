int minIncrementForUnique(vector<int>& nums) {
    /*
    Problem:
    Minimum Increment Operations to Make Array Unique.

    Approach:
    1. Sort the array.
    2. Traverse from left to right.
    3. Ensure nums[i] is at least nums[i-1] + 1.
       - If nums[i] <= nums[i-1], increment it to (nums[i-1] + 1).
       - Add the increment amount to the answer.
    4. This greedy approach ensures minimal total increments.

    Time: O(n log n)
    Space: O(1) (excluding sort space)
    */

    sort(nums.begin(), nums.end());

    int moves = 0;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] <= nums[i - 1]) {
            int required = nums[i - 1] + 1;
            moves += required - nums[i];
            nums[i] = required;
        }
    }

    return moves;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/minimum-number-increment-operations-make-array-elements-unique/

LeetCode:
https://leetcode.com/problems/minimum-increment-to-make-array-unique/
*/
