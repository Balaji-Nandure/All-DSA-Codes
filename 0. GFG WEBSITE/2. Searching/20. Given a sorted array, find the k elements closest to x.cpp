// Binary search the left boundary of a window of size k

// Compare distances:

// If x - arr[mid] > arr[mid + k] - x → shift window right

// Else → shift left

// Final answer = arr[left ... left + k - 1]

// Time: O(log(n-k) + k)
// Space: O(1) (excluding output)

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int n = arr.size();
    int left = 0, right = n - k; // window of size k

    // Binary search for the leftmost start of window
    while (left < right) {
        int mid = left + (right - left) / 2; // middle of window options

        // Compare which edge is closer to x
        if (x - arr[mid] > arr[mid + k] - x) {
            left = mid + 1; // move window right
        } else {
            right = mid;    // move window left
        }
    }

    // Collect k closest elements starting from left
    vector<int> result;
    for (int i = left; i < left + k; i++) {
        result.push_back(arr[i]);
    }

    return result;
}
