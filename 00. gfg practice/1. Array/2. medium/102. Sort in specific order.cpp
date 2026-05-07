/*
Problem: Sort in Specific Order

GFG:
https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1

Example:
Input:
arr = [1,2,3,5,4,7,10]

Output:
[7,5,3,1,2,4,10]

----------------------------------------------------

Intuition / Approach:

We need:
1. Odd numbers first in DESCENDING order
2. Even numbers later in ASCENDING order

So:
- Separate odd and even numbers
- Sort odd descending
- Sort even ascending
- Merge both

----------------------------------------------------

Pattern:
Custom Sorting

----------------------------------------------------

Approach 1:
Using Two Extra Arrays

1. Store odd numbers separately
2. Store even numbers separately
3. Sort odd descending
4. Sort even ascending
5. Put back into original array

----------------------------------------------------

Time Complexity:
O(n log n)

Space Complexity:
O(n)

----------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class ExtraArraySolution {
public:

    // TC: O(n log n)
    // SC: O(n)

    void sortIt(vector<long long>& arr) {

        vector<long long> odd;
        vector<long long> even;

        // Separate odd/even
        for(long long num : arr) {

            if(num % 2 == 1)
                odd.push_back(num);
            else
                even.push_back(num);
        }

        // Odd descending
        sort(odd.begin(), odd.end(), greater<long long>());

        // Even ascending
        sort(even.begin(), even.end());

        int idx = 0;

        // Put odd first
        for(long long num : odd) {
            arr[idx++] = num;
        }

        // Then even
        for(long long num : even) {
            arr[idx++] = num;
        }
    }
};

/*
----------------------------------------------------

Approach 2:
Custom Comparator Sorting

We can directly sort using comparator.

Rules:
1. Odd comes before even
2. Among odd -> descending
3. Among even -> ascending

----------------------------------------------------

Time Complexity:
O(n log n)

Space Complexity:
O(1)
(ignoring sorting internal stack)

----------------------------------------------------
*/

class ComparatorSolution {
public:

    // TC: O(n log n)
    // SC: O(1)

    static bool cmp(long long a, long long b) {

        // a odd, b even
        if(a % 2 == 1 && b % 2 == 0)
            return true;

        // a even, b odd
        if(a % 2 == 0 && b % 2 == 1)
            return false;

        // Both odd -> descending
        if(a % 2 == 1)
            return a > b;

        // Both even -> ascending
        return a < b;
    }

    void sortIt(vector<long long>& arr) {

        sort(arr.begin(), arr.end(), cmp);
    }
};

/*
----------------------------------------------------

Best / Online Judge Solution

Using Custom Comparator

----------------------------------------------------
*/

class Solution {
public:

    static bool cmp(long long a, long long b) {

        // Odd numbers first
        if((a & 1) && !(b & 1))
            return true;

        if(!(a & 1) && (b & 1))
            return false;

        // Both odd -> descending
        if(a & 1)
            return a > b;

        // Both even -> ascending
        return a < b;
    }

    // TC: O(n log n)
    // SC: O(1)

    void sortIt(vector<long long>& arr) {

        sort(arr.begin(), arr.end(), cmp);
    }
};

/*
----------------------------------------------------

Dry Run:

arr = [1,2,3,5,4,7,10]

After sorting:
Odds descending:
7 5 3 1

Evens ascending:
2 4 10

Final:
7 5 3 1 2 4 10

----------------------------------------------------

Common Mistakes:

1. Sorting odd ascending accidentally
2. Forgetting odd should come BEFORE even
3. Using separate sorts incorrectly
4. Wrong comparator return conditions

----------------------------------------------------

Reusable Pattern:

Whenever question says:
- "Sort according to custom rules"
- "Priority-based sorting"

Think:
Custom Comparator

----------------------------------------------------
*/
