bool areDisjoint(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Check whether two arrays are disjoint or not.
    - Two arrays are disjoint if they do NOT have any common element.

    Approach (Value Mapping / Presence Check):
    1. Store all elements of arr1 in a hash set.
    2. Traverse arr2:
       - If any element exists in the set, arrays are NOT disjoint.
    3. If traversal completes without a match, arrays are disjoint.

    This follows the same value → presence mapping pattern:
    - Each value maps to whether it already exists.
    - A collision means violation of disjoint property.

    Time: O(n + m)
    Space: O(n)
    */

    unordered_set<int> seen;

    // Step 1: Insert all elements of arr1
    for (int x : arr1) {
        seen.insert(x);
    }

    // Step 2: Check for common elements in arr2
    for (int x : arr2) {
        if (seen.count(x)) {
            return false;
        }
    }

    return true;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-two-arrays-are-disjoint-or-not/

LeetCode:
No direct equivalent problem.
(Conceptually related to set intersection check)
*/
