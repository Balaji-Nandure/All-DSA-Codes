/*
Question: Given an array of integers and a target value, find the pair of numbers in the array whose sum is closest to the target. Return the pair sum (not the pair itself).

Approach:
1. Sort the array to allow the use of the two-pointer technique (O(n log n) time).
2. Use two pointers, one at the beginning and one at the end, and evaluate the sum of elements at these pointers.
3. Track the sum that has the minimum difference to the target.
4. Move the left pointer if the sum is less than the target; otherwise, move the right pointer, trying to get closer to the target.
5. Repeat this until the pointers meet. Return the closest sum found.

Time Complexity: O(n log n) for sorting + O(n) for the two-pointer scan.
Space Complexity: O(1), in-place.

GFG Link (Closest Pair to a Given Sum):
https://www.geeksforgeeks.org/find-a-pair-with-the-closest-sum-to-a-given-number/
LeetCode Link (Closest Two Sum): 
https://leetcode.com/problems/two-sum-less-than-k/ (Closest variant)
https://leetcode.com/problems/3sum-closest/ (3Sum Closest, for reference)

*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

vector<int> sumClosest(vector<int> &arr, int target) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<int> res;
    int minDiff = INT_MAX;

    int left = 0, right = n - 1;

    while (left < right) {
        int currSum = arr[left] + arr[right];

        // check if this pair is closer than the closest
        // pair so far
        if (abs(target - currSum) < minDiff) {
            minDiff = abs(target - currSum);
            res = {arr[left], arr[right]};
        }

        // if this pair has less sum, move to greater values
        if (currSum < target)
            left++;

        // if this pair has more sum, move to smaller values
        else if (currSum > target)
            right--;

        // If this pair has sum = target, return it
        else
            return res;
    }

    return res;
}