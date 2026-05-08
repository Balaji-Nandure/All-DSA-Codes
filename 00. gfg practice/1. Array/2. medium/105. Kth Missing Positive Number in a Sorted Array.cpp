/*
Problem: Kth Missing Positive Number in a Sorted Array

GFG:
https://www.geeksforgeeks.org/problems/k-th-missing-element3635/1

LeetCode Similar:
https://leetcode.com/problems/kth-missing-positive-number/

----------------------------------------------------

Example:

arr = [2,3,4,7,11]
k = 5

Missing numbers:
1,5,6,8,9,10...

5th missing = 9

----------------------------------------------------

Main Observation:

For every index i:

Expected number at index i:
i + 1

But actual number is:
arr[i]

So missing count till index i is:

missing = arr[i] - (i + 1)

Example:

arr = [2,3,4,7,11]

i = 0
2 - 1 = 1 missing

i = 3
7 - 4 = 3 missing

i = 4
11 - 5 = 6 missing

----------------------------------------------------

Pattern:
Binary Search on Answer / Missing Count

----------------------------------------------------



/*
----------------------------------------------------

Approach 2:
Linear Traversal using Missing Count

If missing count till arr[i] is less than k,
then answer lies ahead.

----------------------------------------------------

Time Complexity:
O(n)

Space Complexity:
O(1)

----------------------------------------------------
*/

class LinearSolution {
public:

    // TC: O(n)
    // SC: O(1)

    int kthMissing(vector<int> &arr, int k) {

        for(int i = 0; i < arr.size(); i++) {

            // Missing count before arr[i]
            int missing = arr[i] - (i + 1);

            // kth missing lies before arr[i]
            if(missing >= k) {

                return i + k;
            }
        }

        // Missing lies after array end
        return arr.size() + k;
    }
};

/*
----------------------------------------------------

Approach 3:
Binary Search

We binary search the FIRST index
where missing count >= k.

missing count till mid:

arr[mid] - (mid + 1)

----------------------------------------------------

Why Binary Search Works?

Missing count increases monotonically.

So we can search efficiently.

----------------------------------------------------

Time Complexity:
O(log n)

Space Complexity:
O(1)

----------------------------------------------------
*/

class BinarySearchSolution {
public:

    // TC: O(log n)
    // SC: O(1)

    int kthMissing(vector<int> &arr, int k) {

        int n = arr.size();

        int low = 0;
        int high = n - 1;

        while(low <= high) {

            int mid = low + (high - low) / 2;

            // Missing numbers till mid
            int missing = arr[mid] - (mid + 1);

            // Need more missing numbers
            if(missing < k) {

                low = mid + 1;
            }
            else {

                high = mid - 1;
            }
        }

        /*
        low = first index where
        missing count >= k

        Answer formula:
        low + k
        */

        return low + k;
    }
};
