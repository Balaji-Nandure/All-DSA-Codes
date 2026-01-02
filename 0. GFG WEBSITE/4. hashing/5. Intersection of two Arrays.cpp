vector<int> intersection(vector<int>& arr1, vector<int>& arr2) {
    /*
    Problem:
    Find the intersection of two arrays.
    - Each element in the result should appear as many times as it appears
      in both arrays (minimum frequency).
    - Order of elements in the result does not matter.

    Approach (Frequency Mapping / Value → Count):
    1. Count the frequency of each element in arr1.
    2. Traverse arr2:
       - If the element exists in the map with count > 0,
         add it to the result and decrement the count.
    3. Return the collected intersection elements.

    This follows value normalization via frequency mapping:
    - Each value contributes only up to its available mapped count.

    Time: O(n + m)
    Space: O(n)
    */

    unordered_map<int, int> freq;
    vector<int> result;

    // Step 1: Frequency count for arr1
    for (int x : arr1) {
        freq[x]++;
    }

    // Step 2: Build intersection using arr2
    for (int x : arr2) {
        if (freq[x]) {
            result.push_back(x);
            freq[x]--;
        }
    }

    return result;
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/intersection-of-two-arrays/

LeetCode:
https://leetcode.com/problems/intersection-of-two-arrays-ii/
*/
