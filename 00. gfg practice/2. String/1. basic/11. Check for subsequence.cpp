/*
Problem:
Check whether string A is a subsequence of string B.

Subsequence:
Characters should appear in same order,
but not necessarily continuously.

Example:
A = "gksrek"
B = "geeksforgeeks"

Answer = true

Because:
g -> k -> s -> r -> e -> k
appears in same order inside B.

Approach:
Two Pointer Technique

1. Pointer i for string A
2. Pointer j for string B
3. Traverse B:
      if A[i] == B[j]
           move i forward
4. If i reaches end of A,
   then A is subsequence of B.

Why this works?
- We greedily match characters in order.
- Relative ordering is preserved.

Dry Run:
A = "AXY"
B = "YADXCP"

Y != A
A == A  -> move i
D != X
X == X  -> move i
C != Y
P != Y

Not fully matched => false

Pattern:
Two Pointers

Time Complexity: O(N)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/check-for-subsequence4930/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool isSubSequence(string A, string B) {

        int i = 0; // pointer for A
        int j = 0; // pointer for B

        // Traverse B
        while(j < B.size()) {

            // Character matched
            if(i < A.size() && A[i] == B[j]) {
                i++;
            }

            j++;
        }

        // If all chars of A matched
        return (i == A.size());
    }
};

/*
Summary:
- Use two pointers
- Match characters in order
- If all characters of A are matched,
  then A is subsequence of B
*/
