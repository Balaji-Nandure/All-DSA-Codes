bool areEqual(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Check whether two arrays are equal or not.
    - Two arrays are considered equal if they contain the same elements
      with the same frequencies, irrespective of order.

    Approach (Frequency Mapping / Canonical Representation):
    1. If sizes differ, arrays cannot be equal.
    2. Count frequency of each element in arr1.
    3. Traverse arr2 and decrease the corresponding frequency.
       - If any element is missing or count becomes negative → not equal.
    4. If all frequencies reduce to zero → arrays are equal.

    This follows value → frequency normalization:
    - Both arrays must map to the same canonical frequency state.

    Time: O(n)
    Space: O(n)
    */

    if (arr1.size() != arr2.size()) {
        return false;
    }

    unordered_map<int, int> freq;

    // Step 1: Count frequencies from arr1
    for (int x : arr1) {
        freq[x]++;
    }

    // Step 2: Reduce using arr2
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
https://www.geeksforgeeks.org/check-two-arrays-equal-not/

LeetCode:
No direct equivalent problem.
(Conceptually related to anagram / multiset equality check)
*/
