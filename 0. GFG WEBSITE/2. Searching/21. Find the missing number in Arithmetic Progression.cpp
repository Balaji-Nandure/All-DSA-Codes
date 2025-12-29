int findMissingAP(vector<int>& arr) {
    int n = arr.size();

    // Common difference (one element missing)
    int d = (arr[n - 1] - arr[0]) / n;

    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        int expected = arr[0] + mid * d;

        // Left part is correct
        if (arr[mid] == expected) {
            left = mid + 1;
        }
        // Mismatch found, go left
        else {
            right = mid - 1;
        }
    }

    // Missing value
    return arr[0] + left * d;
}
