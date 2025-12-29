int findPosition(vector<int>& arr, int target) {
    /*
    Approach:
    1. Since the array is conceptually infinite, we cannot apply binary search directly.
    2. First, find a search window where target may exist:
       - Start with low = 0, high = 1
       - Expand high exponentially until arr[high] >= target
    3. Once the window [low, high] is found, apply normal binary search inside it.

    Time:
    - Window expansion: O(log pos)
    - Binary search: O(log pos)
    Overall: O(log pos)
    Space: O(1)
    */

    int low = 0;
    int high = 1;

    // Step 1: Expand the search window
    while (high < arr.size() && arr[high] < target) {
        low = high;
        high = high * 2;
        if (high >= arr.size()) {
            high = arr.size() - 1;
        }
    }

    // Step 2: Binary search within window
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
