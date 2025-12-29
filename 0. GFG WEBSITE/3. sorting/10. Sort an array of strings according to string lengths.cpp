void sortByLength(vector<string>& arr) {
    /*
    Problem:
    Sort an array of strings according to their lengths.

    Approach:
    1. Use STL sort with a custom comparator.
    2. Comparator compares strings based on their length.
    3. Sorts strings in non-decreasing order of length.
       (If lengths are equal, relative order does not matter unless specified.)

    Time: O(n log n)
    Space: O(1) (ignoring sort internals)
    */
    // here we are using stable sort instead of sort.
    stable_sort(arr.begin(), arr.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/sort-an-array-of-strings-according-to-string-lengths/

LeetCode:
Not available as a standalone problem
*/
