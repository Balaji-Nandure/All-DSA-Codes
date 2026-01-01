int minSubsets(vector<int>& arr) {
    /*
    Problem:
    Partition an array into the minimum number of subsets such that
    each subset contains consecutive numbers.

    Example:
    arr = [1, 2, 3, 5, 6, 8]
    Output = 3
    Subsets: [1,2,3], [5,6], [8]

    Approach (Sorting + Greedy Index Mapping):
    1. Sort the array to bring numbers in increasing order.
    2. Traverse the array linearly:
       - If the current number is NOT consecutive to the previous one,
         it must start a new subset.
    3. Count how many times a new subset is started.

    This greedy works because:
    - Sorted order ensures smallest possible extension.
    - Any gap (>1 difference) forces a new subset.

    Time: O(n log n)   (sorting)
    Space: O(1)        (in-place, ignoring sort stack)
    */

    int n = arr.size();
    if (n == 0) return 0;

    sort(arr.begin(), arr.end());

    int subsets = 1;  // at least one subset

    for (int i = 1; i < n; i++) {
        // If not consecutive, start a new subset
        if (arr[i] != arr[i - 1] + 1) {
            subsets++;
        }
    }

    return subsets;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/minimum-subsets-consecutive-numbers/

LeetCode:
No direct equivalent problem.
(Conceptually related to greedy + sorting pattern)
*/
