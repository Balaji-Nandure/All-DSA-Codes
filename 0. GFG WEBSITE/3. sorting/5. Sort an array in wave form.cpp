void waveSort(vector<int>& arr) {
    /*
    Approach:
    1. Sort the array first.
    2. Swap adjacent elements in pairs:
       - swap(arr[0], arr[1])
       - swap(arr[2], arr[3]) ...
    3. This guarantees wave form:
       arr[0] >= arr[1] <= arr[2] >= arr[3] ...

    Time: O(n log n)
    Space: O(1)
    */

    sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size() - 1; i += 2) {
        swap(arr[i], arr[i + 1]);
    }
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/wave-array-1587115621/1

LeetCode:
Not available as a direct standalone problem
*/
