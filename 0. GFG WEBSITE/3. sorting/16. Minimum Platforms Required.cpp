int findPlatform(vector<int>& arr, vector<int>& dep) {
    /*
    Problem:
    Minimum Platforms Required so that no train waits.

    Important Rule:
    - If arrival time == departure time, they CANNOT use the same platform.

    Approach (Sorting + Two Pointers / Sweep Line):
    1. Sort arrival times and departure times separately.
    2. Use two pointers:
       - i for arrivals
       - j for departures
    3. Traverse events in chronological order:
       - If arr[i] <= dep[j]:
         - A train arrives before (or exactly when) a departure,
           so we need a new platform.
         - platforms++
         - i++
       - Else:
         - A train departs, freeing a platform.
         - platforms--
         - j++
    4. Track the maximum platforms used at any time.

    Note:
    Using <= (not <) because arrival == departure
    still needs a new platform as per problem statement.

    Time: O(n log n)
    Space: O(1)
    */

    int n = arr.size();
    if (n == 0) return 0;

    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int platforms = 0;
    int maxPlatforms = 0;
    int i = 0, j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms++;
            maxPlatforms = max(maxPlatforms, platforms);
            i++;
        } else {
            platforms--;
            j++;
        }
    }

    return maxPlatforms;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

LeetCode:
https://leetcode.com/problems/minimum-number-of-platforms-required-for-a-railway-bus-station/
*/
