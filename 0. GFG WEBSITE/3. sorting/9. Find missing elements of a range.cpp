vector<int> findMissingElements(vector<int>& arr, int low, int high) {
    /*
    Problem:
    Find all missing elements in the given range [low, high].

    Approach:
    1. Given an array (not necessarily continuous) and a range [low, high].
    2. Use a boolean / marker array of size (high - low + 1).
    3. Mark all present elements that lie within the range.
    4. Traverse the marker array:
       - Indices not marked correspond to missing elements.
    5. Collect and return all missing values.

    Time: O(n + range)
    Space: O(range)
    */

    vector<bool> present(high - low + 1, false);

    // Mark existing elements
    for (int x : arr) {
        if (x >= low && x <= high) {
            present[x - low] = true;
        }
    }

    // Collect missing elements
    vector<int> missing;
    for (int i = 0; i < present.size(); i++) {
        if (!present[i]) {
            missing.push_back(low + i);
        }
    }

    return missing;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/find-missing-elements-range/

LeetCode:
Not available as a direct problem
*/
