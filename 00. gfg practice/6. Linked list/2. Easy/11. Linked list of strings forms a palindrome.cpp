/*
GeeksforGeeks: Linked list of strings forms a palindrome
Difficulty: Easy

Problem:
Given a linked list with string data, check whether the combined string forms a palindrome. 
If the combined string is palindrome then return true otherwise return false.

Example 1:
Input: a -> bc -> d -> dcb -> a
Output : true
Explanation: As string "abcddcba" is palindrome the function should return true.

Example 2:
Input: a -> bc -> dba
Output : false
Explanation: As string "abcdba" is not palindrome the function should return false.

Core Idea:
Since each node contains a part of the string, we can concatenate all these parts to form the complete string.
Once we have the combined string, we can use the standard two-pointer approach (one at the beginning, one at the end) to check if the string reads the same forwards and backwards (a palindrome).

Approach:
1. Initialize an empty string `combined`.
2. Traverse the linked list from `head` to `NULL`.
3. In each iteration, append the current node's data (string) to `combined`.
4. After building the `combined` string, initialize two pointers: `left = 0` and `right = combined.length() - 1`.
5. Loop while `left < right`:
   a. If `combined[left] != combined[right]`, return `false`.
   b. Increment `left` and decrement `right`.
6. If the loop completes without mismatches, return `true`.

Time Complexity: O(L) where L is the total number of characters across all strings in the linked list. We append characters to the string and then check them.
Space Complexity: O(L) to store the concatenated string.

GFG Link:
https://www.geeksforgeeks.org/problems/linked-list-of-strings-forms-a-palindrome/1
*/

#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
    
    Node(string x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    bool compute(Node* head) {
        if (head == NULL) return true;
        
        string combined = "";
        Node* curr = head;
        
        // Step 1: Concatenate all strings
        while (curr != NULL) {
            combined += curr->data;
            curr = curr->next;
        }
        
        // Step 2: Check for palindrome
        int left = 0;
        int right = combined.length() - 1;
        
        while (left < right) {
            if (combined[left] != combined[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
};

/*
Dry Run — Example 1:
Input: a -> bc -> d -> dcb -> a

Initial state:
head -> ["a"] -> ["bc"] -> ["d"] -> ["dcb"] -> ["a"] -> NULL

Step 1 (Concatenation):
- curr points to ["a"]. combined = "a"
- curr points to ["bc"]. combined = "abc"
- curr points to ["d"]. combined = "abcd"
- curr points to ["dcb"]. combined = "abcddcb"
- curr points to ["a"]. combined = "abcddcba"

Step 2 (Palindrome Check):
combined = "abcddcba"
length = 8
left = 0, right = 7

Iteration 1:
left = 0 ('a'), right = 7 ('a'). Match! left=1, right=6.

Iteration 2:
left = 1 ('b'), right = 6 ('b'). Match! left=2, right=5.

Iteration 3:
left = 2 ('c'), right = 5 ('c'). Match! left=3, right=4.

Iteration 4:
left = 3 ('d'), right = 4 ('d'). Match! left=4, right=3.

Loop condition `left < right` (4 < 3) is FALSE. Loop terminates.

Final Output: true
*/
