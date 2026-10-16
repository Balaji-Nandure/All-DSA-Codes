/**
 * Problem: Queue based approach for first non-repeating character in a stream
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In static strings, non-repeating characters can be found in two passes (count then scan).
 * - Here, data arrives as an ONLINE dynamic continuous stream, requiring instant output after each
 *   new character arrival.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Frequency Map + FIFO Queue:
 *   - `freq[26]`: Tracks arrival count of each alphabet character.
 *   - `q`: Maintains candidate non-repeating characters in strict arrival order (FIFO).
 *   - On arrival of character `ch`:
 *     1. Increment `freq[ch - 'a']++`.
 *     2. Enqueue `ch` into `q`.
 *     3. Check front of queue:
 *        - While `!q.empty()` and `freq[q.front() - 'a'] > 1`:
 *          - This character is now repeated and can NEVER again serve as the first non-repeating character!
 *          - Permanently dequeue it (`q.pop()`).
 *     4. If queue is empty, output `'#'`; otherwise, output `q.front()`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each character is enqueued and dequeued at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(26) = O(1) auxiliary space (queue never holds more than 26 distinct characters).
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>

std::string FirstNonRepeating(const std::string& A) {
    std::vector<int> freq(26, 0);
    std::queue<char> q;
    std::string result = "";

    for (char c : A) {
        freq[c - 'a']++;
        q.push(c);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Discard all elements from queue front whose frequency has exceeded 1.
        while (!q.empty() && freq[q.front() - 'a'] > 1) {
            q.pop();
        }

        if (q.empty()) {
            result += '#';
        } else {
            result += q.front();
        }
    }

    return result;
}

int main() {
    std::string s1 = "aabc";
    std::cout << "Stream " << s1 << " -> " << FirstNonRepeating(s1) << "\n"; // "a#bb"

    std::string s2 = "zz";
    std::cout << "Stream " << s2 << " -> " << FirstNonRepeating(s2) << "\n"; // "z#"

    return 0;
}
