long long findMinDiff(vector<long long>& arr, int m) {
    /*
    Problem:
    Chocolate Distribution Problem.
    Given packets with chocolates and m students,
    distribute exactly one packet to each student such that
    the difference between max and min chocolates is minimized.

    Approach:
    1. If m > number of packets → return -1 (not enough packets).
    2. Sort the array of packet sizes.
    3. Use a sliding window of size m.
    4. For each window [i ... i+m-1]:
       - Compute diff = arr[i+m-1] - arr[i]
       - Track the minimum such difference.
    5. Return the minimum difference found.

    Time: O(n log n)
    Space: O(1)
    */

    int n = arr.size();
    if (m > n) return -1;

    sort(arr.begin(), arr.end());

    long long minDiff = LLONG_MAX;

    for (int i = 0; i + m - 1 < n; i++) {
        long long diff = arr[i + m - 1] - arr[i];
        minDiff = min(minDiff, diff);
    }

    return minDiff;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/chocolate-distribution-problem3825/1

LeetCode:
Not available as a standalone problem
*/
