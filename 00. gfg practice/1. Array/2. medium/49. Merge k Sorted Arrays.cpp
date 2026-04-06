/*
PROBLEM: Merge K Sorted Arrays (GFG)

Given a matrix mat[][] where each row is sorted,
merge all rows into one single sorted array.

Example:
[
 [1,3,5,7],
 [2,4,6,8],
 [0,9,10,11]
]
Output:
[0,1,2,3,4,5,6,7,8,9,10,11]

--------------------------------------------------

APPROACH 1: BRUTE FORCE
Put all elements into one array and sort.

Time: O(N*M log(N*M))
Space: O(N*M)

--------------------------------------------------

APPROACH 2: MERGE ARRAYS ONE BY ONE
Merge row 1 and row 2 → result
Then merge result with row 3 → result
Then merge with row 4...

Time: O(N * M * K)
Not optimal.

--------------------------------------------------

APPROACH 3 (OPTIMAL): MIN HEAP

This is same as:
"Merge K Sorted Lists"

Idea:
- Put first element of each row into min heap
- Pop smallest element → add to answer
- Insert next element from that row
- Repeat

Heap stores:
(value, row, col)

--------------------------------------------------

TIME COMPLEXITY:
O(N*M * log N)
N = number of rows

SPACE COMPLEXITY:
O(N)

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/merge-k-sorted-arrays/1

LeetCode Similar:
https://leetcode.com/problems/merge-k-sorted-lists/

--------------------------------------------------
*/

class Solution {
  public:
    vector<int> mergeArrays(vector<vector<int>> &mat) {
        // Code here
        // priority queue <value, array index (x), index (y)>
        vector<int> result;
        int n = mat.size();
        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>
        > pq;
        
        // push first element of all the arr in mat
        for(int i = 0; i < n; i++){
            if(mat[i].size()){
                int val = mat[i][0];
                int x = i;
                int y = 0;
                
                pq.push({val, x, y});
            }
        }
        
        while(pq.size()){
            auto [val, x, y] = pq.top();
            pq.pop();
            result.push_back(val);
            if(y + 1 < mat[x].size()){
                pq.push({mat[x][y +  1], x, y + 1});
            }
        }
        
        return result;
        
    }
};


/*
---------------- DRY RUN ----------------

Input:
[1,3,5]
[2,4,6]
[0,9,10]

Heap initially:
1, 2, 0

Pop 0 → push 9
Pop 1 → push 3
Pop 2 → push 4
Pop 3 → push 5
Pop 4 → push 6
Pop 5
Pop 6
Pop 9 → push 10
Pop 10

Result:
0 1 2 3 4 5 6 9 10

--------------------------------------------------

PATTERN RECOGNITION:

If problem says:
- K sorted arrays
- Merge sorted lists
- Smallest element from multiple arrays
→ Use MIN HEAP

This is a VERY IMPORTANT HEAP PATTERN.
*/