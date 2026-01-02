/*
Problem:
Missing Elements of a Range in an Array

Given an integer array arr[] of size n and two integers low and high,
find all the missing elements in the inclusive range [low, high]
that are NOT present in the array.

Examples:
Input  : arr = [1, 3, 5, 4], low = 1, high = 7
Output : [2, 6, 7]

Input  : arr = [10, 12, 11], low = 10, high = 15
Output : [13, 14, 15]

Input  : arr = [], low = 1, high = 5
Output : [1, 2, 3, 4, 5]


Approach (Expected / Optimal – Hashing):
1. Insert all elements of the array into an unordered_set.
2. Iterate from low to high:
   - If the current number is not present in the set,
     it is a missing element.
3. Collect all such missing numbers in the result.

Why this works:
- Hash set provides O(1) average-time lookups.
- Every number in the required range is checked exactly once.
- Simple and robust even when array is empty.

Time Complexity:
O(n + (high - low + 1))

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-missing-elements-of-a-range/

LeetCode:
No direct equivalent problem.
(Related to range checking and hashing patterns)
*/

vector<int> missingElementsInRange(vector<int>& arr, int low, int high) {
    unordered_set<int> s;

    // Store all elements present in the array
    for (int x : arr) {
        s.insert(x);
    }

    vector<int> result;

    // Check each number in the given range
    for (int val = low; val <= high; val++) {
        if (s.find(val) == s.end()) {
            result.push_back(val);
        }
    }

    return result;
}
