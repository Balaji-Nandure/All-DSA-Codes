void threeWayPartition(vector<int>& arr, int lowVal, int highVal) {
    /*
    Problem:
    Three-way partition an array around a given range [lowVal, highVal].

    Goal:
    - All elements < lowVal come first
    - All elements in range [lowVal, highVal] come next
    - All elements > highVal come last
    (Order inside groups does NOT matter)

    Approach (Dutch National Flag – 3 Pointers):
    1. Use three pointers:
       - left  → boundary for elements < lowVal
       - mid   → current element
       - right → boundary for elements > highVal
    2. Traverse while mid <= right:
       - If arr[mid] < lowVal:
         swap(arr[left], arr[mid]), left++, mid++
       - Else if arr[mid] > highVal:
         swap(arr[mid], arr[right]), right--
       - Else:
         mid++
    3. Partition completes in one pass.

    Time: O(n)
    Space: O(1)
    */

    int left = 0;
    int mid = 0;
    int right = arr.size() - 1;

    while (mid <= right) {
        if (arr[mid] < lowVal) {
            swap(arr[left], arr[mid]);
            left++;
            mid++;
        }
        else if (arr[mid] > highVal) {
            swap(arr[mid], arr[right]);
            right--;
        }
        else {
            mid++;
        }
    }
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/three-way-partitioning/1

LeetCode:
https://leetcode.com/problems/sort-colors/   (conceptually equivalent)
*/
