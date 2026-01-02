vector<int> unionWithDuplicates(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Find the union of two arrays considering duplicates.
    - Each element should appear in the result as many times
      as its maximum frequency in either array.

    Example:
    arr1 = [1, 2, 2, 3]
    arr2 = [2, 2, 4]
    Result = [1, 2, 2, 3, 4]

    Approach (Frequency Mapping / Max Count Normalization):
    1. Count frequency of elements in arr1.
    2. Count frequency of elements in arr2.
    3. For each distinct element:
       - Take max(freq1[element], freq2[element])
       - Push that many occurrences to the result.

    This follows canonical frequency mapping:
    - Union preserves maximum contribution of each value.

    Time: O(n + m)
    Space: O(n + m)
    */

    unordered_map<int, int> freq1, freq2;

    // Step 1: Frequency of arr1
    for (int x : arr1) {
        freq1[x]++;
    }

    // Step 2: Frequency of arr2
    for (int x : arr2) {
        freq2[x]++;
    }

    vector<int> result;

    // Step 3: Build union using maximum frequency
    for (auto& it : freq1) {
        int val = it.first;
        int cnt = max(freq1[val], freq2[val]);

        while (cnt--) {
            result.push_back(val);
        }
        freq2.erase(val); // mark handled
    }

    // Step 4: Remaining elements only in arr2
    for (auto& it : freq2) {
        while (it.second--) {
            result.push_back(it.first);
        }
    }

    return result;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/union-of-two-arrays-with-duplicates/

LeetCode:
No direct equivalent problem.
(Conceptually related to multiset union)
*/
