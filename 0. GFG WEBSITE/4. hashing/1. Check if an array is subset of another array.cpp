bool isSubset(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Check whether arr2[] is a subset of arr1[].
    - Every element of arr2 must be present in arr1.
    - Frequency matters (multiset subset).

    Approach (Frequency Mapping / Value → Count):
    1. Count the frequency of each element in arr1.
    2. Traverse arr2:
       - For each element, reduce its count from the map.
       - If an element is missing or count becomes negative → not a subset.
    3. If all elements are verified → subset exists.

    This aligns with index/value-mapping discipline:
    - Each value maps to its available count.
    - arr2 consumes from arr1’s mapped supply.

    Time: O(n + m)
    Space: O(n)
    */

    unordered_map<int, int> freq;

    // Step 1: Count frequency of arr1
    for (int x : arr1) {
        freq[x]++;
    }

    // Step 2: Check elements of arr2
    for (int x : arr2) {
        if (freq[x] == 0) {
            return false;
        }
        freq[x]--;
    }

    return true;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/check-array-subset-another-array/

LeetCode:
No direct equivalent problem.
(Conceptually related to multiset containment check)
*/
