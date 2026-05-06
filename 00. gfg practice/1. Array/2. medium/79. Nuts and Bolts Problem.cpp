/*
Problem: Nuts and Bolts Problem

GFG: https://www.geeksforgeeks.org/problems/nuts-and-bolts-problem0431/1

Description:
You are given two arrays representing nuts[] and bolts[] of equal size, where each element is denoted by a unique character. There exists a one-to-one mapping between nuts and bolts such that a nut matches a bolt if and only if both have the same symbol.

Rearrange both arrays so that each nut is matched with its corresponding bolt.

After matching, both arrays must be sorted according to the following predefined order: ['!', '#', '$', '%', '&', '*', '?', '@', '^'].

Note:
The arrays must be modified in-place.
Inputs are generated such that a valid arrangement is always possible.
In interviews, it is not allowed to compare a nut with another nut or a bolt with another bolt.

Examples:

Input: nuts[] = ['@', '%', '$', '#', '^'], bolts[] = ['%', '@', '#', '$', '^']
Output: ['#', '$', '%', '@', '^'], ['#', '$', '%', '@', '^']
Explanation: According to the predefined order, '#' is followed by '$', '%', '&', '*', '?', '@', and '^'.

Input: nuts[] = ['^','&', '%', '@', '#', '*', '$', '?', '!'], bolts[] = ['?', '#', '@', '%', '&', '*', '$' ,'^', '!']
Output: ['!', '#', '$', '%', '&', '*', '?', '@', '^'], ['!', '#', '$', '%', '&', '*', '?', '@', '^']
Explanation: We'll have to match first '!', then '#', '$', '%', '&', '*', '?', '@', '^' as per the required ordering.

Constraints:
1 ≤ n ≤ 9
The arrays 'nuts' and 'bolts' can only consist of the following elements: ['@', '#', '$', '%', '^', '&', '?', '*', '!'].
All elements of arrays 'nuts' and 'bolts' should be unique.

Approach (Custom Sorting using predefined order):
1. Store predefined order in array
2. Create frequency / presence map
3. Refill nuts and bolts based on order

Why it works:
- Elements are unique
- Order is fixed and small (only 9 chars)
- Direct mapping is optimal and avoids complex partitioning
- Since inputs guarantee valid arrangement, this approach always works

Time Complexity: O(n)
Space Complexity: O(1)

-----------------------------------------------------

PROBLEM: Nuts and Bolts (INTERVIEW VERSION)

 CONSTRAINT:
- You CANNOT compare nut with nut
- You CANNOT compare bolt with bolt
- Only allowed: nut ↔ bolt comparison

 This removes simple sorting → forces QUICK SORT STYLE solution

-----------------------------------------------------

INTUITION / APPROACH (INTERVIEW WAY):

 KEY IDEA:
Use QuickSort-like partitioning

STEP FLOW:

1. Pick a pivot from bolts[]
2. Use it to partition nuts[]
   → place matching nut at correct position

3. Now use that matched nut as pivot
   → partition bolts[]

4. Recursively solve left and right parts

-----------------------------------------------------

WHY THIS WORKS:

- Each partition aligns one nut with its correct bolt
- Recursively ensures full matching
- Mimics QuickSort partition logic

-----------------------------------------------------

PATTERN:
Modified QuickSort (Dual Array Partitioning)

-----------------------------------------------------

TIME COMPLEXITY:
Average: O(n log n)
Worst:   O(n^2)

SPACE:
O(log n) recursion

-----------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Partition function (like QuickSort)
    int partition(vector<char>& arr, int low, int high, char pivot) {
        
        int i = low;
        
        for (int j = low; j < high; j++) {
            
            // if current < pivot → move left
            if (arr[j] < pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
            // if element == pivot → move to end temporarily
            else if (arr[j] == pivot) {
                swap(arr[j], arr[high]);
                j--; // recheck swapped element
            }
        }
        
        // place pivot at correct position
        swap(arr[i], arr[high]);
        
        return i;
    }

    void matchHelper(vector<char>& nuts, vector<char>& bolts, int low, int high) {
        
        if (low >= high) return;
        
        // Step 1: use last bolt as pivot → partition nuts
        int pivotIndex = partition(nuts, low, high, bolts[high]);
        
        // Step 2: use matched nut → partition bolts
        partition(bolts, low, high, nuts[pivotIndex]);
        
        // Step 3: recurse left and right
        matchHelper(nuts, bolts, low, pivotIndex - 1);
        matchHelper(nuts, bolts, pivotIndex + 1, high);
    }

    void matchPairs(vector<char>& nuts, vector<char>& bolts) {
        
        matchHelper(nuts, bolts, 0, nuts.size() - 1);
    }
};

/*
-----------------------------------------------------

 INTERVIEW SUMMARY (VERY IMPORTANT):

- Say: "This is QuickSort-style partition problem"
- Key constraint: cross comparison only
- Solve by:
    nut partition ← bolt pivot
    bolt partition ← nut pivot

-----------------------------------------------------

 WHEN TO USE WHICH APPROACH:

GFG (practical):
→ Use predefined order → O(n)

INTERVIEW (real test):
→ Use QuickSort partition → O(n log n)

-----------------------------------------------------
*/
