void sortArrayAccordingToOrder(vector<int>& arr, vector<int>& order) {
    /*
    Problem:
    Sort an array according to the order defined by another array.
    - Elements present in `order` should appear first in `arr`, following the same order.
    - Remaining elements (not present in `order`) should be placed at the end in ascending order.

    Approach (Index Mapping + Cyclic Placement Idea):
    1. Count the frequency of each element in `arr`.
    2. Traverse the `order` array:
       - For each value, place it in `arr` as many times as it appears.
       - Maintain an index to place elements sequentially.
    3. For remaining elements not in `order`:
       - Place them in increasing order using the stored frequencies.

    Note:
    - This follows the same "value → placement index" discipline as cyclic/index mapping problems,
      adapted because the target positions are dictated by another array.

    Time: O(n log n)   (due to ordered traversal of remaining elements)
    Space: O(n)
    */

    unordered_map<int, int> freq;

    // Step 1: Frequency count
    for (int x : arr) {
        freq[x]++;
    }

    int idx = 0;

    // Step 2: Place elements according to given order
    for (int x : order) {
        while (freq[x] > 0) {
            arr[idx++] = x;
            freq[x]--;
        }
        freq.erase(x); // remove to mark handled
    }

    // Step 3: Place remaining elements in ascending order
    vector<int> remaining;
    for (auto& it : freq) {
        while (it.second--) {
            remaining.push_back(it.first);
        }
    }

    sort(remaining.begin(), remaining.end());

    for (int x : remaining) {
        arr[idx++] = x;
    }
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/sort-array-according-order-defined-another-array/

LeetCode:
No direct equivalent problem.
(Conceptually related to custom ordering + index mapping)
*/
