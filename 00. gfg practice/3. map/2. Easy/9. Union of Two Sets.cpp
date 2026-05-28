/*
Problem: Union of Two Sets

Given two sets a and b, the task is to find the number of elements in the union between these two sets.
The Union of the two sets can be defined as the set containing distinct elements from both sets. If there are repetitions, then only one element occurrence should be there in the union.

Constraints:
1 <= a.size(), b.size() <= 10^6
0 <= a[i], b[i] < 10^5

--------------------------------------------------

Pattern:
Hashing / Set

--------------------------------------------------

Key Observation:
- The union of two collections mathematically refers to all the unique elements present in either collection.
- A Hash Set inherently prevents duplicate entries, meaning any repeated numbers will just be ignored upon insertion. This makes it the perfect data structure for this problem.
- By dumping all elements from both arrays into a single Hash Set, the final size of the set will be exactly equal to the number of distinct elements in their union.

--------------------------------------------------

Approach:
1. Initialize an `unordered_set<int> union_set`.
2. Traverse the first array `a` and insert every element into `union_set`.
3. Traverse the second array `b` and insert every element into `union_set`.
4. Return the total number of elements in the set, which can simply be obtained via `union_set.size()`.

--------------------------------------------------

Time Complexity: O(N + M) where N and M are the sizes of arrays `a` and `b`. Inserting elements into an `unordered_set` takes O(1) time on average.
Space Complexity: O(N + M) in the worst-case scenario where all elements across both arrays are entirely distinct, as they will all be stored in the hash set.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/union-of-two-arrays3538/1
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int doUnion(vector<int>& a, vector<int>& b) {
        unordered_set<int> union_set;
        
        // Insert all elements from the first array
        for (int num : a) {
            union_set.insert(num);
        }
        
        // Insert all elements from the second array
        for (int num : b) {
            union_set.insert(num);
        }
        
        // The size of the set is the count of distinct elements
        return union_set.size();
    }
};
