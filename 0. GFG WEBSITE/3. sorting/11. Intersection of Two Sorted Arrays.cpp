vector<int> intersectionSortedArrays(vector<int>& a, vector<int>& b) {
    /*
    Problem:
    Find the intersection of two sorted arrays.
    Each common element should appear ONLY ONCE in the result
    (unique intersection).

    Approach (Two Pointers with Duplicate Skipping):
    1. Use two pointers i and j.
    2. If a[i] == b[j]:
       - If result is empty OR last element != a[i], add to result.
       - Move both pointers.
    3. If a[i] < b[j] → move i.
    4. Else → move j.
    5. This automatically skips duplicates due to pointer movement
       and result check.

    Time: O(n + m)
    Space: O(1) (excluding output)
    */

    vector<int> result;
    int i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            // to avoid duplicates
            if (result.empty() || result.back() != a[i]) {
                result.push_back(a[i]);
            }
            i++;
            j++;
        }
        else if (a[i] < b[j]) {
            i++;
        }
        else {
            j++;
        }
    }

    return result;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/intersection-of-two-sorted-arrays-1587115621/1

LeetCode:
https://leetcode.com/problems/intersection-of-two-arrays/
*/
