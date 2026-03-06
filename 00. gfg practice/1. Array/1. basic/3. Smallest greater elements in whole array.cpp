/*
Problem:
For every element, find the smallest element
in the whole array that is strictly greater than it.
If none exists, return -10000000.
*/

vector<int> greaterElement(int arr[], int n) {

    vector<int> result(n);

    // Step 1: Copy array
    vector<int> temp(arr, arr + n);

    // Step 2: Sort it
    sort(temp.begin(), temp.end());

    // Step 3: For each element
    for(int i = 0; i < n; i++) {

        // Find first element greater than arr[i]
        auto it = upper_bound(temp.begin(), temp.end(), arr[i]);

        if(it == temp.end())
            result[i] = -10000000;
        else
            result[i] = *it;
    }

    return result;
}
