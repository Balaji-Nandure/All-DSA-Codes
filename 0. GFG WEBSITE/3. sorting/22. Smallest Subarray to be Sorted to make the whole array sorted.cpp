vector<int> smallestUnsortedSubarray(vector<int>& arr) {
    /*
    Problem:
    Find the smallest subarray which, if sorted,
    results in the entire array being sorted.

    Approach:
    1. Traverse from left to right to find the first index l
       where arr[l] > arr[l+1].
    2. Traverse from right to left to find the first index r
       where arr[r] < arr[r-1].
    3. If no such indices found → array already sorted → return {-1, -1}.
    4. Find min and max elements in subarray arr[l..r].
    5. Extend l to the left while arr[l-1] > subarray_min.
    6. Extend r to the right while arr[r+1] < subarray_max.
    7. Return {l, r}.

    Time: O(n)
    Space: O(1)
    */

    int n = arr.size();
    int l = -1, r = -1;

    // Step 1: find left boundary
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            l = i;
            break;
        }
    }

    // Already sorted
    if (l == -1) return {-1, -1};

    // Step 2: find right boundary
    for (int i = n - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            r = i;
            break;
        }
    }

    // Step 4: find min and max in subarray
    int subMin = INT_MAX, subMax = INT_MIN;
    for (int i = l; i <= r; i++) {
        subMin = min(subMin, arr[i]);
        subMax = max(subMax, arr[i]);
    }

    // Step 5: extend left boundary
    while (l > 0 && arr[l - 1] > subMin) {
        l--;
    }

    // Step 6: extend right boundary
    while (r < n - 1 && arr[r + 1] < subMax) {
        r++;
    }

    return {l, r};
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/minimum-length-unsorted-subarray/0

LeetCode:
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
*/
