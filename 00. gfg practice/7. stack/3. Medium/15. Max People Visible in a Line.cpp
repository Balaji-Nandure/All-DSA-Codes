/*
    Problem Name: Max People Visible in a Line
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given an array `arr[]`, where `arr[i]` represents the height of the i-th person
    standing in a line. A person `i` can see another person `j` if:
    1. height[j] < height[i], AND
    2. There is no person `k` standing between them such that height[k] >= height[i].

    Each person can see in both directions (front and back / left and right).
    Your task is to find the maximum number of people that any person can see (including themselves).

    Examples:
    Input: arr = [6, 2, 5, 4, 5, 1, 6]
    Output: 6
    Explanation:
    - Person 0 (height 6): Blocked on the right by person 6 (height 6 >= 6).
      Can see indices 1, 2, 3, 4, 5 (all < 6) + himself = 6 people.
    - Person 6 (height 6): Blocked on the left by person 0 (height 6 >= 6).
      Can see indices 5, 4, 3, 2, 1 + himself = 6 people.
    - Maximum visible is 6.

    Input: arr = [1, 3, 6, 4]
    Output: 4
    Explanation:
    - Person 2 (height 6) sees index 0 (height 1) and index 1 (height 3) on the left,
      and index 3 (height 4) on the right + himself = 4 people.

    Constraints:
    1 <= arr.size() <= 10^4
    1 <= arr[i] <= 10^5

    Expected Complexities:
    Time Complexity: O(N)
    Auxiliary Space: O(N)

    Approach: Monotonic Stack (Nearest Greater or Equal Element) (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. For person `i` with height `arr[i]`:
       - To the left, person `i` can see all strictly shorter people until blocked by someone
         with height `>= arr[i]`.
       - To the right, person `i` can see all strictly shorter people until blocked by someone
         with height `>= arr[i]`.
    2. Thus, the sight range of person `i` is bounded by:
       - `left[i]`: index of the Nearest Greater or Equal element to the left (default -1 if none).
       - `right[i]`: index of the Nearest Greater or Equal element to the right (default n if none).
    3. Number of people visible:
       - On left: `leftCount = i - left[i] - 1`
       - On right: `rightCount = right[i] - i - 1`
       - Including himself: `total = leftCount + rightCount + 1` = `right[i] - left[i] - 1`.
    4. We find `left[i]` and `right[i]` in O(N) time using two passes with a monotonic stack.
    5. The answer is `max(total)` over all `0 <= i < n`.

    DRY RUN:
    Example: arr = [1, 3, 6, 4], n = 4
    - left:
      * i = 0 (1): st empty -> left[0] = -1, st = [0]
      * i = 1 (3): pop 0, st empty -> left[1] = -1, st = [1]
      * i = 2 (6): pop 1, st empty -> left[2] = -1, st = [2]
      * i = 3 (4): st.top() is 2 (val 6 >= 4) -> left[3] = 2, st = [2, 3]
      left = [-1, -1, -1, 2]
    - right:
      * i = 3 (4): st empty -> right[3] = 4, st = [3]
      * i = 2 (6): pop 3, st empty -> right[2] = 4, st = [2]
      * i = 1 (3): st.top() is 2 (val 6 >= 3) -> right[1] = 2, st = [2, 1]
      * i = 0 (1): st.top() is 1 (val 3 >= 1) -> right[0] = 1, st = [2, 1, 0]
      right = [1, 2, 4, 4]
    - Total visible for each person:
      * i = 0: 1 - (-1) - 1 = 1
      * i = 1: 2 - (-1) - 1 = 2
      * i = 2: 4 - (-1) - 1 = 4
      * i = 3: 4 - 2 - 1 = 1
    - Maximum = 4.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach: Monotonic Stack (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    int maxPeople(vector<int>& arr) {
        int n = arr.size();

        vector<int> left(n, -1), right(n, n);
        stack<int> st;

        // Nearest greater or equal on the left
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] < arr[i]) {
                st.pop();
            }

            if (!st.empty()) {
                left[i] = st.top();
            }

            st.push(i);
        }

        while (!st.empty()) {
            st.pop();
        }

        // Nearest greater or equal on the right
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] < arr[i]) {
                st.pop();
            }

            if (!st.empty()) {
                right[i] = st.top();
            }

            st.push(i);
        }

        int ans = 1;

        for (int i = 0; i < n; i++) {
            int leftCount = i - left[i] - 1;
            int rightCount = right[i] - i - 1;

            int total = leftCount + rightCount + 1;

            ans = max(ans, total);
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int maxPeople(vector<int>& arr) {
        SolutionStack solver;
        return solver.maxPeople(arr);
    }
};
