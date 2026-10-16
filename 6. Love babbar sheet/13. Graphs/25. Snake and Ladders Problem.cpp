/**
 * Problem: Snake and Ladder Problem (Minimum Throws to Reach Destination)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - The board is linear (squares 1 to N), but state transitions are directed and asymmetric:
 *   - Normal die throws move +1 to +6.
 *   - Landing on a snake or ladder instantly teleports the player to a predetermined destination square.
 * - This forms an unweighted directed graph where BFS yields the exact minimum number of die throws.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Breadth-First Search (BFS) on Board States:
 *   - Represent moves using a 1D array `moves[N + 1]` initialized to `-1`.
 *   - If there is a ladder or snake from square `u` to `v`, set `moves[u] = v`.
 *   - Queue stores `pair<int, int>`: `{currentSquare, throwCount}`.
 *   - For current square `curr`:
 *     - Try all die outcomes `1 <= dice <= 6`: `nextSquare = curr + dice`.
 *     - If `nextSquare <= N`:
 *       - If `moves[nextSquare] != -1`, teleport to `dest = moves[nextSquare]`; else `dest = nextSquare`.
 *       - If `dest` not yet visited, mark visited and push into queue with `throwCount + 1`.
 *   - Stop when target `N` (e.g. 30 or 100) is reached.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each cell on the board is enqueued at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) for the BFS queue and visited tracking array.
 */

#include <iostream>
#include <vector>
#include <queue>

int minThrow(int N, std::vector<int>& arr) {
    // arr contains 2*N elements: [src1, dest1, src2, dest2, ...]
    int boardSize = 30; // Standard GFG board size is 30 (or 100)
    std::vector<int> moves(boardSize + 1, -1);

    for (int i = 0; i < 2 * N; i += 2) {
        moves[arr[i]] = arr[i + 1];
    }

    std::vector<bool> visited(boardSize + 1, false);
    std::queue<std::pair<int, int>> q;

    q.push({1, 0});
    visited[1] = true;

    while (!q.empty()) {
        auto [curr, throws] = q.front();
        q.pop();

        if (curr == boardSize) {
            return throws;
        }

        // Try rolling 1 through 6
        for (int dice = 1; dice <= 6 && (curr + dice) <= boardSize; dice++) {
            int nextCell = curr + dice;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Follow snake or ladder immediately; mark visited on destination to avoid redundant cyclic paths.
            int finalDest = (moves[nextCell] != -1) ? moves[nextCell] : nextCell;

            if (!visited[finalDest]) {
                visited[finalDest] = true;
                q.push({finalDest, throws + 1});
            }
        }
    }

    return -1; // Destination unreachable
}

int main() {
    int N = 8;
    // Snakes and Ladders pairs
    std::vector<int> arr = {
        3, 22, 5, 8, 11, 26, 20, 29, // Ladders
        17, 4, 19, 7, 21, 9, 27, 1   // Snakes
    };

    int throws = minThrow(N, arr);
    std::cout << "Minimum die throws to reach square 30: " << throws << "\n"; // Expected: 3

    return 0;
}
