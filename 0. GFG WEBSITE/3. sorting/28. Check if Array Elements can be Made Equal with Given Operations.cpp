bool canMakeEqual(vector<int>& arr) {
    /*
    Problem:
    Given an array arr[] of N integers, you may choose a number X and,
    for each element, perform exactly one of the following:
      - Add X once
      - Subtract X once
      - Do nothing
    (Only one operation per element.)

    Determine whether there exists some X such that all elements
    can be made equal.

    Key Observation:
    Assume all elements are finally converted to a common value T.

    For any element a:
        T - a ∈ { -X, 0, +X }

    Therefore, all elements must already be within at most
    three distinct values:
        { T - X, T, T + X }

    This implies:
    1. The array can have at most 3 distinct values.
    2. If there are exactly 3 distinct values, they must be in
       arithmetic progression (middle is the average).

    Approach (Value Normalization / Difference Mapping):
    1. Store all unique values in a set.
    2. If unique count > 3 → impossible.
    3. If unique count ≤ 2 → always possible.
    4. If unique count == 3:
       - Sort the values: a, b, c
       - Check if (b - a) == (c - b)

    Time: O(n log n)
    Space: O(1)   (excluding set storage)
    */

    set<int> s(arr.begin(), arr.end());

    // More than 3 distinct values is impossible
    if (s.size() > 3) {
        return false;
    }

    // 1 or 2 distinct values can always be equalized
    if (s.size() <= 2) {
        return true;
    }

    // Exactly 3 distinct values
    vector<int> v(s.begin(), s.end());

    // They must form an arithmetic progression
    if (v[1] - v[0] == v[2] - v[1]) {
        return true;
    }

    return false;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-array-elements-can-be-made-equal-with-given-operations/

LeetCode:
No direct equivalent problem.
(Conceptually related to difference-mapping / normalization logic)
*/
