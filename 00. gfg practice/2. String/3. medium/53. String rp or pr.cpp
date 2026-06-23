/*
    Problem Name: String rp or pr
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string S. In one operation, you can remove the substring "pr" from the string S and get amount X or you can remove the substring "rp" and get the amount Y. 
    Find the maximum amount you can get if you perform zero or more such operations optimally.

    Expected Complexities:
    Time Complexity: O(|S|), where |S| is the length of the string.
    Space Complexity: O(|S|) to store the remaining characters during processing.

    Love Babbar Style Approach:
    1. Greedy Choice: To maximize the total amount, we should greedily prioritize the operation that gives a higher score. If `X > Y`, removing "pr" gives more money, so we should remove all possible "pr"s first, and then process the leftover string to remove any "rp"s. If `Y > X`, we do the reverse.
    2. Stack-based String processing: 
       - Instead of actually modifying the string (which takes O(N) per deletion and leads to O(N^2) time), we can simulate string deletions using a Stack (or a string behaving as a stack).
       - Let `s1` be the pattern we want to remove first (with higher value `max(X, Y)`), and `s2` be the pattern with lower value.
       - Pass 1: Iterate through the string `S` and push characters into `stack1`. Whenever the top two characters of `stack1` form `s1`, we pop them and add `max(X, Y)` to our total amount.
       - Pass 2: We take the leftover characters from `stack1` and do the same process using `stack2` to find and remove `s2`, adding `min(X, Y)` to our amount.
    3. Result: Return the final accumulated amount.

    Dry Run:
    Input: X = 5, Y = 4, S = "abppprrr"
    - Since X > Y, our first priority is "pr" (s1 = "pr"), and second is "rp" (s2 = "rp").
    Pass 1 (Finding "pr"):
    - Push 'a', 'b', 'p', 'p', 'p' -> stack1 = "abppp"
    - Push 'r' -> stack1 ends with "pr". Pop "pr", amount += 5. stack1 = "abpp"
    - Push 'r' -> stack1 ends with "pr". Pop "pr", amount += 5. stack1 = "abp"
    - Push 'r' -> stack1 ends with "pr". Pop "pr", amount += 5. stack1 = "ab"
    - Leftover string in stack1 is "ab". Amount = 15.
    Pass 2 (Finding "rp"):
    - Process "ab" from stack1. No "rp" found.
    Result: 15
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
  public:
    long long solve(int X, int Y, string S) {
        long long amount = 0;
        string s1 = "pr", s2 = "rp";
        
        // Ensure that X >= Y, meaning s1 is always the higher priority substring
        if (X < Y) {
            swap(X, Y);
            swap(s1, s2);
        }
        
        // Pass 1: Greedily remove the higher priority substring (s1)
        string stack1 = "";
        for (char ch : S) {
            stack1 += ch;
            int n = stack1.size();
            if (n >= 2 && stack1[n - 2] == s1[0] && stack1[n - 1] == s1[1]) {
                amount += X;
                stack1.pop_back();
                stack1.pop_back();
            }
        }
        
        // Pass 2: Remove the lower priority substring (s2) from the leftover string
        string stack2 = "";
        for (char ch : stack1) {
            stack2 += ch;
            int n = stack2.size();
            if (n >= 2 && stack2[n - 2] == s2[0] && stack2[n - 1] == s2[1]) {
                amount += Y;
                stack2.pop_back();
                stack2.pop_back();
            }
        }
        
        return amount;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int X, Y;
            string S;
            cin >> X >> Y >> S;
            Solution ob;
            cout << ob.solve(X, Y, S) << "\n";
        }
    }
    return 0;
}
