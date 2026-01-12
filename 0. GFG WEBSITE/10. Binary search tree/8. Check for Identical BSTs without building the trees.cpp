/*
Problem:
Check for Identical BSTs without Building the Trees

Given two arrays arr1[] and arr2[] representing the insertion order
of elements into two Binary Search Trees, check whether the BSTs
formed from these arrays would be identical.

Rules:
- You must NOT construct the BSTs.
- BST property: left < root < right
- No duplicate elements.

Example:
Input:
arr1 = [8, 3, 6, 1, 4, 7, 10, 14, 13]
arr2 = [8, 3, 1, 6, 4, 7, 10, 14, 13]

Output:
true

Approach (Optimized – Range Validation Recursion):
- The first valid element in a range is the root.
- For both arrays:
  - Find the first element within (min, max).
  - This element must match in both arrays.
- Recursively check left subtree range (min, root)
  and right subtree range (root, max).
- If all recursive checks pass, BSTs are identical.

GeeksforGeeks:
https://www.geeksforgeeks.org/check-for-identical-bsts-without-building-the-trees/

Time Complexity:
O(N^2) worst case

Space Complexity:
O(N) recursion stack
*/

class Solution {
public:
    int findNext(const vector<int>& arr, int start, int low, int high) {
        for (int i = start; i < arr.size(); i++) {
            if (arr[i] > low && arr[i] < high)
                return i;
        }
        return -1;
    }

    bool checkUtil(const vector<int>& a, const vector<int>& b,
                    int i1, int i2, int low, int high) {

        int idx1 = findNext(a, i1, low, high);
        int idx2 = findNext(b, i2, low, high);

        if (idx1 == -1 && idx2 == -1) return true;
        if (idx1 == -1 || idx2 == -1) return false;
        if (a[idx1] != b[idx2]) return false;

        return checkUtil(a, b, idx1 + 1, idx2 + 1, low, a[idx1]) &&
                checkUtil(a, b, idx1 + 1, idx2 + 1, a[idx1], high);
    }

    bool isSameBST(vector<int>& arr1, vector<int>& arr2) {

        if (arr1.size() != arr2.size()) return false;

        return checkUtil(arr1, arr2, 0, 0, INT_MIN, INT_MAX);
    }
};
    