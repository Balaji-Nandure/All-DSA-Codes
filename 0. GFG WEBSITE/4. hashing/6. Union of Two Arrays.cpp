int unionOfArrays(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Find the number of distinct elements present in the union of two arrays.

    Approach (Value Presence Mapping):
    1. Insert all elements of arr1 into a hash set.
    2. Insert all elements of arr2 into the same set.
    3. The size of the set represents the union count.

    This follows value → presence normalization:
    - Each distinct value is mapped once, regardless of repetitions.

    Time: O(n + m)
    Space: O(n)
    */

    unordered_set<int> s;

    // Insert elements of first array
    for (int x : arr1) {
        s.insert(x);
    }

    // Insert elements of second array
    for (int x : arr2) {
        s.insert(x);
    }

    return s.size();
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/union-and-intersection-of-two-arrays/

LeetCode:
https://leetcode.com/problems/intersection-of-two-arrays/
(conceptually related; LeetCode focuses on intersection output)
*/
