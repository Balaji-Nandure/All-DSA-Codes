void sortArray(vector<int>& arr) {
    /*
    Problem:
    Sort an array which contains values from 1 to n (each value may appear once).

    Approach (Cyclic Sort):
    1. Since values range from 1 to n, each value v should be at index (v - 1).
    2. Traverse the array:
       - While arr[i] is not at its correct position:
         swap arr[i] with arr[arr[i] - 1].
    3. Continue until all elements are placed correctly.

    Time: O(n)
    Space: O(1)
    */

    int i = 0;
    int n = arr.size();

    while (i < n) {
        int correctIndex = arr[i] - 1;

        if (arr[i] != arr[correctIndex]) {
            swap(arr[i], arr[correctIndex]);
        } else {
            i++;
        }
    }
}

/*
GeeksforGeeks:
https://www.geeksforgeeks.org/sort-an-array-of-1-to-n-values/

LeetCode:
https://leetcode.com/problems/set-mismatch/
(conceptually related to cyclic sort pattern)
*/
