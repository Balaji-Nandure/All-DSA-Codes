void sort012(vector<int>& nums) {
    /*
    Problem:
    Sort an array consisting only of 0s, 1s, and 2s.

    Approach (Dutch National Flag Algorithm):
    1. Maintain three pointers:
       - low   → boundary for 0s
       - mid   → current index
       - high  → boundary for 2s
    2. Traverse while mid <= high:
       - If nums[mid] == 0:
         swap(nums[low], nums[mid]), low++, mid++
       - If nums[mid] == 1:
         mid++
       - If nums[mid] == 2:
         swap(nums[mid], nums[high]), high--
    3. Array gets partitioned into:
       [0s | 1s | 2s]

    Time: O(n)
    Space: O(1)
    */

    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if (nums[mid] == 1) {
            mid++;
        }
        else { // nums[mid] == 2
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s/1

LeetCode:
https://leetcode.com/problems/sort-colors/
*/
