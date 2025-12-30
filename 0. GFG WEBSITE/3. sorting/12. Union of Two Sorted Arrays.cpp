vector<int> unionSortedArrays(vector<int>& a, vector<int>& b) {
    /*
    Problem:
    Return the UNION of two sorted arrays.
    - Result must contain DISTINCT elements only.
    - Result must be in SORTED order.

    Approach (Two Pointers + Duplicate Skipping):
    1. Use two pointers i and j starting from 0.
    2. Compare a[i] and b[j]:
       - If equal → add once, move both pointers.
       - If smaller → add smaller element, move its pointer.
    3. While adding:
       - Ensure the last added element is not duplicated in result.
    4. After one array ends:
       - Add remaining elements from the other array (skip duplicates).

    Time: O(n + m)
    Space: O(1) (excluding output)
    */

    vector<int> result;
    int i = 0, j = 0;

    // Merge with uniqueness
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) {
            if (result.empty() || result.back() != a[i]) {
                result.push_back(a[i]);
            }
            i++;
            j++;
        }
        else if (a[i] < b[j]) {
            if (result.empty() || result.back() != a[i]) {
                result.push_back(a[i]);
            }
            i++;
        }
        else {
            if (result.empty() || result.back() != b[j]) {
                result.push_back(b[j]);
            }
            j++;
        }
    }

    // Remaining elements of a[]
    while (i < a.size()) {
        if (result.empty() || result.back() != a[i]) {
            result.push_back(a[i]);
        }
        i++;
    }

    // Remaining elements of b[]
    while (j < b.size()) {
        if (result.empty() || result.back() != b[j]) {
            result.push_back(b[j]);
        }
        j++;
    }

    return result;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1

LeetCode:
https://leetcode.com/problems/intersection-of-two-arrays/ 
(Note: Union variant not directly available on LeetCode)
*/
