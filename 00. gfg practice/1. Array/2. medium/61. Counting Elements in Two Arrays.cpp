/*
PROBLEM: Counting Elements in Two Arrays
------------------------------------------------
Given:
- a[] and b[] - two unsorted arrays (may contain duplicates)
- For each element in a[], count elements in b[] <= that element

Return:
- Vector of counts corresponding to each element in a[]

Example:
a[] = [4, 8, 7, 5, 1], b[] = [4, 48, 3, 0, 1, 1, 5]
Output = [5, 6, 6, 6, 3]
Explanation:
For a[0]=4: b elements <=4 are [4,3,0,1,1] → count=5
For a[1]=8: all 6 elements in b <=8 → count=6
For a[2]=7: all 6 elements in b <=7 → count=6
For a[3]=5: b elements <=5 are [4,3,0,1,1,5] → count=6
For a[4]=1: b elements <=1 are [0,1,1] → count=3

Constraints:
1 ≤ a.size(), b.size() ≤ 10^5
0 ≤ a[i], b[j] ≤ 10^5

------------------------------------------------
INTUITION / APPROACH:
------------------------------------------------
Pattern: Sorting + Binary Search + Frequency Count

Key Idea:
- Sort array b[] to enable binary search
- For each element in a[], find upper_bound in sorted b[]
- upper_bound gives first element > target, so index gives count of ≤ target
- Use frequency array for O(1) lookups when values are small

Approach 1: Sort + Binary Search
1. Sort b[] in ascending order
2. For each element x in a[]:
   - Use upper_bound(b.begin(), b.end(), x)
   - Count = index returned by upper_bound
3. Return counts vector

Approach 2: Frequency Array (When max value is reasonable)
1. Create frequency array of size max(b[i]) + 1
2. Compute prefix sums for cumulative counts
3. For each element x in a[]:
   - If x <= max_b: count = prefix[x]
   - Else: count = prefix[max_b]
4. Return counts vector

Why Binary Search works:
- upper_bound returns iterator to first element > x
- All elements before this iterator are ≤ x
- Index position gives exact count needed

------------------------------------------------
TIME COMPLEXITY:
Approach 1 (Sort + Binary Search): O((n+m)logm + nlogm)
Approach 2 (Frequency Array): O(n+m+max(b))

SPACE COMPLEXITY:
Approach 1: O(m) for sorted array
Approach 2: O(max(b)) for frequency array

------------------------------------------------
GFG LINK:
https://www.geeksforgeeks.org/problems/counting-elements-in-two-arrays/1

Related:
- Upper and Lower Bound
- Count Smaller or Equal elements
- Binary Search applications

------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---------------- APPROACH 1: SORT + BINARY SEARCH ----------------
    // TC: O((n+m)logm + nlogm)  SC: O(m)
    vector<int> countLessEq_BinarySearch(vector<int>& a, vector<int>& b) {
        
        int n = a.size(), m = b.size();
        
        // Step 1: Sort array b for binary search
        sort(b.begin(), b.end());
        
        vector<int> result;
        
        // Step 2: For each element in a, find count using upper_bound
        for(int x : a) {
            // upper_bound gives first element > x
            // Index gives count of elements ≤ x
            auto it = upper_bound(b.begin(), b.end(), x);
            int count = it - b.begin();
            result.push_back(count);
        }
        
        return result;
    }


    // ---------------- APPROACH 2: FREQUENCY ARRAY + PREFIX SUM ----------------
    // TC: O(n+m+max(b))  SC: O(max(b))
    vector<int> countLessEq_Frequency(vector<int>& a, vector<int>& b) {
        
        int n = a.size(), m = b.size();
        
        // Find maximum value in b to determine frequency array size
        int max_b = *max_element(b.begin(), b.end());
        
        // Step 1: Create frequency array for b
        vector<int> freq(max_b + 1, 0);
        for(int x : b) {
            freq[x]++;
        }
        
        // Step 2: Compute prefix sums (cumulative counts)
        vector<int> prefix(max_b + 1, 0);
        prefix[0] = freq[0];
        for(int i = 1; i <= max_b; i++) {
            prefix[i] = prefix[i-1] + freq[i];
        }
        
        // Step 3: Answer queries for each element in a
        vector<int> result;
        for(int x : a) {
            if(x <= max_b) {
                result.push_back(prefix[x]);
            } else {
                // If x > max_b, all elements in b are ≤ x
                result.push_back(m);
            }
        }
        
        return result;
    }


    // ---------------- MAIN FUNCTION ----------------
    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        
        // Choose approach based on constraints
        int max_b = b.empty() ? 0 : *max_element(b.begin(), b.end());
        
        // If max value is reasonable (< 10^6), use frequency array
        // Otherwise, use binary search approach
        if(max_b <= 1000000) {
            return countLessEq_Frequency(a, b);
        } else {
            return countLessEq_BinarySearch(a, b);
        }
    }
};

/*
ALGORITHM SUMMARY:
--------------------------------
APPROACH 1 - Sort + Binary Search:
1. Sort array b: O(m log m)
2. For each x in a: upper_bound(b, x) → O(log m)
3. Count = index returned by upper_bound
4. Total: O((n+m)logm)

APPROACH 2 - Frequency Array:
1. freq[val] = count of val in b
2. prefix[i] = sum of freq[0..i]
3. For x in a: if x <= max_b → prefix[x], else → m
4. Total: O(n+m+max_b)

Key Insights:
- upper_bound gives first element > target
- Index position = count of ≤ target elements
- Frequency array works well when max value is reasonable
- Prefix sum enables O(1) range sum queries

Interview Tips:
- Explain why upper_bound gives correct count
- Discuss trade-offs between both approaches
- Mention when to use frequency vs binary search
- Handle edge cases (empty arrays, large values)

------------------------------------------------
TEST CASES:
--------------------------------
1. a=[4,8,7,5,1], b=[4,48,3,0,1,1,5] → [5,6,6,6,3]
2. a=[10,20], b=[30,40,50] → [0,0]
3. a=[1,2,3], b=[1,1,1,1] → [4,4,4]
4. a=[5,5,5], b=[1,2,3,4,5] → [5,5,5]
5. a=[0], b=[0,0,0] → [3]
6. a=[], b=[1,2,3] → []
7. a=[1,2,3], b=[] → [0,0,0]
8. a=[100000], b=[99999,100000] → [2]

Edge Cases:
- Empty arrays
- All elements same
- Large values
- No elements ≤ target
- All elements ≤ target

------------------------------------------------
*/
