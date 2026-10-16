/**
 * Problem: The Celebrity Problem
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A brute-force approach checks every pair of people resulting in O(N^2) inquiries.
 * - Here, by using pairwise elimination via Stack (or two pointers), each inquiry permanently disqualifies
 *   one person, finding the sole potential candidate in strictly O(N) inquiries.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Celebrity Definition:
 *   - Everyone knows the celebrity: Column for C has all 1s (except diagonal C,C).
 *   - Celebrity knows no one: Row for C has all 0s.
 * - Stack-Based Elimination:
 *   - Push all N persons onto a stack.
 *   - Pop top two people: A and B.
 *   - If A knows B (`M[A][B] == 1`): A CANNOT be the celebrity. Discard A, push B.
 *   - If A does NOT know B (`M[A][B] == 0`): B CANNOT be the celebrity (celebrity must be known to all). Discard B, push A.
 *   - Repeat until exactly 1 candidate remains.
 * - Verification Phase:
 *   - Check if candidate knows nobody (row is 0) and everyone knows candidate (column is 1).
 * 
 * TIME COMPLEXITY:
 * - O(N): (N-1) elimination steps + 2N verification checks.
 * 
 * SPACE COMPLEXITY:
 * - O(N) with stack (or O(1) with two pointers).
 */

#include <iostream>
#include <vector>
#include <stack>

int celebrity(const std::vector<std::vector<int>>& M, int n) {
    std::stack<int> st;

    // Step 1: Push all candidates onto stack
    for (int i = 0; i < n; i++) {
        st.push(i);
    }

    // Step 2: Pairwise eliminate candidates
    while (st.size() > 1) {
        int a = st.top(); st.pop();
        int b = st.top(); st.pop();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If a knows b, 'a' cannot be celebrity. If 'a' doesn't know b, 'b' cannot be celebrity.
        if (M[a][b] == 1) {
            st.push(b);
        } else {
            st.push(a);
        }
    }

    if (st.empty()) return -1;
    int candidate = st.top();

    // Step 3: Verify the remaining candidate
    for (int i = 0; i < n; i++) {
        if (i != candidate) {
            // Celebrity must know nobody, and everyone must know celebrity
            if (M[candidate][i] == 1 || M[i][candidate] == 0) {
                return -1;
            }
        }
    }

    return candidate;
}

int main() {
    std::vector<std::vector<int>> M = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };
    int n = 3;
    int celeb = celebrity(M, n);
    if (celeb == -1) {
        std::cout << "No celebrity found.\n";
    } else {
        std::cout << "Celebrity is person: " << celeb << "\n"; // Person 1
    }

    return 0;
}
