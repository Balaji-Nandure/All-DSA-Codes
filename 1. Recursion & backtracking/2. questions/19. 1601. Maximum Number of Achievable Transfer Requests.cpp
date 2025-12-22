/*
 * Problem: 1601. Maximum Number of Achievable Transfer Requests
 * 
 * We have n buildings numbered from 0 to n - 1. Each building has a number of employees.
 * The transfer request is represented as [from, to], meaning an employee wants to move 
 * from building 'from' to building 'to'.
 * 
 * All buildings are full, so a list of requests is achievable only if for each building,
 * the net change in employee transfers is zero. This means the number of employees 
 * leaving is equal to the number of employees entering.
 * 
 * Given n and an array of requests, return the maximum number of achievable requests.
 * 
 * Example 1:
 * Input: n = 5, requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]
 * Output: 5
 * Explanation: Let's see the requests:
 * - Building 0: employees leave (0->1, 0->1), employees enter (1->0, 2->0) = balanced
 * - Building 1: employees leave (1->0, 1->2), employees enter (0->1, 0->1) = balanced
 * - Building 2: employees leave (2->0), employees enter (1->2) = balanced
 * - Building 3: employees leave (3->4), employees enter () = NOT balanced
 * - Building 4: employees leave (), employees enter (3->4) = NOT balanced
 * So we can achieve at most 5 requests (excluding 3->4).
 * 
 * Example 2:
 * Input: n = 3, requests = [[0,0],[1,2],[2,1]]
 * Output: 3
 * Explanation: All requests are achievable.
 * 
 * Constraints:
 * - 1 <= n <= 20
 * - 1 <= requests.length <= 16
 * - requests[i].length == 2
 * - 0 <= fromi, toi < n
 */

#include <bits/stdc++.h>
using namespace std;

// Backtracking: try all subsets of requests (pick/not pick)
void backtrack(int idx, vector<vector<int>>& requests, vector<int>& balance, 
               int count, int& maxCount) {
    // Base case: processed all requests
    if (idx == (int)requests.size()) {
        // Check if all buildings are balanced (net change = 0)
        // For a request to be achievable, each building must have equal in/out transfers
        bool allBalanced = true;
        for (int i = 0; i < (int)balance.size(); i++) {
            if (balance[i] != 0) {
                allBalanced = false;
                break;
            }
        }
        
        // If all balanced, update maximum achievable requests
        if (allBalanced) {
            maxCount = max(maxCount, count);
        }
        return;
    }
    
    // NOT PICK: Skip current request
    backtrack(idx + 1, requests, balance, count, maxCount);
    
    // PICK: Include current request
    int from = requests[idx][0];
    int to = requests[idx][1];
    
    // Apply request: decrease balance at 'from', increase at 'to'
    balance[from]--;
    balance[to]++;
    
    backtrack(idx + 1, requests, balance, count + 1, maxCount);
    
    // Backtrack: restore balance
    balance[from]++;
    balance[to]--;
}

int maximumRequests(int n, vector<vector<int>>& requests) {
    vector<int> balance(n, 0);  // Track net change for each building
    int maxCount = 0;
    backtrack(0, requests, balance, 0, maxCount);
    return maxCount;
}

// Helper function to print result
void printResult(int result) {
    cout << "Maximum achievable requests: " << result << endl;
}

int main() {
    // Test case 1
    int n1 = 5;
    vector<vector<int>> requests1 = {{0,1}, {1,0}, {0,1}, {1,2}, {2,0}, {3,4}};
    cout << "Test case 1:" << endl;
    cout << "n = " << n1 << ", requests = [[0,1],[1,0],[0,1],[1,2],[2,0],[3,4]]" << endl;
    printResult(maximumRequests(n1, requests1));  // Expected: 5
    cout << endl;
    
    // Test case 2
    int n2 = 3;
    vector<vector<int>> requests2 = {{0,0}, {1,2}, {2,1}};
    cout << "Test case 2:" << endl;
    cout << "n = " << n2 << ", requests = [[0,0],[1,2],[2,1]]" << endl;
    printResult(maximumRequests(n2, requests2));  // Expected: 3
    cout << endl;
    
    // Test case 3
    int n3 = 4;
    vector<vector<int>> requests3 = {{0,3}, {3,1}, {1,2}, {2,0}};
    cout << "Test case 3:" << endl;
    cout << "n = " << n3 << ", requests = [[0,3],[3,1],[1,2],[2,0]]" << endl;
    printResult(maximumRequests(n3, requests3));  // Expected: 4
    cout << endl;
    
    // Test case 4: Edge case - all requests form a cycle
    int n4 = 3;
    vector<vector<int>> requests4 = {{0,1}, {1,2}, {2,0}};
    cout << "Test case 4:" << endl;
    cout << "n = " << n4 << ", requests = [[0,1],[1,2],[2,0]]" << endl;
    printResult(maximumRequests(n4, requests4));  // Expected: 3
    cout << endl;
    
    return 0;
}

